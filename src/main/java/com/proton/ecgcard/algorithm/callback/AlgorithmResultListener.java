package com.proton.ecgcard.algorithm.callback;

import com.proton.ecgcard.algorithm.bean.AlgorithmResult;

/**
 * 算法结果
 */
public abstract class AlgorithmResultListener {
    /**
     * 返回算法分析结果
     */
    public void receiveAlgorithmResult(AlgorithmResult result) {
    }
}