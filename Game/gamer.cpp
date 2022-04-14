#include "gamer.hh"
#include "QDebug"

Gamer::Gamer(int sceneW, int sceneH, QString name) :
    sceneW_(sceneW), sceneH_(sceneH), playerName_(name)
{
    setPos(mapToParent(x_, y_));
    size_ = 29;
    loc_= Interface::Location();
    loc_.setXY(x_ + 373,500 + y_ + 133);
}

QRectF Gamer::boundingRect() const
{
    return QRectF(0, 0, size_, size_);
}

void Gamer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, QPixmap(":/DRONE.png"), 0, 0, 0, 0);
    // Use (void) to suppress warnings about option and widget not being used, recurring theme
    (void) option;
    (void) widget;
}

void Gamer::move(char heading, int deltaX, int deltaY)
{
    if (deltaX == 0) {
        step_ = deltaY;
    } else {
        step_ = deltaX;
    }
    if (isMovable(heading)) {
        setCoord(x_ + deltaX, y_ + deltaY);
    }
}

int Gamer::giveX()
{
    return x_;
}

int Gamer::giveY()
{
    return y_;
}

QString Gamer::getName()
{
    return playerName_;
}

Interface::Location Gamer::returnloc()
{
    loc_.setXY(x_ - 373,500 - y_ + 133);
    return loc_;
}

void Gamer::giveName(QString name)
{
    playerName_ = name;
}


bool Gamer::isMovable(char heading)
{
    if (heading == 'D') {
        if (x_ + size_ + step_ <= sceneW_) {
            return true;
        }
        return false;
    } else if (heading == 'A') {
        if (x_ - step_ >= 0) {
            return true;
        }
        return false;
    }else if (heading == 'W') {
        if (y_ - step_ >= 0) {
            return true;
        }
        return false;
    }else if (heading == 'S') {
        if (y_ + step_ <= sceneH_) {
            return true;
        }
        return false;
    }
    return false;
}

void Gamer::setCoord(int x, int y)
{
    setX(x);
    setY(y);
    x_ = x;
    y_ = y;
}
