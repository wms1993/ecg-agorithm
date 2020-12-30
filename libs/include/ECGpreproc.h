//
//  ECGpreproc.h in ECG_patch_inspection project
//  Protontek
//
//  Created by Yizhou Zhong on 2018/09/05.
//  Copyright © 2018年 ZYZ. All rights reserved.
//  Version: 1.0.12.0 
//  Version Date: 2019/03/19
//
#ifndef ECGperproc_H
#define ECGperproc_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>

#ifdef LIBRARY_EXPORTS
#    define LIBRARY_API __declspec(dllexport)
#else
#    define LIBRARY_API __declspec(dllimport)
#endif

using namespace std;
using std::string;
const int ecgPatchLoop = 200;//平滑次数
const int ecgCardSigLoop = 2;//可调，该值过大，平滑越明显，同时正向峰值会被削峰
const int ecgCardNoiseLoop = 10;//可调，该值过大，平滑越明显，同时负向峰值会被削峰


struct FastAndSlowStruct
{
    int* fastBeginIndex;
    int* fastEndIndex;
    int fastNum;
    int* slowBeginIndex;
    int* slowEndIndex;
    int slowNum;
};

struct EcgAccFullResult
{
    vector< vector<int> > accResult;
    vector<double> dataArray;
    vector<double> RRs;
    FastAndSlowStruct fastAndSlowStruct;
};


struct BaseData
{
    int aveHR;					// 平均心率
    int maxHR;					// 最快心率
    int minHR;					// 最慢心率
    int peakSum;				// R 峰总数
    int heartPace;				// 用于表征正常(0)、心动过缓(1)、心动过速(2)；
    int sampr;					// 信号采样率
    int heartSlowTime;			// 心动过缓时长	ms
    int heartFastTime;			// 心动过速时长	ms
    int maxHRTime;				// 最快心率发生时刻 ms
    int minHRTime;				// 最慢心率发生时刻 ms
    int heartSlowMaxBeat;   	// 最长心动过缓连续心拍数
    int heartSlowMaxTime;		// 最长心动过缓时刻 ms
    int heartFastMaxBeat;		// 最长心动过速连续心拍数
    int heartFastMaxTime;		// 最长心动过速时刻 ms
};

/* 该结构为 hrvAnalyse() 函数的返回类型
StressIndex 精神压力指标 : -1 错误; 0 正常; 1 轻度; 2 中度; 3 重度
StressScore 精神压力分数 : -1 错误; 0 ~ 100 正常值
SMS 精神压力减分 : 0 ~ 15
HRV指标数值 26~82为正常范围，0~26为偏低，82以上为偏高
AlcoholRiskIndex 饮酒风险指标 : -1 错误; 0 低; 1 中低; 2 中; 3 中高; 4 高
AlcoholRiskScore 饮酒风险指标 : -1 错误; 5 ~ 100 正常值
ARMS 饮酒风险减分: 0 ~ 15
*/
struct FileData : BaseData
{
    vector<double> RRs;
    vector<double> dataArray;	// 滤波后的 ECG 信号
    vector<int> Rpeaks;			// R 峰坐标向量
    // 院内版本 app 所需接口
    vector<double> ecgmodel;	// 输入分类模型的 ECG 信号
    double extrPercent;
    //double extrPercentNoless;
    bool interference; //HRV干扰程度
    //int extremeRRs;
    //double extreRRsper;
    //int extremeBPM;
    //double extreBPMper;
    int StressIndex;
    int StressScore;
    int SMS;
    int HRVScore;
    int HRVIndex;
    int AlcoholRiskIndex;
    int AlcoholRiskScore;
    int ARMS;
    double SDNN;
    double RMSSD;

    vector<int> Rind;           // R 峰坐标的另一种表达方式

    double TP;   //20191121 浙江医院远程心电诊断报告新增
    double VLF;
    double LF;
    double HF;
    int FatigueScore;
    int FatigueIndex;  //暂时没有需求
    double LFnorm;
    double HFnorm;
    double LFHFratio;
    //int StressIndex_origin;
    //int StressScore_origin;
    //int SMS_origin;
    //int HRVScore_origin;
    //int HRVIndex_origin;
    //int AlcoholRiskIndex_origin;
    //int AlcoholRiskScore_origin;
    //int ARMS_origin;
    //int SDNN_origin;
    //int RMSSD_origin;
    FastAndSlowStruct fastAndSlowStruct;
};

struct ServerData : BaseData
{
    int dataArrayLen;
    int RpeakNum;
    int RRNum;
    int StressIndex;
    int StressScore;
    int SMS;
    int HRVScore;
    int HRVIndex;
    int AlcoholRiskIndex;
    int AlcoholRiskScore;
    int ARMS;
    bool interference; // HRV干扰程度

