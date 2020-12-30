package com.proton.ecgcard.algorithm.utils;

import com.proton.ecgcard.algorithm.BuildConfig;
import com.proton.ecgcard.algorithm.bean.AlgorithmResult;
import com.proton.ecgcard.algorithm.bean.RealECGData;

import java.util.List;

/**
 * Created by 王梦思 on 2017/7/21.
 * 算法处理
 */
public class FilterAlgorithmHelper {
    static {
        System.loadLibrary("ecgpatch");
        System.loadLibrary("ecgcardalgorithm");
        init(BuildConfig.DEBUG);
    }

    public static native void init(boolean isDebug);

    public static RealECGData processEcgData(List<Float> data, long section, int sample) {
        double[] doubles = new double[data.size()];
        for (int i = 0; i < data.size(); i++) {
            doubles[i] = data.get(i);
        }
        return processEcgData(doubles, section, sample);
    }

    public static RealECGData processEcgData(double[] doubles, long section, int sample) {
        return processEcgData(doubles, section, sample, 1, 1, 1, 1, 1);
    }

    /**
     * 滤波处理算法（用户版本）
     */
    public static native RealECGData processEcgData(double[] doubles, long section, int sample, int band50Switch, int band100Switch, int lowPassSwitch, int highPassSwitch, int smoothSwitch);

    /**
     * 滤波处理算法完整分析(用户板)
     */
    public static native AlgorithmResult fullAnalyse(double[] ecgDatas, int sample, int band50Switch, int band100Switch, int lowPassSwitch, int highPassSwitch, int smoothSwitch);
}
