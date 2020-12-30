//
// Created by 王梦思 on 2018/08/11.
//

#include <jni.h>
#include <ECGpreproc.h>
#include <sys/time.h>
#include <android/log.h>
#include <string.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"JniHelper",__VA_ARGS__)

extern "C" {

static bool IS_DEBUG = false;

long getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

JNIEXPORT void JNICALL
Java_com_proton_ecgcard_algorithm_utils_FilterAlgorithmHelper_init(JNIEnv *env, jclass type,
                                                                   jboolean isDebug) {
    IS_DEBUG = isDebug;
}

JNIEXPORT jobject JNICALL
Java_com_proton_ecgcard_algorithm_utils_FilterAlgorithmHelper_processEcgData(JNIEnv *env,
                                                                             jobject obj,
                                                                             jdoubleArray doubles_,
                                                                             jlong section,
                                                                             jint sample,
                                                                             jint band50Switch,
                                                                             jint band100Switch,
                                                                             jint lowpassSwitch,
                                                                             jint highpassSwitch,
                                                                             jint smoothSwitch) {
    jclass arraylistClass = env->FindClass("java/util/ArrayList");
    jmethodID listAddMethod = env->GetMethodID(arraylistClass, "add", "(Ljava/lang/Object;)Z");
    //构造返回的对象
    jclass ecgData = env->FindClass("com/proton/ecgcard/algorithm/bean/RealECGData");
    //获取返回的数组
    jfieldID ecgDataFiled = env->GetFieldID(ecgData, "ecgData", "Ljava/util/List;");
    jmethodID ecgDataInit = env->GetMethodID(ecgData, "<init>", "()V");
    jobject ecgDataObj = env->AllocObject(ecgData);
    env->CallVoidMethod(ecgDataObj, ecgDataInit);
    jobject ecgDatas = env->GetObjectField(ecgDataObj, ecgDataFiled);
    int size = env->GetArrayLength(doubles_);
    vector<double> arrayValue(static_cast<unsigned long>(size));
    env->GetDoubleArrayRegion(doubles_, 0, size, &arrayValue[0]);

    long startTime = getCurrentTime();
    LOGI("数据大小:%d,section:%ld,采样率:%d", size, section, sample);
    ECGData data = processEcgData(arrayValue, section, sample, band50Switch, band100Switch,
                                  lowpassSwitch, highpassSwitch, smoothSwitch);
    if (IS_DEBUG) {
        LOGI("算法处理时间:%ld,数据大小:%d,section:%ld", getCurrentTime() - startTime, size, section);
    }
    jclass f_class = env->FindClass("java/lang/Float");
    jmethodID f_init = env->GetMethodID(f_class, "<init>", "(F)V");

    for (int i = 0; i < data.valueArray.size(); i++) {
        jobject f = env->AllocObject(f_class);
        env->CallVoidMethod(f, f_init, (float) -data.valueArray[i]);
        env->CallBooleanMethod(ecgDatas, listAddMethod, f);
        env->DeleteLocalRef(f);
    }

    jfieldID insHeartRateField = env->GetFieldID(ecgData, "heartRate", "I");
    jfieldID signalQualityIndexField = env->GetFieldID(ecgData, "signalQuality", "I");
    jfieldID sectionField = env->GetFieldID(ecgData, "section", "J");
    jfieldID breathField = env->GetFieldID(ecgData, "breath", "I");
    env->SetIntField(ecgDataObj, insHeartRateField, data.insHeartRate);
    env->SetIntField(ecgDataObj, signalQualityIndexField, data.signalQualityIndex);
    env->SetLongField(ecgDataObj, sectionField, data.section);
    env->SetIntField(ecgDataObj, breathField, data.insRes);

    return ecgDataObj;
}

JNIEXPORT jobject JNICALL
Java_com_proton_ecgcard_algorithm_utils_FilterAlgorithmHelper_fullAnalyse(JNIEnv *env,
                                                                          jobject obj,
                                                                          jdoubleArray ecgys_,
                                                                          jint sample,
                                                                          jint band50Switch,
                                                                          jint band100Switch,
                                                                          jint lowpassSwitch,
                                                                          jint highpassSwitch,
                                                                          jint smoothSwitch) {
    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID listAddMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
    jclass doubleClass = env->FindClass("java/lang/Float");
    jmethodID doubleInit = env->GetMethodID(doubleClass, "<init>", "(F)V");
    jclass intClass = env->FindClass("java/lang/Integer");
    jmethodID intInit = env->GetMethodID(intClass, "<init>", "(I)V");
    //获取类以及类的属性id 对象属性id
    jclass resultClass = env->FindClass("com/proton/ecgcard/algorithm/bean/AlgorithmResult");
    //创建返回结果对象
    jmethodID resultInit = env->GetMethodID(resultClass, "<init>", "()V");
    jobject resultObj = env->NewObject(resultClass, resultInit);
    jfieldID filterDatasField = env->GetFieldID(resultClass, "filterDatas", "Ljava/util/List;");
    jfieldID sourceDatasField = env->GetFieldID(resultClass, "sourceDatas", "Ljava/util/List;");
    jobject filterDataObj = env->GetObjectField(resultObj, filterDatasField);
    jobject sourceDataObj = env->GetObjectField(resultObj, sourceDatasField);
    jfieldID peakSumField = env->GetFieldID(resultClass, "peaksum", "I");
    jfieldID heartRateField = env->GetFieldID(resultClass, "heartRate", "I");
    jfieldID heartRaceField = env->GetFieldID(resultClass, "heartPace", "I");
    jfieldID highestRateField = env->GetFieldID(resultClass, "highestRate", "I");
    jfieldID lowestRateField = env->GetFieldID(resultClass, "lowestRate", "I");
    jfieldID heartFastTimeField = env->GetFieldID(resultClass, "heartFastTime", "J");
    jfieldID heartSlowTimeField = env->GetFieldID(resultClass, "heartSlowTime", "J");
    jfieldID maxHRTimeField = env->GetFieldID(resultClass, "maxHRTime", "I");
    jfieldID minHRTimeField = env->GetFieldID(resultClass, "minHRTime", "I");
    jfieldID heartSlowMaxBeatField = env->GetFieldID(resultClass, "heartSlowMaxBeat", "I");
    jfieldID heartSlowMaxTimeField = env->GetFieldID(resultClass, "heartSlowMaxTime", "I");
    jfieldID heartFastMaxField = env->GetFieldID(resultClass, "heartFastMaxBeat", "I");
    jfieldID heartFastMaxTimeField = env->GetFieldID(resultClass, "heartFastMaxTime", "I");

    jfieldID peakSumsField = env->GetFieldID(resultClass, "peakSums", "Ljava/util/List;");
    jobject peakSumsObj = env->GetObjectField(resultObj, peakSumsField);
    //原始数据大小
    int sourceDataSize = env->GetArrayLength(ecgys_);
    vector<double> ecgys(static_cast<unsigned long>(sourceDataSize));
    env->GetDoubleArrayRegion(ecgys_, 0, sourceDataSize, &ecgys[0]);
    FileData result = fullanalyse(ecgys, sample, band50Switch, band100Switch, lowpassSwitch,
                                  highpassSwitch, smoothSwitch);
    for (int i = 0; i < sourceDataSize; i++) {
        jobject filterValue = env->NewObject(doubleClass, doubleInit, result.dataArray[i]);
        jobject sourceValue = env->NewObject(doubleClass, doubleInit, ecgys[i]);
        env->CallBooleanMethod(filterDataObj, listAddMethod, filterValue);
        env->CallBooleanMethod(sourceDataObj, listAddMethod, sourceValue);
        env->DeleteLocalRef(filterValue);
        env->DeleteLocalRef(sourceValue);
    }

    for (int i = 0; i < result.Rind.size(); ++i) {
        jobject peakValue = env->NewObject(intClass, intInit, result.Rind[i]);
        env->CallBooleanMethod(peakSumsObj, listAddMethod, peakValue);
        env->DeleteLocalRef(peakValue);
    }

    vector<double>().swap(ecgys);
    env->SetIntField(resultObj, peakSumField, result.peakSum);
    env->SetIntField(resultObj, heartRateField, result.aveHR);
    env->SetIntField(resultObj, heartRaceField, result.heartPace);
    env->SetIntField(resultObj, highestRateField, result.maxHR);
    env->SetIntField(resultObj, lowestRateField, result.minHR);
    env->SetLongField(resultObj, heartFastTimeField, result.heartFastTime);
    env->SetLongField(resultObj, heartSlowTimeField, result.heartSlowTime);
    env->SetIntField(resultObj, maxHRTimeField, result.maxHRTime);
    env->SetIntField(resultObj, minHRTimeField, result.minHRTime);
    env->SetIntField(resultObj, heartSlowMaxBeatField, result.heartSlowMaxBeat);
    env->SetIntField(resultObj, heartSlowMaxTimeField, result.heartSlowMaxTime);
    env->SetIntField(resultObj, heartFastMaxField, result.heartFastMaxBeat);
    env->SetIntField(resultObj, heartFastMaxTimeField, result.heartFastMaxTime);
    return resultObj;
}
}