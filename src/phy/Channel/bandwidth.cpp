#include "bandwidth.h"




Bandwidth::Bandwidth(double ulBw, double dlBw, int ulOffset, int dlOffset,
                     bool tddTrue)
{
    if(tddTrue == true){
        tddTrue = true;
        // TODO: Check the specification for TDD bandwidth calculation based
        // on Dl and UL bandwidths
    }
    else{
        this->m_ulBandwidth = ulBw;
        this->m_dlBandwidth = dlBw;
    }
    m_ulOffsetBw = ulOffset;
    m_dlOffsetBw = dlOffset;



}
