#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QWidget>

class ColorButton : public QWidget
{
    Q_OBJECT
public:
    ColorButton(QWidget *parent_in, QColor color_in);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    QColor color;
    int size;
    bool depressed; // button will look different depending on whether
                    // it's currently pressed or not
signals:
    void triggered(QColor);
};

#endif // COLORBUTTON_H
