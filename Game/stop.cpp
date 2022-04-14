#include "stop.h"

Stop::Stop()
{

}

Interface::Location Stop::getLocation() const
{
    return location_;
}

QString Stop::getName() const
{
    return name_;
}

unsigned int Stop::getId() const
{
    return id_;
}

std::vector<std::shared_ptr<Interface::IPassenger> > Stop::getPassengers() const
{
    return passengers_;
}

