#include "ServiceTrafficProfile.h"

ServiceTrafficProfile::ServiceTrafficProfile()
{

}

ServiceTrafficProfile::ServiceTrafficProfile(ServiceTrafficProfile::Profile profile)
{
    switch (profile)
    {
    case ServiceTrafficProfile::Profile::NOKIA:
        chracterTable_.jitter = 0;
        /* code */
        break;
    
    default:
        break;
    }
}
