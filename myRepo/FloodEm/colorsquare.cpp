#include "colorsquare.h"
#include <QPainter>

ColorSquare::ColorSquare(QWidget* parent_in, QColor color_in)
    : QWidget(parent_in), hit(false), size(50), color(color_in)
{
    setFixedSize(size, size);
}

void ColorSquare::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(color);
    painter.drawRect(0,0, size, size);
    painter.fillRect(0,0, size, size, color);
}

QColor ColorSquare::get_color()
{
    return color;
}

void ColorSquare::set_color(QColor new_color)
{
    color = new_color;
    update();
}

void ColorSquare::mousePressEvent(QMouseEvent* )
{
    emit square_clicked(color);
}