    //20191121 浙江医院远程心电诊断报告新增
    double SDNN;
    double RMSSD;
    double TP;
    double VLF;
    double LF;
    double HF;
    int FatigueScore;
    int FatigueIndex;  // 暂时没有需求
    double LFnorm;
    double HFnorm;
    double LFHFratio;
    int fastNum;
    int slowNum;
    int insRes;
};

//struct CryptData
//{
//	vector<double> dataSource;	// 原始的 ECG 信号
//	vector<double> dataArray;	// 滤波后的 ECG 信号
//	int sampr;					// 采样率
//	vector<int> Rpeaks;			// R 峰坐标向量
//};

struct CryptData
{
    double* dataSource;	// 原始的 ECG 信号
    int dataSourceLen;
    double* dataArray;	// 滤波后的 ECG 信号
    int dataArrayLen;
    int sampr;			// 采样率
    int* rind;			// R 峰坐标向量
    int rindLen;
};

struct EncryptData
{
    unsigned char* fileOutput;
    int filebyteLen;
};

struct ECGData
{
    vector<double> valueArray;	// 实时心电信号
    vector<long> indexArray;	// 实时 R 峰坐标
    int insHeartRate;			// 实时心率值
    int signalQualityIndex;		// 信号质量指标：0 正常, 1 干扰
    long section;				// 实时心电分段编号 从 0 开始计数
    int insRes;                 // 实时呼吸率
};

struct ECGData4Server
{
    long* indexArray;	// 实时 R 峰坐标
    int RNum;           // R峰数量
    int insHeartRate;			// 实时心率值
    int signalQualityIndex;		// 信号质量指标：0 正常, 1 干扰
    long section;				// 实时心电分段编号 从 0 开始计数
    int insRes;                 // 实时呼吸率
    int insFlag;
};

struct ECGDataJson
{
    int insHeartRate;			// 实时心率值
    int signalQualityIndex;		// 信号质量指标：0 正常, 1 干扰
    long section;				// 实时心电分段编号 从 0 开始计数
    int insRes;                 // 实时呼吸率
    int dataArrayLen;
    int RpeakNum;
};

struct ECGData4hw
{
    int insHeartRate;			// 实时心率值
    int signalQualityIndex;		// 信号质量指标：0 正常, 1 干扰
    long section;				// 实时心电分段编号 从 0 开始计数
};


ECGData processEcgData4(std::vector<double>arrayValue);

int processEcgData3();

ECGData processEcgData(std::vector<double>arrayValue, long section, int sampr, int band50Switch, int band100Switch, int lowpassSwitch, int highpassSwitch, int smoothSwitch);
//extern "C" LIBRARY_API
/* 实时心电信号处理函数
输入值：
arrayValue：		原始实时心电信号
section：		实时心电分段编号 从 0 开始计数
sampr：			心电信号采样率，分为 256 512 500 三种情况
band50Switch：	50Hz 带阻滤波器开关，0关闭，1开启；
band100Switch：	100Hz 带阻滤波器开关，0关闭，1开启；
lowpassSwitch：	低通滤波器开关，0关闭，1开启；
highpassSwitch：高通滤波器开关，0关闭，1开启；
smoothSwitch：	平滑滤波开关，0关闭，1开启；
返回值：
ECGData 结构

*/
ECGDataJson processEcgDatawithJson(double* data, int dataLen, long section, int sampr, int* Rpeaks, int* RRs, int filterType);
//extern "C" LIBRARY_API
/* 实时心电信号处理函数
输入值：
arrayValue：		原始实时心电信号
section：		实时心电分段编号 从 0 开始计数
sampr：			心电信号采样率，分为 256 512 500 三种情况
band50Switch：	50Hz 带阻滤波器开关，0关闭，1开启；
band100Switch：	100Hz 带阻滤波器开关，0关闭，1开启；
lowpassSwitch：	低通滤波器开关，0关闭，1开启；
highpassSwitch：高通滤波器开关，0关闭，1开启；
smoothSwitch：	平滑滤波开关，0关闭，1开启；
返回值：
ECGData 结构

*/

ECGData4Server processEcgData4Server(double* arrayValue, int arrayLen, int section, int sampr, int insFlag, double* pd_inBandStopBefore, double* pd_outBandStopBefore, double* pd_inBandStopBefore100,
                                     double* pd_outBandStopBefore100, double* pd_inLowPassBefore, double* pd_outLowPassBefore);
//extern "C" LIBRARY_API
/* 实时心电信号处理函数用于多线程服务器
输入值：
arrayValue：	原始实时心电信号
arrayLen：      原始实时心电信号长度
section：		实时心电分段编号 从 0 开始计数
sampr：			心电信号采样率，分为 256 512 500 三种情况
pd_inBandStopBefore：      长度为12，初始值为0
pd_outBandStopBefore：     长度为12，初始值为0
pd_inBandStopBefore100：   长度为12，初始值为0
pd_outBandStopBefore100：  长度为12，初始值为0
pd_inLowPassBefore：       长度为337，初始值为0
pd_outLowPassBefore：      长度为337，初始值为0

返回值：
ECGData 结构

*/

