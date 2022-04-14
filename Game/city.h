#ifndef CITY_H
#define CITY_H

#include <vector>
#include <memory>
#include <QTime>
#include "QTimer"
#include "passenger.h"

#include "../CourseLib/interfaces/icity.hh"
#include "../CourseLib/interfaces/istop.hh"
#include "../CourseLib/interfaces/iactor.hh"
#include "../CourseLib/actors/stop.hh"
#include "../CourseLib/core/location.hh"
#include "gamewindow.h"
#include "actor.hh"
#include "../CourseLib/interfaces/ivehicle.hh"
#include "statistics.h"

namespace Mikael {


class City : public Interface::ICity
{
public:

    City(Vesa::MainWindow* inputWindow = nullptr, Mikael::Statistics* stats = nullptr);
    ~City();
    /**
     * @brief setBackground sets the bitmap picture of the game area.
     * @param basicbackground  Normal sized picture used as the game area. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @param bigbackground  Background of the game that is bigger than normal. Used only if doing Scrolling map-expansion. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @pre City is in init state.
     * @post Picture for the game area is set. Exception guarantee: basic.
     * @exception InitError Setting the picture was unsuccesful or the picture was invalid.
     */
    void setBackground(QImage& basicbackground, QImage& bigbackground) final;
    /**
     * @brief setClock sets the time of the game clock.
     * @param clock Game clock time at the function call.
     * @pre `kello.isValid() == true`.
     * @post Time is set. Exception guarantee: nothrow.
     */
    void setClock(QTime clock) final;
    /**
     * @brief addStop adds a stop to the city.
     * @param stop pointer to a stop object.
     * @pre City is in init state.
     * @post Stop is added to the city. Exception guarantee: basic
     * @exception InitError Stops position is not valid.
     */
    void addStop(std::shared_ptr<Interface::IStop> stop) final;
    /**
     * @brief startGame shofts city from init state to the gamestate.
     * @pre City is in init state. setBackground() and setClock() have been called.
     * @post City is in gamestate. Exception guarantee: nothrow.
     */
    void startGame() final;
    /**
     * @brief addActor adds a new actor to the city.
     * @param newactor actor to be added to the city that fulfills ActorIF.
     * @pre -
     * @post Actor is added to the city. Exception guarantee: basic.
     * @exception GameError Actor is already in the city.
     */
    void addActor(std::shared_ptr<Interface::IActor> newactor) final;
    /**
     * @brief removeActor removes the actor from the city.
     * @param actor Actor to be removed.
     * @pre City is in gamestate.
     * @post Actor is removed from the city. Exception guarantee: strong.
     * @exception GameError Actor not found in the city
     */
    void removeActor(std::shared_ptr<Interface::IActor> actor) final;
    /**
     * @brief actorRemoved tells the city that actor is removed ingame.
     * @param actor Actor that is set removed ingame.
     * @pre City is in gamestate. Given actor is found in the city. Actor has `actor.isRemoved() == true`.
     * @post Exception guarantee: strong.
     */
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) final;
    /**
     * @brief findActor checks if the given actor is in the city.
     * @param actor Actor that that is looked for in the city.
     * @pre -
     * @return Boolean that tells wether the actor is in the city.
     * @post Exception guarantee: nothrow.
     */
    bool findActor(std::shared_ptr<Interface::IActor> actor) const final;

    /**
     * @brief actorMoved is an operation that is used to tell wether certain actor has moved.
     * @param actor Actor that has moved.
     * @pre City is in gamestate. Given actor is found in the city.
     * @post Exception guarantee: basic.
     */
    void actorMoved(std::shared_ptr<Interface::IActor> actor) final;

    // At the start of the game, we need to infect some passengers to start a pandemic
    void initiatePandemic (int infected = 20);

    // We need to be able to iterate through passengers and manipulate their state
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*>> givePassengers();

    /**
     * @brief getNearbyActors returns actors that are close to given position.
     * @param loc Location for getting the actors close to it.
     * @pre City is in gamestate.
     * @return Vector containing actors close to the location, that pass `getLocation().isClose(loc) == true`.
     * @post Exception guarantee: strong.
     */

    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const final;

    /**
     * @brief isGameOver
     * @return true if bats level is equal to 0 or 10
     */
    bool isGameOver() const final;
    QTime time_;

private:
    Vesa::MainWindow* mainWindow_ = nullptr;
    Mikael::Statistics* stats_ = nullptr;

    // We want to separate each actor by their type to their owen vectors, along with their corresponding
    // graphic items.
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*>> actorsAndItems;
    std::vector<std::pair<std::shared_ptr<Interface::IStop>, Vesa::ActorItem*>> stopsAndItems;
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*>> busesAndItems;
    std::shared_ptr<Interface::IActor> last_;
    int i = 0;
    int j = 0;
    int dx = 373;
    int dy = 133;
    bool startedgame = false;

    // Infection percentage, at which the game is lost
    double losingThreshold = 10.0;

};
}

#endif // CITY_H
