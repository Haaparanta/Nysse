#include "vehicle.h"

Vehicle::Vehicle()
{

}

std::string Vehicle::getName() const
{
    return name_;
}

std::vector<std::shared_ptr<Interface::IPassenger> > Vehicle::getPassengers() const
{
    return passengers_;
}

void Vehicle::addPassenger(std::shared_ptr<Interface::IPassenger> passenger)
{
    passengers_.push_back(passenger);
}

void Vehicle::removePassenger(std::shared_ptr<Interface::IPassenger> passenger)
{
    passengers_.erase(std::remove(passengers_.begin(), passengers_.end(), passenger), passengers_.end());
}
