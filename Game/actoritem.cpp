#include "actoritem.hh"
#include "QDebug"


namespace Vesa {

ActorItem::ActorItem(int x, int y, int type):
    x_(x), y_(y), type_(type)
{
    if ( x_ <= 3050 && x_ >= 0 && y_ <= 2874 && y_ >= 0) {
        if (type_ == 1) {
            deltaX = std::rand() % 20 - 10;
            deltaY = std::rand() % 20 - 10;
        }
        setPos(mapToParent(x_ + deltaX, y_ + deltaY));
    } else {
        type_ = 4; // Paint nothing because not in the area.
    }
}

ActorItem::~ActorItem()
{

}

QRectF ActorItem::boundingRect() const
{
    return QRectF(0, 0, 30, 30);
}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // QRectF bounds = boundingRect();
    if (type_ == 0) {
        painter->drawPixmap(0, 0, QPixmap(":/bussi.png"), 0, 0, 0, 0);
    } else if (type_ == 1) {
        // We chose not to paint passangers, because it wuold just make this game more heavier.
        // painter->drawPixmap(0,0,QPixmap(":/matkustaja.png"), 0, 0, 0, 0);
    } else if (type_ == 2) {
        painter->drawPixmap(0,0,QPixmap(":/pysäkki.png"), 0, 0, 0, 0);
    } else if (type_ == 3) {
        painter->drawPixmap(0,0,QPixmap(":/bat.png"), 0, 0, 0, 0);
    }

    // Suppress warnings of unused parameters
    (void) option;
    (void) widget;
}

void ActorItem::setCoord(int x, int y)
{
    if ( x_ <= 3050 && x_ >= 0 && y_ <= 2874 && y_ >= 0) {
        setX(x);
        setY(y);
        x_ = x;
        y_ = y;
    } else {
        type_ = 4; // Paint nothing because not in the area.
    }
}


void ActorItem::giveInfection()
{
    infected = true;
    type_ = 3;

}

bool ActorItem::cure()
{
    bool cured = false;
    if (infected) {
        cured = true;
        infected = false;
        type_ = 1;
    }
    return  true;
}

bool ActorItem::hasInfection()
{
    if (!infected) {
        return false;
    } else {
        return true;
    }
}


}
