#ifndef PASSENGER_H
#define PASSENGER_H

#include "../CourseLib/interfaces/ipassenger.hh"


class Passenger : public Interface::IPassenger
{
public:
    Passenger();
    /**
     * @brief isInVehicle tells if passenger is in any vehicle currently.
     * @pre -
     * @return Boolean, tells wether passenger is in any vehicle.
     * @post Exception guarantee: nothrow
     */
    bool isInVehicle() const final;

    /**
     * @brief getVehicle returns the vehicle passenger is in.
     * @pre -
     * @return Vechicle where passenger is in. Empty pointer if passenger is not in any vehicle.
     * @post Exception guarantee: nothrow.
     */
    std::shared_ptr<Interface::IVehicle> getVehicle() const final;
    void setVehicle(std::shared_ptr<Interface::IVehicle>vehicle);
    void setStop(std::shared_ptr<Interface::IStop> stop);

    // We need to monitor infection state of a passenger and to give them infection
    // at will.
    bool hasInfection();
    void giveInfection();

private:
    bool inVehicle = false;
    std::shared_ptr<Interface::IVehicle> bus_ = nullptr;
    std::shared_ptr<Interface::IStop> stop_ = nullptr;
    bool isInfected_ = false;

};

#endif // PASSENGER_H
