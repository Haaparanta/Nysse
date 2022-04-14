#ifndef ACTOR_HH
#define ACTOR_HH


#include "../CourseLib/interfaces/icity.hh"
#include "../CourseLib/interfaces/istop.hh"
#include "../CourseLib/interfaces/iactor.hh"
#include "../CourseLib/actors/stop.hh"
#include "../CourseLib/core/location.hh"
#include "../CourseLib/interfaces/ivehicle.hh"

/**
 * @brief The Actor class
 * This class is baseclass of nysses and passangers
 */

class Actor : public Interface::IActor
{
public:
    Actor();
    virtual ~Actor();

    /**
     * @brief giveLocation returns the location of the actor.
     * @pre -
     * @return Actors location.
     * @post Exception guarantee: strong.
     * @exception GameError - actor wasn't given a location.
     */
    Interface::Location giveLocation() const = 0;

    /**
     * @brief move-method moves the actor to given location.
     * @param loc Actors new location.
     * @pre -
     * @post Actors location is sij. Excaption guarantee: strong.
     * @exception GameError Location is not possible.
     */
    void move(Interface::Location loc);

    /**
     * @brief isRemoved tells if the actor is removed ingame.
     * @pre -
     * @return `true`, if actor is removed ingame, otherwise `false`.
     * @post Exception guarantee: nothrow.
     */
    bool isRemoved() const;

    /**
     * @brief remove marks the actor as removed.
     * @pre Actor is not removed already.
     * @post Actor is removed, after this isRemoved() returns `true`. Exception guarantee: basic.
     */
    void remove();

private:
    Interface::Location location_;
    bool removed_;


};

#endif // ACTOR_HH
