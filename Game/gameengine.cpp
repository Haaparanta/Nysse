#include "gameengine.hh"
#include "QDebug"



Vesa::Gameengine::Gameengine() : CourseSide::Logic()
{

}

Vesa::Gameengine::~Gameengine()
{
    delete mainwindow_;
    delete stats_;
}

void Vesa::Gameengine::takeUi(Vesa::MainWindow *mainwindow)
{
    mainwindow_ = mainwindow;
}

void Vesa::Gameengine::startGame()
{
    Mikael::Statistics* stats(new Mikael::Statistics(mainwindow_));
    stats_ = stats;
    std::shared_ptr<Mikael::City> city(new Mikael::City(mainwindow_, stats_));

    takeCity(city);
    mainwindow_->takeCity(city);

    readOfflineData(DEFAULT_BUSES_FILE, DEFAULT_STOPS_FILE);
    city_ = city;
    setTime(8,0);
    finalizeGameStart();
}

