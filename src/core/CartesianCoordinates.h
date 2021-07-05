#pragma once


class CartesianCoordinates
{
public:
    CartesianCoordinates();
    CartesianCoordinates(double x, double y, double z);
    CartesianCoordinates(double x, double y, double z, double angX, double angY, double angZ);

    void setCoordintes(double x, double y, double z);
    void setAngles(double angX, double angY, double angZ);

    double calculateDistance3D(CartesianCoordinates *remoteEquipment);
    // TODO: calculate distance for sphere
    double calculateDistanceSphere(CartesianCoordinates *remoteEquipment);


    double getCoordinateX();
    double getCoordinateY();
    double getCoordinateZ();

    void setCoordinateX(double x);
    void setCoordinateY(double y);
    void setCoordinateZ(double z);

    void setCoordinateAngleX(double angX);
    void setCoordinateAngleY(double angY);
    void setCoordinateAngleZ(double angZ);

    // TODO: Need a method is able to transform from Cartesian to Geographical position.
    void transformToLatLon();



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
    double altitude_ = 0;
    double longtitude_;
    double latitude_;

    double lonAngle_ = 0;
    double latAngle_ = 0;
    double altAngle_ = 0;
};
