#ifndef STOP_H
#define STOP_H

#include "../CourseLib/interfaces/istop.hh"

class Stop : public Interface::IStop
{
public:
    Stop();

    // IStop interface
public:
    Interface::Location getLocation() const override;
    QString getName() const override;
    unsigned int getId() const override;
    std::vector<std::shared_ptr<Interface::IPassenger> > getPassengers() const override;    

private:
    Interface::Location location_;
    QString name_;
    unsigned int id_;
    std::vector<std::shared_ptr<Interface::IPassenger>> passengers_;

};

#endif // STOP_H
