package com.proton.ecgcard.algorithm.bean;

import java.util.ArrayList;
import java.util.List;

public class RealECGData {
    /**
     * 实时心电信号
     */
    private List<Float> ecgData = new ArrayList<>();
    /**
     * 实时心率值
     */
    private int heartRate;
    /**
     * 信号质量指标：0 Pvalue<2.5, 1 2.5<=Pvalue<4, 2 Pvalue>4
     */
    private int signalQuality;
    /**
     * 实时心电分段编号 从 0 开始计数
     */
    private long section;
    /**
     * 实时呼吸
     */
    private int breath;

    public RealECGData() {
    }

    public RealECGData(List<Float> ecgData) {
        this.ecgData = ecgData;
    }

    public List<Float> getEcgData() {
        return ecgData;
    }

    public void setEcgData(List<Float> ecgData) {
        this.ecgData = ecgData;
    }

    public int getHeartRate() {
        return heartRate;
    }

    public void setHeartRate(int heartRate) {
        this.heartRate = heartRate;
    }

    public int getSignalQuality() {
        return signalQuality;
    }

    public void setSignalQuality(int signalQuality) {
        this.signalQuality = signalQuality;
    }

    public long getSection() {
        return section;
    }

    public void setSection(long section) {
        this.section = section;
    }

    public int getBreath() {
        return breath;
    }

    public void setBreath(int breath) {
        this.breath = breath;
    }
}
