#pragma once

// The TrafficProfile class is aimed to create a rules for packet generation

class ServiceTrafficProfile
{
public:
    enum class Profile
    {
      NOKIA,
      MODEL_1
    };

public:
    struct Characteristics {
        int jitter;
        int lowDataVolume; // [Bytes]
        int highDataVolume; // [Bytes]
        int periodicity; // [ms]
    };

protected:

    ServiceTrafficProfile::Characteristics chracterTable_;

public:
    ServiceTrafficProfile();
    ServiceTrafficProfile(ServiceTrafficProfile::Profile profile);
};

