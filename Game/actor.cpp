#include "actor.hh"



Actor::Actor() : Interface::IActor::IActor()
{
    location_= Interface::Location();
    removed_ = false;
}

Actor::~Actor()
{

}

Interface::Location Actor::giveLocation() const
{
    return location_;
}

void Actor::move(Interface::Location loc)
{
    location_ = loc;
}

bool Actor::isRemoved() const
{
    return removed_;
}

void Actor::remove()
{
    removed_ = true;
}


