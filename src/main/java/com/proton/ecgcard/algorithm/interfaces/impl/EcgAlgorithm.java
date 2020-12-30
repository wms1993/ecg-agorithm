package com.proton.ecgcard.algorithm.interfaces.impl;

import android.os.Handler;
import android.os.Looper;

import com.proton.ecgcard.algorithm.bean.AlgorithmResult;
import com.proton.ecgcard.algorithm.callback.AlgorithmResultListener;
import com.proton.ecgcard.algorithm.interfaces.IEcgAlgorithm;
import com.proton.ecgcard.algorithm.utils.FilterAlgorithmHelper;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by 王梦思 on 2017/8/8.
 * 算法处理实现
 */
abstract class EcgAlgorithm implements IEcgAlgorithm {
    private final Handler mainHandler = new Handler(Looper.getMainLooper());
    /**
     * 未处理过的数据
     */
    protected final List<Float> mSourceData = new ArrayList<>();
    /**
     * 第一次处理数据
     */
    protected boolean isFirst = true;
    /**
     * 第几次处理数据（供算法使用）
     */
    protected int section;

    @Override
    public void fullAnalyse(final List<Float> ecgDatas, final int sample, final int band50Switch, final int band100Switch, final int lowPassSwitch, final int highPassSwitch, final int smoothSwitch, final AlgorithmResultListener listener) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                final AlgorithmResult result = fullAnalyse(ecgDatas, sample, band50Switch, band100Switch, lowPassSwitch, highPassSwitch, smoothSwitch);
                mainHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (result != null && listener != null) {
                            listener.receiveAlgorithmResult(result);
                        }
                    }
                });
            }
        }).start();
    }

    @Override
    public AlgorithmResult fullAnalyse(List<Float> ecgDatas, final int sample, final int band50Switch, final int band100Switch, final int lowPassSwitch, final int highPassSwitch, final int smoothSwitch) {
        final List<Float> ecgSourceData = new ArrayList<>(ecgDatas);
        double[] ecgDatasArr = new double[ecgSourceData.size()];
        for (int i = 0; i < ecgDatasArr.length; i++) {
            ecgDatasArr[i] = ecgSourceData.get(i);
        }
        AlgorithmResult result = FilterAlgorithmHelper.fullAnalyse(ecgDatasArr, sample, band50Switch, band100Switch, lowPassSwitch, highPassSwitch, smoothSwitch);
        ecgSourceData.clear();
        return result;
    }
}