FileData fullanalyse(std::vector<double>& ecgys, int sampr, int band50Switch, int band100Switch, int lowpassSwitch, int highpassSwitch, int smoothSwitch);//算法处理源数据
//extern "C" LIBRARY_API
/* 全局心电信号处理函数
输入值：
ecgys：原始全局心电信号
sampr：			心电信号采样率，分为 256 512 500 三种情况
band50Switch：	50Hz 带阻滤波器开关，0关闭，1开启；
band100Switch：	100Hz 带阻滤波器开关，0关闭，1开启；
lowpassSwitch：	低通滤波器开关，0关闭，1开启；
highpassSwitch：高通滤波器开关，0关闭，1开启；
smoothSwitch：	平滑滤波开关，0关闭，1开启；
返回值：
FileData 结构

普通滤波、增强滤波与滤波器开关的关系：
|				| 普通滤波 | 增强滤波 | 无滤波 |
|band50Switch	|	1	  |		1	|	0	|
|band100Switch	|	1	  |		1	|   0	|
|lowpassSwitch	|	1	  |		1	|   0	|
|highpassSwitch	|	1	  |		1	|   0	|
|smoothSwitch	|	0	  |		1	|   0	|

ecgys 长度与 section 及 sampr 的关系：
|section\sampr| 256 Hz		| 512/500 Hz	|
| 0		|		512 + 256	| 1024 + 512	|
| others|		512			| 1024			|
*/

ServerData fullanalysewithJson(double* data, int* Rpeaks, int* RRs, int* fastBeginIndex, int* fastEndIndex,
                               int* slowBeginIndex, int* slowEndIndex, int dataLen, int filterType, int sampr);
//extern "C" LIBRARY_API
/* 全局心电信号服务器接口函数
输入值：
*filedata：读取加密 dat 文件后的字符串；
filebytelen：*filedata 中的字节数
filterType：		 0: 无滤波 1：普通滤波 2：增强滤波
返回值：
ServerData 结构体
*/

EncryptData datSave(CryptData sourceData);
//extern "C" LIBRARY_API
/* 加密字符串生成函数 
输入值：
CryptData sourceData 加密前源数据结构体，内部包括 原始信号 滤波信号 R峰数组 采样率

返回值：
EncryptData包含如下：
unsigned char* 加密后的数据字符串
int& filebytelen 输出字符串的字节数
*/

CryptData datRead(unsigned char* cryptedData, int filebytelen);
//extern "C" LIBRARY_API 
//extern "C" CryptData datRead(unsigned char* cryptedData, int filebytelen);
/* 加密字符串读取函数
输入值：
unsigned char* cryptedData 加密后的数据字符串
int filebytelen	字符串的字节数

返回值：
CryptData 结构体
*/

char* getVersion();

//HealthResult hrvAnalyse(std::vector<double>& ecgys, int sampr, int band50Switch, int band100Switch, int lowpassSwitch, int highpassSwitch, int smoothSwitch);
/* HRV分析相关函数
输入值：
ecgys：原始全局心电信号
sampr：			心电信号采样率，分为 256 512 500 三种情况
band50Switch：	50Hz 带阻滤波器开关，0关闭，1开启；
band100Switch：	100Hz 带阻滤波器开关，0关闭，1开启；
lowpassSwitch：	低通滤波器开关，0关闭，1开启；
highpassSwitch：高通滤波器开关，0关闭，1开启；
smoothSwitch：	平滑滤波开关，0关闭，1开启；
返回值：
HealthResult 结构

普通滤波、增强滤波与滤波器开关的关系：
|				| 普通滤波 | 增强滤波 | 无滤波 |
|band50Switch	|	1	  |		1	|	0	|
|band100Switch	|	1	  |		1	|   0	|
|lowpassSwitch	|	1	  |		1	|   0	|
|highpassSwitch	|	1	  |		1	|   0	|
|smoothSwitch	|	0	  |		1	|   0	|

ecgys 长度与 section 及 sampr 的关系：
|section\sampr| 256 Hz		| 512/500 Hz	|
| 0		|		512 + 256	| 1024 + 512	|
| others|		512			| 1024			|
*/

//extern "C" HealthResult hrvAnalyseWithJson(double* data, int dataLen, int filterType, int sampr);
//extern "C" LIBRARY_API HealthResult hrvAnalyseWithJson(double* data, int dataLen, int filterType, int sampr);
/* HRV分析服务器接口函数
输入值：
*data：读取加密 dat 文件后的字符串；
dataLen：*filedata 中的字节数
filterType：		 0: 无滤波 1：普通滤波 2：增强滤波
返回值：
HealthResult 结构体
*/
#endif