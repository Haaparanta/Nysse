#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include <vector>
#include <memory>
#include <QTime>

#include "../CourseLib/core/logic.hh"
#include "../CourseLib/interfaces/icity.hh"
#include "../CourseLib/interfaces/istop.hh"
#include "../CourseLib/interfaces/iactor.hh"
#include "../CourseLib/actors/stop.hh"
#include "../CourseLib/core/location.hh"
#include "../CourseLib/creategame.hh"
#include "statistics.h"

const QString DEFAULT_STOPS_FILE = ":/offlinedata/offlinedata/full_stations_kkj3.json";
const QString DEFAULT_BUSES_FILE = ":/offlinedata/offlinedata/final_bus_liteN.json";

#include "gamewindow.h"
#include "city.h"

namespace Vesa
{

class Gameengine : public CourseSide::Logic
{
public:
    Gameengine();
    ~Gameengine();
    /**
     * @brief takeUi
     * @param ui
     * take ui to engine so it can give it to city
     */
    void takeUi(Vesa::MainWindow* ui);
    /**
     * @brief startGame
     * call right functions to start game
     */
    void startGame();

private:
    Vesa::MainWindow *mainwindow_;
    std::shared_ptr<Interface::ICity> city_;
    Mikael::Statistics* stats_;
};

}

#endif // GAMEENGINE_HH
