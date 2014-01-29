#ifndef COLORSQUARE_H
#define COLORSQUARE_H

#include <QWidget>
#include <QMouseEvent>

class ColorSquare : public QWidget
{
    Q_OBJECT
public:
    ColorSquare(QWidget *parent_in, QColor color_in);
    void paintEvent(QPaintEvent *);
    QColor get_color();
    void set_color(QColor new_color);
private:
    void mousePressEvent(QMouseEvent*);
    QColor color;
    bool hit;
    int size;
signals:
    void square_clicked(QColor);
};

#endif // COLORSQUARE_H
