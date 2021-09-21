#include "QoSProfile.h"

#include <QDebug>
#include <QPair>

QoSProfile::QoSProfile()
{

}


void QoSProfile::set5QIValue(int value)
{
    switch(value) {
        // GBR
        case 1 : 
            config(1,   true, 20, 100,     0.01, 0, 2000); 
            break;                                              
        case 2 : 
            config(2,   true, 40, 150,    0.001, 0, 2000); 
            break;
        case 3 : 
            config(3,   true, 30,  50,    0.001, 0, 2000); 
            break; 
        case 4 : 
            config(4,   true, 50, 300, 0.000001, 0, 2000); 
            break;   
        case 65 : 
            config(65, true,  7,  75,     0.01, 0, 2000); 
            break; 
        case 66 : 
            config(66, true, 20, 100,    0.001, 0, 2000); 
            break; 
        case 67 : 
            config(67, true, 15, 100,    0.001, 0, 2000); 
            break; 
        case 75 : 
            qDebug() << "QoSProfile : for now it is empty"; 
            break;  
        case 71 : 
            config(71, true, 56, 150,   0.000001, 0, 2000);
            break;  
        case 72 : 
            config(72, true, 56, 300,     0.0001, 0, 2000);
            break;  
        case 73 : 
            config(73, true, 56, 150, 0.00000001, 0, 2000);
            break;  
        case 74 : 
            config(74, true, 56, 500, 0.00000001, 0, 2000); 
            break; 
        case 76 : 
            config(76, true, 56, 500,     0.0001, 0, 2000); 
            break; 
        // Non-GBR
        case 5 : 
            config(5,  false, 10, 100, 0.000001, 0, 0); 
            break;  
        case 6 : 
            config(6,  false, 60, 300, 0.000001, 0, 0); 
            break;  
        case 7 : 
            config(7,  false, 70, 100,    0.001, 0, 0); 
            break;  
        case 8 : 
            config(8,  false, 80, 300, 0.000001, 0, 0); 
            break;  
        case 9 : 
            config(9,  false, 90, 300, 0.000001, 0, 0); 
            break;  
        case 69: 
            config(69, false,  5,  60, 0.000001, 0, 0); 
            break;  
    }
}

void QoSProfile::config(
                        int id,
                        bool gbrNgbr,
                        int priority,
                        double delayBudget,
                        float packetErrorRate,
                        int dataBurstVolume,
                        int defaultAveragingWindow
                        )
{
    id_ = id;
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

void QoSProfile::showProfile()
{
    qDebug() << "5QI Value: " << getId();
    qDebug() << "Resource Type: " << getGbrNbr();
    qDebug() << "Default Priority Level: " << getPriority();
    qDebug() << "Packet Delay Budget: " << getDelayBudget();
    qDebug() << "Packet Error Rate: " << getPacketErrorRate();
    qDebug() << "Default Maximum Data Burst Volume: " << getDataBurstVolume();
    qDebug() << "Default Averaging Window: " << getDefaultAveragingWindow();
}