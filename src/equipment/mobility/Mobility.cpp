#include <QDebug>
#include "Mobility.h"
#include "src/debug.h"

// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Mobility::Mobility()
{
    setSpeed(1);
    setAngle(1);
    interval_ = 0.;
    lastTimeDirectionChange_ = 0.;
    positionLastUpdate_ = 0;
    sumAngle_ = 0.;
    sumSpeed_ = 0.;
    changeCount_ = 0;
    averageSpeed_ = 0.;
    averageAngle_ = 0.;
    moveToPosition_ = nullptr;
}

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void Mobility::setEquipment(Equipment *equipment)
{
    equipment_ = equipment;
}

Equipment* Mobility::getEquipment(void) const
{
    return equipment_;
}

void Mobility::setModel(Model model)
{
    model_ = model;
}

Mobility::Model Mobility::getModel(void) const
{
    return model_;
}
void Mobility::setPosition(CartesianCoordinates *position)
{
    debug("Mobility: setting position");

    // if (position == nullptr) {
    //     currentPosition_ = nullptr;
    // }
    // if (currentPosition_ == nullptr) {
    //     currentPosition_ = new CartesianCoordinates();
    // }

    currentPosition_ = new CartesianCoordinates();
    currentPosition_->setCoordintes(position->getCoordinateX(), position->getCoordinateY(), position->getCoordinateZ());
    debug("Mobility: currentPosition_:", currentPosition_);
}

CartesianCoordinates* Mobility::getPosition(void) const
{
    return currentPosition_;
}

void Mobility::setSpeed(int speed)
{
    speed_ = speed;
}

int Mobility::getSpeed()
{
    return speed_;
}

void Mobility::setAngle(double angle)
{
    angle_ = angle;
}

double Mobility::getAngle()
{
    return angle_;
}

void Mobility::setPositionLastUpdate(double time)
{
    positionLastUpdate_ = time;
}

double Mobility::getPositionLastUpdate() const
{
    return positionLastUpdate_;
}

void Mobility::setAlpha(double alpha)
{
    alpha_ = alpha;
}

double Mobility::getAlpha()
{
    return alpha_;
}

void Mobility::setBorders(double top, double bottom, double left, double right)
{
    topBorder_ = top;
    bottomBorder_ = bottom;
    leftBorder_ = left;
    rightBorder_ = right;
}

void Mobility::setBorderZone(double zone)
{
    borderZone_ = zone;
}

int Mobility::isInZone(CartesianCoordinates *position)
{
    if(position->getCoordinateY() < bottomBorder_ + borderZone_ &&
            position->getCoordinateX() < leftBorder_ + borderZone_){
        return 1;
    }
    if(position->getCoordinateY() > topBorder_ - borderZone_ &&
            position->getCoordinateX() < leftBorder_ + borderZone_){
        return 3;
    }
    if(position->getCoordinateY() > topBorder_ - borderZone_ &&
            position->getCoordinateX() > rightBorder_ - borderZone_){
        return 5;
    }
    if(position->getCoordinateY() < bottomBorder_ + borderZone_ &&
            position->getCoordinateX() < leftBorder_ + borderZone_){
        return 7;
    }

    if(position->getCoordinateX() < leftBorder_ + borderZone_){
        return 2;
    }
    if(position->getCoordinateY() > topBorder_ - borderZone_){
        return 4;
    }
    if(position->getCoordinateX() > rightBorder_ - borderZone_){
        return 6;
    }
    if(position->getCoordinateY() < bottomBorder_ + borderZone_){
        return 8;
    }

    return 0;

}

void Mobility::setMaxSpeed(int max)
{
    speedMax_ = max;
}

void Mobility::setMinSpeed(int min)
{
    speedMin_ = min;
}

void Mobility::forceStayInArea(CartesianCoordinates *position)
{
    if(position->getCoordinateX() > rightBorder_) position->setCoordinateX(rightBorder_);
    if(position->getCoordinateX() < leftBorder_) position->setCoordinateX(leftBorder_);
    if(position->getCoordinateY() > topBorder_) position->setCoordinateY(topBorder_);
    if(position->getCoordinateY() < bottomBorder_) position->setCoordinateY(bottomBorder_);
}

void Mobility::setMovePosition(double lon, double lat)
{
    if(moveToPosition_ != nullptr) delete moveToPosition_;
    moveToPosition_ = new CartesianCoordinates(lon, lat, 0);
}

