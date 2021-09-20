#include "QoSProfile.h"

QoSProfile::QoSProfile()
{

}


void QoSProfile::set5QIValue(int value)
{
    switch(value) {
        case 1 : config(true, 20, 100,     0.01, 0, 2000); // Conveerational Voice
        case 2 : config(true, 40, 150,    0.001, 0, 2000); // Conversational Video
        case 3 : config(true, 30,  50,    0.001, 0, 2000); // 
        case 4 : config(true, 50, 300, 0.000001, 0, 2000); // 
        
        case 65 : config(true,  7,  75,     0.01, 0, 2000); // 
        case 66 : config(true, 20, 100,    0.001, 0, 2000); // 
        case 67 : config(true, 15, 100,    0.001, 0, 2000); // 
        case 71 : config(true, 56, 150, 0.000001, 0, 2000); // 
        
        case 5 : config(false, 10, 100, 0.000001, 0, 0); // 
        case 6 : config(false, 60, 300, 0.000001, 0, 0); // 
        case 7 : config(false, 70, 100,    0.001, 0, 0); // 
        case 8 : config(false, 80, 300, 0.000001, 0, 0); // 
        case 9 : config(false, 90, 300, 0.000001, 0, 0); // 

        /*
            NOTE 1: A packet which is delayed more than PDB is not counted as lost, thus not included in the PER.
            NOTE 2: It is required that default MDBV is supported by a PLMN supporting the related 5QIs.
            NOTE 3: The Maximum Transfer Unit (MTU) size considerations in clause 9.3 and Annex C of TS 23.060 [56] are also
            applicable. IP fragmentation may have impacts to CN PDB, and details are provided in clause 5.6.10.
            NOTE 4: A static value for the CN PDB of 1 ms for the delay between a UPF terminating N6 and a 5G-AN should be
            subtracted from a given PDB to derive the packet delay budget that applies to the radio interface. When a
            dynamic CN PDB is used, see clause 5.7.3.4.
            NOTE 5: A static value for the CN PDB of 2 ms for the delay between a UPF terminating N6 and a 5G-AN should be
            subtracted from a given PDB to derive the packet delay budget that applies to the radio interface. When a
            dynamic CN PDB is used, see clause 5.7.3.4.
            NOTE 6: A static value for the CN PDB of 5 ms for the delay between a UPF terminating N6 and a 5G-AN should be
            subtracted from a given PDB to derive the packet delay budget that applies to the radio interface. When a
            dynamic CN PDB is used, see clause 5.7.3.4.
            NOTE 7: For Mission Critical services, it may be assumed that the UPF terminating N6 is located "close" to the 5G_AN
            (roughly 10 ms) and is not normally used in a long distance, home routed roaming situation. Hence a static
            value for the CN PDB of 10 ms for the delay between a UPF terminating N6 and a 5G_AN should be
            subtracted from this PDB to derive the packet delay budget that applies to the radio interface.
            NOTE 8: In both RRC Idle and RRC Connected mode, the PDB requirement for these 5QIs can be relaxed (but not to
            a value greater than 320 ms) for the first packet(s) in a downlink data or signalling burst in order to permit
            reasonable battery saving (DRX) techniques.
            NOTE 9: It is expected that 5QI-65 and 5QI-69 are used together to provide Mission Critical Push to Talk service (e.g.
            5QI-5 is not used for signalling). It is expected that the amount of traffic per UE will be similar or less
            compared to the IMS signalling.
            NOTE 10: In both RRC Idle and RRC Connected mode, the PDB requirement for these 5QIs can be relaxed for the first
            packet(s) in a downlink data or signalling burst in order to permit battery saving (DRX) techniques.
            NOTE 11: In RRC Idle mode, the PDB requirement for these 5QIs can be relaxed for the first packet(s) in a downlink
            data or signalling burst in order to permit battery saving (DRX) techniques.
            NOTE 12: This 5QI value can only be assigned upon request from the network side. The UE and any application
            running on the UE is not allowed to request this 5QI value.
            NOTE 13: A static value for the CN PDB of 20 ms for the delay between a UPF terminating N6 and a 5G-AN should be
            subtracted from a given PDB to derive the packet delay budget that applies to the radio interface.
            NOTE 14: This 5QI is not supported in this Release of the specification as it is only used for transmission of V2X
            messages over MBMS bearers as defined in TS 23.285 [72] but the value is reserved for future use.
            NOTE 15: For "live" uplink streaming (see TS 26.238 [76]), guidelines for PDB values of the different 5QIs correspond to
            the latency configurations defined in TR 26.939 [77]. In order to support higher latency reliable streaming
            services (above 500ms PDB), if different PDB and PER combinations are needed these configurations will
            have to use non-standardised 5QIs.
            NOTE 16: These services are expected to need much larger MDBV values to be signalled to the RAN. Support for such
            larger MDBV values with low latency and high reliability is likely to require a suitable RAN configuration, for
            which, the simulation scenarios in TR 38.824 [112] may contain some guidance.
            NOTE 17: The worst case one way propagation delay for GEO satellite is expected to be ~270ms, ,~ 21 ms for LEO at
            1200km, and 13 ms for LEO at 600km. The UL scheduling delay that needs to be added is also typically 1
            RTD e.g. ~540ms for GEO, ~42ms for LEO at 1200km, and ~26 ms for LEO at 600km. Based on that, the
            5G-AN Packet delay budget is not applicable for 5QIs that require 5G-AN PDB lower than the sum of these
            values when the specific types of satellite access are used (see TS 38.300 [27]). 5QI-<New Value> can
            accommodate the worst case PDB for GEO satellite type.
        */

    }
}

void QoSProfile::config(
                        bool gbrNgbr,
                        int priority,
                        double delayBudget,
                        float packetErrorRate,
                        int dataBurstVolume,
                        int defaultAveragingWindow
                        )
{
    gbrNgbr_ = gbrNgbr;
    priority_ = priority;
    delayBudget_ = delayBudget;
    packetErrorRate_ = packetErrorRate;
    dataBurstVolume_ = dataBurstVolume;
    defaultAveragingWindow_ = defaultAveragingWindow;
}

int QoSProfile::getId()
{
    return id_;
}

bool QoSProfile::getGbrNbr()
{
    return gbrNgbr_;
}

int QoSProfile::getPriority()
{
    return priority_;
}

int QoSProfile::getDelayBudget()
{
    return delayBudget_;
}

float QoSProfile::getPacketErrorRate()
{
    return packetErrorRate_;
}

int QoSProfile::getDataBurstVolume()
{
    return dataBurstVolume_;
}

int QoSProfile::getDefaultAveragingWindow()
{
    return defaultAveragingWindow_;
}