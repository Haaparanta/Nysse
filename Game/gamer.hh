#ifndef GAMER_HH
#define GAMER_HH

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>

#include "../CourseLib/core/location.hh"

/**
 * @brief The Gamer class
 * movable player it is a drone
 */

class Gamer : public QGraphicsPixmapItem
{
public:
    Gamer(int sceneW = 0, int sceneH = 0, QString name = "");
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void move(char heading, int deltaX, int deltaY);
    int giveX();
    int giveY();
    QString getName();
    Interface::Location returnloc();

public slots:
    void giveName(QString name);

private:
    bool isMovable(char heading);
    void setCoord(int x, int y);
    int sceneW_;
    int sceneH_;
    int size_;
    int x_ = 2125; // spawns at Mikontalo
    int y_ = 2365; // spawns at Mikontalo
    int step_ = 5;
    QString playerName_;
    Interface::Location loc_;

};

#endif // GAMER_HH
