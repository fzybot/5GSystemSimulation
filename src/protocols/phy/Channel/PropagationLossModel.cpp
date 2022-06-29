#include "PropagationLossModel.h"
#include "src/protocols/phy/Channel/propagationModels.h"

PropagationLossModel::PropagationLossModel(PropagationLossModel::PropagationModel model)
{
    _propagationModel = model;
}

double PropagationLossModel::calculateLosses(   double distance2Dout,
                                                double distance2Din,
                                                double heightBS,
                                                double heightUT,
                                                double centerFrequency,
                                                double h,
                                                double W,
                                                double shadowFading )
{
    double loss = 0;
    switch (_propagationModel)
    {
        case PropagationLossModel::PropagationModel::RMA_LOS:
            loss = RMa_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::RMA_NLOS:
            loss = RMa_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMA_LOS:
            loss = UMa_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMA_NLOS:
            loss = UMa_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMI_LOS:
            loss = UMi_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMI_NLOS:
            loss = UMi_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INH_LOS:
            loss = InH_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INH_NLOS:
            loss = InH_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_LOS:
            loss = InF_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_SL:
            loss = InF_NLOS_SL(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_DL:
            loss = InF_NLOS_DL(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_SH:
            loss = InF_NLOS_SH(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_DH:
            loss = InF_NLOS_DH(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::COST231_HATA:
            loss = COST231_Hata(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::FREE_SPACE:
            loss = Free_space(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
    }
    return loss;
}
