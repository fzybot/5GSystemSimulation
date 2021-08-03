#pragma once


class CartesianCoordinates
{
private:
    // Position. Should be used to draw an image (for heatmap).
    double posX_;
    double posY_;
    double posZ_;

    // Angles
    double angleX_;
    double angleY_;
    double angleZ_;

    // Geographical coordinates
    double altitude_;
    double longtitude_;
    double latitude_;

public:
// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
    CartesianCoordinates();
    CartesianCoordinates(double x, double y, double z);
    CartesianCoordinates(double x, double y, double z, double angX, double angY, double angZ);

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setCoordintes(double x, double y, double z);
    void setAngles(double angX, double angY, double angZ);

    void setCoordinateX(double x);
    void setCoordinateY(double y);
    void setCoordinateZ(double z);

    double getCoordinateX();
    double getCoordinateY();
    double getCoordinateZ();

    void setAngleX(double angX);
    void setAngleY(double angY);
    void setAngleZ(double angZ);

    double getAngleX();
    double getAngleY();
    double getAngleZ();

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
    // TODO: make tests for operators
    CartesianCoordinates* operator + (CartesianCoordinates *A);
    CartesianCoordinates* operator - (CartesianCoordinates *B);
    bool operator == (CartesianCoordinates C);

    double calculateDistance3D(CartesianCoordinates *remoteEquipment);

    // TODO: calculate distance for sphere
    double calculateDistanceSphere(CartesianCoordinates *remoteEquipment);

    // TODO: Need a method is able to transform from Cartesian to Geographical position.
    void transformToLatLon();

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
    void print();
    
};
