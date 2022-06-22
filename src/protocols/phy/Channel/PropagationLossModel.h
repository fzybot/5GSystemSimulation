#pragma once


class PropagationLossModel
{

public:
    enum class PropagationModel
    {
      RMA_LOS,
      RMA_NLOS,
      UMA_LOS,
      UMA_NLOS,
      UMI_LOS,
      UMI_NLOS,
      INH_LOS,
      INH_NLOS,
      INF_LOS,
      INF_NLOS_SL,
      INF_NLOS_DL,
      INF_NLOS_SH,
      INF_NLOS_DH,
      COST231_HATA,
      FREE_SPACE
    };

public:
    PropagationLossModel::PropagationModel _propagationModel;

public:
    PropagationLossModel(PropagationLossModel::PropagationModel model);

    double calculateLosses( double distance2Dout,
                            double distance2Din,
                            double heightBS,
                            double heightUT,
                            double centerFrequency,
                            double h,
                            double W,
                            double shadowFading );
};
