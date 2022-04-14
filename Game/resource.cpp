#include "resource.hh"

Resource::Resource(int x, int y, int type): x_(x),y_(y), type_(type)
{
    setPos(mapToParent(x_ - 25, y_ - 25));
    loc_= Interface::Location();
    loc_.setXY(x_ - 373,500 - y_ + 133);
}

Resource::~Resource()
{

}

QRectF Resource::boundingRect() const
{
    return QRectF(0, 0, size_, size_);
}

void Resource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (type_ == 0) {
        painter->drawPixmap(0,0,QPixmap(":/kasidesi.png"),0,0,0,0);
    } else if (type_ == 1) {
        painter->drawPixmap(0,0,QPixmap(":/Vessapaperi.png"),0,0,0,0);
    } else if (type_ == 2) {
        painter->drawPixmap(0,0,QPixmap(":/mask.png"),0,0,0,0);
    }
    (void) option;
    (void) widget;
}

Interface::Location Resource::returnloc()
{
    return loc_;
}

void Resource::addResouce(int amount)
{
    resource_ += amount;
}

int Resource::returnResource()
{
    int temp = resource_;
    resource_ = 0;
    return temp;
}

int Resource::resourceAmount()
{
    return resource_;
}

int Resource::returnType()
{
    return type_;
}
