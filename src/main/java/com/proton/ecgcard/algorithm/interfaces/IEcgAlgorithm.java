package com.proton.ecgcard.algorithm.interfaces;

import com.proton.ecgcard.algorithm.bean.AlgorithmResult;
import com.proton.ecgcard.algorithm.callback.AlgorithmResultListener;

import java.util.List;

/**
 * Created by 王梦思 on 2017/8/8.
 */

public interface IEcgAlgorithm {
    /**
     * 滤波处理算法
     */
    void processEcgData(byte[] encryptEcgData);

    /**
     * 滤波处理算法完整分析(异步)
     */
    void fullAnalyse(List<Float> ecgDatas, int sample, int band50Switch, int band100Switch, int lowpassSwitch, int highpassSwitch, int smoothSwitch, AlgorithmResultListener listener);

    /**
     * 滤波处理算法完整分析(同步)
     */
    AlgorithmResult fullAnalyse(List<Float> ecgDatas, int sample, int band50Switch, int band100Switch, int lowpassSwitch, int highpassSwitch, int smoothSwitch);
}
