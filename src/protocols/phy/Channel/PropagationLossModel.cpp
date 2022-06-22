#include "PropagationLossModel.h"
#include "src/protocols/phy/Channel/propagationModels.h"

PropagationLossModel::PropagationLossModel(PropagationLossModel::PropagationModel model)
{

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

    switch (_propagationModel)
    {
        case PropagationLossModel::PropagationModel::RMA_LOS:
            RMa_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::RMA_NLOS:
            RMa_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMA_LOS:
            UMa_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMA_NLOS:
            UMa_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMI_LOS:
            UMi_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::UMI_NLOS:
            UMi_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INH_LOS:
            InH_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INH_NLOS:
            InH_NLOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_LOS:
            InF_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_SL:
            InF_NLOS_SL(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_DL:
            InF_NLOS_DL(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_SH:
            InF_NLOS_SH(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::INF_NLOS_DH:
            InF_NLOS_DH(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::COST231_HATA:
            COST231_Hata(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            break;
        case PropagationLossModel::PropagationModel::FREE_SPACE:
            Free_space(distance2Dout, centerFrequency);
            break;
    }
}
