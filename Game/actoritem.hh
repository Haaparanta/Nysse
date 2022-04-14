#ifndef ACTORITEM_HH
#define ACTORITEM_HH7

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <vector>

namespace Vesa {
/**
 * @brief The ActorItem class
 * Paints busses, stops, bats and passangers to scene.
 */

class ActorItem : public QGraphicsPixmapItem
{
public:
    ActorItem(int x, int y, int type = 0);
    virtual ~ActorItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void setCoord(int x, int y);
    void giveInfection();
    bool cure();
    bool hasInfection();


private:
    int x_;
    int y_;
    int deltaX = 0;
    int deltaY = 0;
    int type_;
    bool infected = false;
};
}

#endif // ACTORITEM_HH