void Mobility::setPauseTime(double pauseTime)
{
    tempPauseTime_ = pauseTime_ = pauseTime;
}

void Mobility::deletePosition()
{
    delete currentPosition_;
    delete startPosition_;
}

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
void Mobility::updatePosition(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com

    switch (model_) {
    case Model::CONSTANT_POSITION: break;
    case Model::RANDOM_DIRECTION:
        modelRandomDirection(time);
        break;
    case Model::RANDOM_WALK:
        modelRandomWalk(time);
        break;
    case Model::RANDOM_WAYPOINT:
        modelRandomWaypoint(time);
        break;
    case Model::MANHATTAN:
        modelManhattan(time);
        break;
    case Model::LINEAR_MOVEMENT:
        modelLinearMovement(time);
        break;
    case Model::GAUSS_MARKOV:
        modelGaussMarkov(time);
        break;
    }
}

void Mobility::modelRandomDirection(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com

    if(isInZone(getPosition())){

        switch (isInZone(getPosition())) {
        case 1:
            setAngle(((float)rand()/(float)RAND_MAX)*M_PI/2);
            break;
        case 2:
            setAngle(((float)rand()/(float)RAND_MAX)*M_PI - M_PI/2);
            break;
        case 3:
            setAngle(((float)rand()/(float)RAND_MAX)*M_PI/2 - M_PI/2);
            break;
        case 4:
            setAngle(((float)rand()/(float)RAND_MAX)*(-M_PI));
            break;
        case 5:
            setAngle(((float)rand()/(float)RAND_MAX)*M_PI/2 + M_PI);
            break;
        case 6:
            setAngle(((float)rand()/(float)RAND_MAX)*M_PI + M_PI/2);
            break;
        case 7:
            setAngle(((float)rand()/(float)RAND_MAX)*M_PI/2 + M_PI/2);
            break;
        case 8:
            setAngle(((float)rand()/(float)RAND_MAX)*M_PI);
            break;
        }


        setSpeed(rand()%speedMax_ + speedMin_);
    }

        double timeInterval = time - getPositionLastUpdate();

        double shift = timeInterval * (getSpeed()*(1000.0/3600.0));

        double shift_y = shift * sin(getAngle());
        double shift_x = shift * cos(getAngle());

        CartesianCoordinates *newPosition = new CartesianCoordinates(getPosition()->getCoordinateX() + shift_x,
                                                                     getPosition()->getCoordinateY() + shift_y,
                                                                     getPosition()->getCoordinateZ());
        forceStayInArea(newPosition);
        setPosition(newPosition);
        delete newPosition;
        setPositionLastUpdate(time);



}
void Mobility::modelRandomWalk(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com

    setAngle(((float)rand()/(float)RAND_MAX)*2*M_PI + 0);
    setSpeed(rand()%speedMax_ + speedMin_);

    if(getSpeed()==0){
        qDebug() << "speed =0 --> position has not been updated!" << endl;
        return;
    }

    double timeInterval = time - getPositionLastUpdate();

    double shift = timeInterval * (getSpeed()*(1000.0/3600.0));

    if(isInZone(getPosition())!=0){
        switch (isInZone(getPosition())) {
        case 1:
            setAngle(M_PI/4);
            break;
        case 2:
            setAngle(0);
            break;
        case 3:
            setAngle(-M_PI/4);
            break;
        case 4:
            setAngle(-M_PI/2);
            break;
        case 5:
            setAngle(5*M_PI/4);
            break;
        case 6:
            setAngle(M_PI);
            break;
        case 7:
            setAngle(3*M_PI/4);
            break;
        case 8:
            setAngle(M_PI/2);
            break;
        }
    }

    double shift_y = shift * sin(getAngle());
    double shift_x = shift * cos(getAngle());

    ///
    CartesianCoordinates *newPosition = new CartesianCoordinates(getPosition()->getCoordinateX() + shift_x,
                                                                 getPosition()->getCoordinateY() + shift_y,
                                                                 getPosition()->getCoordinateZ());
    forceStayInArea(newPosition);
    setPosition(newPosition);
    delete newPosition;
    setPositionLastUpdate(time);
}
void Mobility::modelRandomWaypoint(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
    double dLat, dLon;

    if(getPositionLastUpdate() == 0){
        setMovePosition(getPosition()->getCoordinateX(),
                        getPosition()->getCoordinateY());
          tempPauseTime_ = pauseTime_;
    }

    if(fabs(getPosition()->getCoordinateX() - moveToPosition_->getCoordinateX())<0.001 &&
            fabs(getPosition()->getCoordinateY() - moveToPosition_->getCoordinateY())<0.001){
        if(tempPauseTime_ > 0){
            tempPauseTime_ -= time - getPositionLastUpdate();
        }
        if(tempPauseTime_ <= 0){
            setMovePosition(((float)rand()/(float)RAND_MAX) * (rightBorder_ - leftBorder_) + leftBorder_,
                            ((float)rand()/(float)RAND_MAX) * (topBorder_ - bottomBorder_) + bottomBorder_);

            dLat = (moveToPosition_->getCoordinateY() - getPosition()->getCoordinateY());
            dLon = (moveToPosition_->getCoordinateX() - getPosition()->getCoordinateX());

            if(dLon > 0){
                if(dLat < 0){
                    setAngle(atan(dLat/dLon));
                }
                else if(dLat > 0){
                    setAngle(atan(dLat/dLon));
                }
            }
            else if(dLon < 0){
                if(dLat > 0){
                    setAngle(atan(dLat/dLon) + M_PI);
                }
                else if(dLat < 0){
                    setAngle(atan(dLat/dLon) + M_PI);
                }
            }


            setSpeed(rand()%speedMax_ + speedMin_);
            tempPauseTime_ = pauseTime_;
        }
    }else{

        double timeInterval = time - getPositionLastUpdate();

        double shift = timeInterval * (getSpeed()*(1000.0/3600.0));
        double shift_y = shift * sin(getAngle());
        double shift_x = shift * cos(getAngle());

        ///
        CartesianCoordinates *newPosition = new CartesianCoordinates(getPosition()->getCoordinateX() + shift_x,
                                                                     getPosition()->getCoordinateY() + shift_y,
                                                                     getPosition()->getCoordinateZ());
        forceStayInArea(newPosition);
        setPosition(newPosition);
        delete newPosition;
    }

    setPositionLastUpdate(time);

//    qDebug() << "Position = " <<getPosition()->getCoordinateX()<<" "
//             <<getPosition()->getCoordinateY()
//            << "Move to Position = " << moveToPosition_->getCoordinateX()<<" "
//            <<moveToPosition_->getCoordinateY()<<" "
//           <<"angle = " << getAngle()<<" "
//          <<"speed = " << getSpeed();


}
void Mobility::modelManhattan(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
}
void Mobility::modelLinearMovement(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
}

