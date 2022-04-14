#include "creategame.hh"
#include "city.h"


std::shared_ptr<Interface::ICity> Interface::createGame()
{
    std::shared_ptr<Interface::ICity> city_(new Mikael::City());
    return city_;
}

