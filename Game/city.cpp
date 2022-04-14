#include "city.h"
#include "stop.h"
#include "actor.hh"
#include "gameengine.hh"
#include "gamewindow.h"
#include "vehicle.h"

#include "QDebug"
namespace Mikael {

City::City(Vesa::MainWindow* inputWindow, Mikael::Statistics* stats)
{
    mainWindow_ = inputWindow;
    stats_ = stats;
}

City::~City()
{
    delete mainWindow_;
    delete stats_;
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    bool bigbackgroundimage = true;

    if (bigbackgroundimage) {
        mainWindow_->setPicture(bigbackground);
    } else {
        mainWindow_->setPicture(basicbackground);
    }

    mainWindow_->setGameBackround();

}

void City::setClock(QTime clock)
{
    if (clock.isValid()) {
        time_.setHMS(clock.hour(),clock.minute(), clock.second());
    }
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    // 500 - Y, because origo is located in the bottomleft corner
    Interface::Location stopLocation = stop->getLocation();
    int type = 2;
    Vesa::ActorItem* nActor = new Vesa::ActorItem(stopLocation.giveX() + dx, 500 - stopLocation.giveY() + dy, type);
    mainWindow_->addActor(nActor);
    stopsAndItems.push_back(std::make_pair(stop, nActor));
}

void City::startGame()
{
    if (!startedgame) {
    QImage image1(":/offlinedata/offlinedata//kartta_pieni_500x500.png");
    QImage image2(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    QImage image3(":/Tampere3050.png");
    setBackground(image1, image3);
    }
    startedgame = true;
    initiatePandemic();
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    // If the dynamic pointer cast fails, it returns 0, meaning newactor is not part of the subclass IVehicle.
    // Basically, if this returns 0, we know it is a passenger and not a vehicle, because this particular addActor
    // is called for both newBus and newPassenger.
    std::shared_ptr<Interface::IVehicle> isItBus = std::dynamic_pointer_cast<Interface::IVehicle>(newactor);

    // If it ain't a bus...also checking how many passengers get added. It is over 9000!
    int type = 0; // Tells Actoritem either or bus or passanger.
    if (isItBus == 0) {
        // qDebug() << i << "ois voinu olla bussi, mutta onkin ihminen!";
        i++;
        type = 1;
    } else {
        // qDebug() << j << "ois voinu olla bussi, mutta onkin bussi!";
        j++;
        type = 0;
    }

    Interface::Location actorLocation = newactor->giveLocation();
    Vesa::ActorItem* nActor = new Vesa::ActorItem(actorLocation.giveX() + dx, 500 - actorLocation.giveY() + dy, type);
    mainWindow_->addActor(nActor);
    if (isItBus == 0) { // Add to vector if a passenger.
        actorsAndItems.push_back(std::make_pair(newactor, nActor));
    } else { // Add to vector if a bus.
        busesAndItems.push_back(std::make_pair(newactor, nActor));
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if (actor->isRemoved() == false) {
        actor->remove();
    }
    mainWindow_->getActorsanditems(actorsAndItems);
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{   
    // This function is not called anywhere. Random functionality to get rid of the warnings.
    actor->giveLocation();
}


bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    if (actor->isRemoved() == true) {
        return false;
    } else {
        return true;
    }
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    // it->first is the actor. it->second is the corresponding graphical item, to which we give coordinates
    // from it->first.
    std::shared_ptr<Interface::IVehicle> isItBus = std::dynamic_pointer_cast<Interface::IVehicle>(actor);
    if (isItBus == 0) {
        for (auto& it : actorsAndItems ) {
            if (it.first == actor) {
                it.second->setCoord(it.first->giveLocation().giveX() + dx,
                                    500 - it.first->giveLocation().giveY() + dy);
            }
        }
    } else {
        for (auto& it : busesAndItems ) {
            if (it.first == actor) {
                it.second->setCoord(it.first->giveLocation().giveX() + dx,
                                    500 - it.first->giveLocation().giveY() + dy);

            }
        }
    }
}

void City::initiatePandemic(int infected)
{
    // This function will only be called once at the start of the game to throw some pandemic bats to the city.    
    std::random_shuffle( actorsAndItems.begin(), actorsAndItems.end() );
    for (int i = 0; i < infected; i++) {
        auto aPassenger = actorsAndItems.at(i);
        Interface::Location actorLocation = aPassenger.first->giveLocation();
        aPassenger.second->giveInfection();        
        actorLocation.printBoth();
        mainWindow_->addInfected(aPassenger);
    }
    mainWindow_->getActorsanditems(actorsAndItems);
}

std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem *> > City::givePassengers()
{
    return actorsAndItems;
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{  
    std::vector<std::shared_ptr<Interface::IActor>> nearbyActors;
    for (auto& actors : actorsAndItems) {
        if (actors.first->giveLocation().isClose(loc)) {
            nearbyActors.push_back(actors.first);
        }
    }
    return nearbyActors;
}

bool City::isGameOver() const
{
    float batCount = mainWindow_->reportBatCount();
    float population = mainWindow_->reportPopulation();
    auto infectedPercentage = stats_->monitorProgress(batCount, population);
    if (infectedPercentage == 0) { // checks if defeated the game
        mainWindow_->endGame(true);
        if (stats_->isTopScore(mainWindow_->getPoints())) {
            stats_->updateHighScores();
        }
        return false;

    } else if (infectedPercentage < losingThreshold) { // checks if game defeated you
        return false;

    } else {
        // You did not save everyone AND your infectedPercentage has risen above the threshold, so game should end.
        mainWindow_->endGame(false);

        if (stats_->isTopScore(mainWindow_->getPoints())) {            
            stats_->updateHighScores(mainWindow_->getName(), mainWindow_->getPoints());
        }        
        return true;
    }
}
}