void Mobility::modelGaussMarkov(double times)
{
    srand(time(nullptr));

    double timeInterval = times - getPositionLastUpdate();

    double shift = timeInterval * (getSpeed()*(1000.0/3600.0));

    if(isInZone(getPosition())!=0){
        switch (isInZone(getPosition())) {
        case 1:
            setAngle(M_PI/4);
            break;
        case 2:
            setAngle(0);
            break;
        case 3:
            setAngle(-M_PI/4);
            break;
        case 4:
            setAngle(-M_PI/2);
            break;
        case 5:
            setAngle(5*M_PI/4);
            break;
        case 6:
            setAngle(M_PI);
            break;
        case 7:
            setAngle(3*M_PI/4);
            break;
        case 8:
            setAngle(M_PI/2);
            break;
        }
    }

    double shift_y = shift * sin(getAngle());
    double shift_x = shift * cos(getAngle());

    CartesianCoordinates *newPosition = new CartesianCoordinates((getPosition()->getCoordinateX() + shift_x),
                                            getPosition()->getCoordinateY() + shift_y,
                                            getPosition()->getCoordinateZ());
    forceStayInArea(newPosition);
    setPosition(newPosition);
    delete newPosition;
    setPositionLastUpdate(times);

    double newSpeed = alpha_*getSpeed() + (1 - alpha_)*averageSpeed_ +
            sqrt((1 - alpha_*alpha_)*(rand()%10));

    double newAngle = alpha_*getAngle() + (1 - alpha_)*averageAngle_ +
            sqrt((1 - alpha_*alpha_)*(rand()%10));

    setSpeed(newSpeed);
    setAngle(newAngle);

    changeCount_++;

    sumSpeed_+=getSpeed();
    sumAngle_+=getAngle();
    averageSpeed_ = (float)sumSpeed_ / (float)changeCount_;
    averageAngle_ = (float)sumAngle_ / (float)changeCount_;
}

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
// void Mobility::print()
// {
//     qDebug() << "Mobility model: " << mobilityModel_;
//     //getPosition()->print();
// }
