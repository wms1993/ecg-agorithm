package com.proton.ecgcard.algorithm.bean;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by 王梦思 on 2018/7/7.
 * 算法结果
 */
public class AlgorithmResult implements Serializable {
    /**
     * 滤波心电数据
     */
    private List<Float> filterDatas = new ArrayList<>();
    /**
     * 心电原始数据
     */
    private List<Float> sourceDatas = new ArrayList<>();
    /**
     * 实时心率
     */
    private int heartRate;
    /**
     * 心动过速时间，单位毫秒
     */
    private long heartFastTime;
    /**
     * 心动过缓时间，单位毫秒
     */
    private long heartSlowTime;
    private List<Integer> peakSums = new ArrayList<>();
    /**
     * R峰总数
     */
    private int peaksum;
    /**
     * 用于表征正常(0)、心动过缓(1)、心动过速(2)
     */
    private int heartPace;
    /**
     * 最高心率
     */
    private int highestRate;
    /**
     * 最低心率
     */
    private int lowestRate;
    /**
     * 最快心率发生时刻 ms
     */
    private int maxHRTime;
    /**
     * 最慢心率发生时刻 ms
     */
    private int minHRTime;
    /**
     * 最长心动过缓连续心拍数
     */
    private int heartSlowMaxBeat;
    /**
     * 最长心动过缓时刻 ms
     */
    private int heartSlowMaxTime;
    /**
     * 最长心动过速连续心拍数
     */
    private int heartFastMaxBeat;
    /**
     * 最长心动过速时刻 ms
     */
    private int heartFastMaxTime;

    public void setPeakSums(List<Integer> peakSums) {
        this.peakSums = peakSums;
    }

    public int getMaxHRTime() {
        return maxHRTime;
    }

    public void setMaxHRTime(int maxHRTime) {
        this.maxHRTime = maxHRTime;
    }

    public int getMinHRTime() {
        return minHRTime;
    }

    public void setMinHRTime(int minHRTime) {
        this.minHRTime = minHRTime;
    }

    public int getHeartSlowMaxBeat() {
        return heartSlowMaxBeat;
    }

    public void setHeartSlowMaxBeat(int heartSlowMaxBeat) {
        this.heartSlowMaxBeat = heartSlowMaxBeat;
    }

    public int getHeartSlowMaxTime() {
        return heartSlowMaxTime;
    }

    public void setHeartSlowMaxTime(int heartSlowMaxTime) {
        this.heartSlowMaxTime = heartSlowMaxTime;
    }

    public int getHeartFastMaxBeat() {
        return heartFastMaxBeat;
    }

    public void setHeartFastMaxBeat(int heartFastMaxBeat) {
        this.heartFastMaxBeat = heartFastMaxBeat;
    }

    public int getHeartFastMaxTime() {
        return heartFastMaxTime;
    }

    public void setHeartFastMaxTime(int heartFastMaxTime) {
        this.heartFastMaxTime = heartFastMaxTime;
    }

    public int getHeartRate() {
        return heartRate;
    }

    public void setHeartRate(int heartRate) {
        this.heartRate = heartRate;
    }

    public long getHeartFastTime() {
        return heartFastTime;
    }

    public void setHeartFastTime(long heartFastTime) {
        this.heartFastTime = heartFastTime;
    }

    public long getHeartSlowTime() {
        return heartSlowTime;
    }

    public void setHeartSlowTime(long heartSlowTime) {
        this.heartSlowTime = heartSlowTime;
    }

    public List<Integer> getPeakSums() {
        return peakSums;
    }

    public void setPeak(List<Integer> peakSums) {
        this.peakSums = peakSums;
    }

    public int getPeaksum() {
        return peaksum;
    }

    public void setPeaksum(int peaksum) {
        this.peaksum = peaksum;
    }

    public List<Float> getFilterDatas() {
        return filterDatas;
    }

    public void setFilterDatas(List<Float> filterDatas) {
        this.filterDatas = filterDatas;
    }

    public List<Float> getSourceDatas() {
        return sourceDatas;
    }

    public void setSourceDatas(List<Float> sourceDatas) {
        this.sourceDatas = sourceDatas;
    }

    public int getHeartPace() {
        return heartPace;
    }

    public void setHeartPace(int heartPace) {
        this.heartPace = heartPace;
    }

    public int getHighestRate() {
        return highestRate;
    }

    public void setHighestRate(int highestRate) {
        this.highestRate = highestRate;
    }

    public int getLowestRate() {
        return lowestRate;
    }

    public void setLowestRate(int lowestRate) {
        this.lowestRate = lowestRate;
    }

    @Override
    public String toString() {
        return "AlgorithmResult{" +
                ", heartRate=" + heartRate +
                ", heartFastTime=" + heartFastTime +
                ", heartSlowTime=" + heartSlowTime +
                ", peakSums=" + peakSums +
                ", peaksum=" + peaksum +
                ", heartPace=" + heartPace +
                ", highestRate=" + highestRate +
                ", lowestRate=" + lowestRate +
                ", maxHRTime=" + maxHRTime +
                ", minHRTime=" + minHRTime +
                ", heartSlowMaxBeat=" + heartSlowMaxBeat +
                ", heartSlowMaxTime=" + heartSlowMaxTime +
                ", heartFastMaxBeat=" + heartFastMaxBeat +
                ", heartFastMaxTime=" + heartFastMaxTime +
                '}';
    }
}
