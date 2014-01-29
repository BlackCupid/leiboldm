#include "colorbutton.h"
#include <cmath>
#include <QPainter>
#include <QMouseEvent>

ColorButton::ColorButton(QWidget* parent_in, QColor color_in)
    : QWidget(parent_in), size(50), color(color_in), depressed(false)
{
    setFixedSize(size + 10, size + 10);
}

void ColorButton::mousePressEvent(QMouseEvent* event)
{
    int relx = event->x() - size/2 - 5;  // x relative to center of circle
    int rely = event->y() - size/2 - 5;  // y relative to center of circle

    //only emits signal if mouse press is within circle
    if ((relx*relx + rely*rely) < size*size/4)
    {
        emit triggered(color);
    }
    depressed = true;
}

void ColorButton::mouseReleaseEvent(QMouseEvent*)
{
    depressed = false;
    update();
}

//TODO: Draw rectangles with gradient that makes them look sexy
void ColorButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    QRadialGradient grad(30,30,30);
    if (!depressed){
        grad.setColorAt(0.2, color.darker(110));
        grad.setColorAt(1, color.lighter(140));
    }
    else {
        grad.setColorAt(0.2, color.lighter(140));
        grad.setColorAt(1, color.darker(110));
    }
    QBrush brush(grad);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(5,5,size,size);
}
