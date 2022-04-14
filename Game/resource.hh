#ifndef RESOURCE_HH
#define RESOURCE_HH

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <vector>

#include "../CourseLib/core/location.hh"

/**
 * @brief The Resource class
 * Adds resources to map, so you can heal
 */

class Resource : public QGraphicsItem
{
public:
    Resource(int x, int y, int type);
    virtual ~Resource();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    Interface::Location returnloc();
    void addResouce(int amount);
    int returnResource();
    int resourceAmount();
    int returnType();
private:
    int x_ = 0;
    int y_ = 0;
    int type_ = 0;
    int resource_ = 0;
    int size_ = 50;
    Interface::Location loc_;
};

#endif // RESOURCE_HH
