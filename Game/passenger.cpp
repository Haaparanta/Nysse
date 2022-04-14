#include "passenger.h"

Passenger::Passenger()
{

}

bool Passenger::isInVehicle() const
{
    return inVehicle;
}

std::shared_ptr<Interface::IVehicle> Passenger::getVehicle() const
{
    return bus_;
}

void Passenger::setVehicle(std::shared_ptr<Interface::IVehicle> vehicle)
{
    bus_ = vehicle;
    stop_ = nullptr;
    inVehicle = true;
}

void Passenger::setStop(std::shared_ptr<Interface::IStop> stop)
{
    stop_ = stop;
    bus_ = nullptr;
    inVehicle = false;
}

bool Passenger::hasInfection()
{
    if (!isInfected_) {
        return false;
    } else {
        return true;
    }
}

void Passenger::giveInfection()
{
    isInfected_ = true;
}
