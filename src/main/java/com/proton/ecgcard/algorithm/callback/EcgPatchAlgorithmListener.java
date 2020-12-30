package com.proton.ecgcard.algorithm.callback;

/**
 * @author 王梦思
 * @date 12/30/20 11:08 AM.
 */
public class EcgPatchAlgorithmListener {
    /**
     * 信号是否干扰
     *
     * @param signalQualityIndex 0 Pvalue<2.5, 1 2.5<=Pvalue<4, 2 Pvalue>4
     *                           0，信号质量好, 1，信号质量差, 2，信号质量差，数据没有意义
     */
    public void signalInterference(int signalQualityIndex) {
    }

    /**
     * 实时心率
     *
     * @param rate 算法处理后的数据集大小
     */
    public void receiverHeartRate(int rate) {
    }

    /**
     * 接收ecg滤波处理后数据
     *
     * @param ecgData 加密后的滤波数据
     */
    public void receiveEcgFilterData(byte[] ecgData) {
    }
}
