package com.proton.ecgcard.algorithm.interfaces.impl;

import com.proton.decrypt.DecryptHelper;
import com.proton.ecgcard.algorithm.bean.RealECGData;
import com.proton.ecgcard.algorithm.callback.EcgPatchAlgorithmListener;
import com.proton.ecgcard.algorithm.utils.FilterAlgorithmHelper;
import com.proton.encrypt.EncryptHelper;

import java.util.ArrayList;
import java.util.List;

/**
 * @author 王梦思
 * @date 12/30/20 11:07 AM.
 */
@SuppressWarnings("unused")
public class EcgPatchAlgorithm extends EcgAlgorithm {
    private final EcgPatchAlgorithmListener algorithmListener;

    public EcgPatchAlgorithm(EcgPatchAlgorithmListener algorithmListener) {
        this.algorithmListener = algorithmListener;
    }

    @Override
    public void processEcgData(byte[] encryptEcgData) {
        mSourceData.addAll(DecryptHelper.decryptFilterData(encryptEcgData).getSourceDatas());
        int sourceDataSize = mSourceData.size();
        int dealDataSize = 512;
        int firstDealDataSize = 256 + dealDataSize;
        if (isFirst && sourceDataSize >= firstDealDataSize) {
            //滤波处理
            filterEcgData(new ArrayList<>(mSourceData.subList(0, firstDealDataSize)));
            isFirst = false;
        } else if (!isFirst && sourceDataSize > firstDealDataSize + dealDataSize * section) {
            //滤波处理
            filterEcgData(new ArrayList<>(mSourceData.subList(firstDealDataSize + dealDataSize * (section - 1), firstDealDataSize + dealDataSize * section)));
        }
    }

    /**
     * 滤波算法处理ecg原始数据
     */
    private void filterEcgData(final List<Float> dealingDataList) {
        final RealECGData processData = FilterAlgorithmHelper.processEcgData(dealingDataList, section++, 256);
        if (algorithmListener != null) {
            algorithmListener.signalInterference(processData.getSignalQuality());
            algorithmListener.receiverHeartRate(processData.getHeartRate());
            algorithmListener.receiveEcgFilterData(EncryptHelper.encryptData(processData.getEcgData()));
        }
    }
}
