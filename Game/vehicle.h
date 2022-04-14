#ifndef VEHICLE_H
#define VEHICLE_H

#include "../CourseLib/interfaces/ivehicle.hh"
#include "algorithm"

class Vehicle : public Interface::IVehicle
{
public:
    Vehicle();

    // IVehicle interface
public:
    std::string getName() const override;
    std::vector<std::shared_ptr<Interface::IPassenger> > getPassengers() const override;
    void addPassenger(std::shared_ptr<Interface::IPassenger> passenger) override;
    void removePassenger(std::shared_ptr<Interface::IPassenger> passenger) override;
private:
    std::vector<std::shared_ptr<Interface::IPassenger>> passengers_;
    std::string name_;
};

#endif // VEHICLE_H
