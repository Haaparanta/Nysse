#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QImage>
#include <QGraphicsRectItem>
#include <QVector>
#include <memory>
#include "../CourseLib/graphics/simpleactoritem.hh"
#include "../CourseLib/interfaces/icity.hh"
#include "actoritem.hh"
#include "resource.hh"
#include "gamer.hh"
#include <QGraphicsItem>
#include <QPainter>
#include "dialog.h"
#include "QGraphicsSimpleTextItem"
#include "../CourseLib/core/logic.hh"
#include "QLabel"
#include <QSound>


namespace Ui {
class MainWindow;
}

namespace Vesa {

/**
 * @brief The MainWindow class
 *  Mainwindow so you can play the game
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Take controls from player
    void keyPressEvent(QKeyEvent* event) override;

    Ui::MainWindow* giveMainwindow();

    void addActor(Vesa::ActorItem* nActor);
    // Reimplemented function with changable radius
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem *> > getNearbyActorsandItems(
            Interface::Location loc, int radius = 10);

    // Adds infected actors to mainwindow
    void addInfected(std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*> Infected);
    void resetInfected();

    // So we can iterate through actors and their corresponding graphic items
    void getActorsanditems(std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*>>
                           actorsAndItems);

    void takeCity(std::shared_ptr<Interface::ICity> city);

    void setPicture(QImage &img);
    void setGameBackround();

    void playerVision(); // Moves player
    void storedName(QString name);
    QString getName();

    // Spread the disease to nearbyActors, 10% chance
    void updatePandemic();
    int reportBatCount();
    int reportPopulation();
    // Game ending procedures
    void endGame(bool defeated);

    long int getPoints();

    void upgrade(int type);

    int useUpgrade(int type);

    void resetUpgrades();

private slots:
    void on_start_clicked();

    void on_pause_clicked();

    void on_reset_clicked();

    void on_quit_clicked();

    void on_Playmusic_clicked();

    void on_up1_clicked();

    void on_up2_clicked();

    void on_up3_clicked();

    void on_up4_clicked();

    void on_up5_clicked();

private:
    int kasidesi = 0;
    int vessapaperi = 0;
    int maskit = 0;
    int kasidesiU = 5;
    int vessapaperiU = 3; // You get lesser toilet paper bc it is worth more in pandemic.
    int maskitU = 4;
    int rangeU = 60;
    int speedU = 5;
    int bats = 20;


    QSound* song_;
    QSound* song;
    bool gameOn = false;

    QTimer timer_;
    QTimer fast_timer_;
    QTimer resource_timer;
    QTimer infection_timer;
    int sec_;
    int min_;
    bool game_;
    long int points_;
    void updatePoints();
    Ui::MainWindow *ui;
    QGraphicsScene* map;
    void updateView();
    int viewHeight = 0;
    int viewWidth = 0;
    int sceneHeight = 0;
    int sceneWidth = 0;
    bool bigMap = true;
    QString name_;
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*>> infectedsAndItems;
    std::vector<std::pair<std::shared_ptr<Interface::IActor>, Vesa::ActorItem*>> actorsAndItems_;
    std::shared_ptr<Interface::ICity> city_;
    std::vector<std::pair<Resource*, QGraphicsSimpleTextItem*>> resourseandtext;

    void addResourceLocations();
    void updateResource();
    void addResource();
    void collectResources();
    void resetResources();

    Gamer* gamer_ = nullptr;

    std::vector<std::pair<int, int>> resourcelocations_ = {{2130,2200},{1660,710}, {830,1510}, {780,360},{560,420},
                                                           {2245,2250}, {80,1400},{2222,720},{900,500},{420,369},
                                                           {2110,2200},{1640,670},{700,570},{285,90}};
    int refresh_rate = 0;

    QLabel* fps_;
    QLabel* kasidesi_;
    QLabel* vessapaperi_;
    QLabel* maskit_;
    QLabel* score_;
    QLabel* min;
    QLabel* sec;
    QLabel* bats_;
    QLabel* people_;
    QLabel* instructions_;
    QLabel* gameEndingText_;

};

}
#endif // GAMEWINDOW_H

