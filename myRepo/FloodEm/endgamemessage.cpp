#include "endgamemessage.h"
#include <QPainter>

EndGameMessage::EndGameMessage(QWidget* parent_in, int moves_in, int parwidth, int parheight)
    : QWidget(parent_in), total_moves(moves_in), parent_width(parwidth), parent_height(parheight)
{
    setFixedSize(parent_width, parent_height);
    update();
    restart_button = new QPushButton(this);
    menu_button = new QPushButton(this);
    QObject::connect(restart_button,SIGNAL(clicked()),this,SIGNAL(restart_button_clicked()));
    QObject::connect(menu_button,SIGNAL(clicked()),this,SIGNAL(menu_button_clicked()));
}

void EndGameMessage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QFont font("Arial");
    font.setBold(true);
    font.setPointSize(30);
    painter.setFont(font);
    int x, y;
    x = parent_width/4;
    y = parent_height/3;
    QRectF rec(x, y, x*2, y*2);
    if (total_moves < 22) {
        painter.drawText(rec, Qt::AlignHCenter | Qt::TextWordWrap, "You Win!");
        y += 50;
    }
    else if (total_moves < 30){
        painter.drawText(rec, Qt::AlignHCenter | Qt::TextWordWrap, "You Lose!");
        y += 50;
    }
    else if (total_moves > 1000000){
        painter.drawText(rec, Qt::AlignHCenter | Qt::TextWordWrap, "You're crazy");
        y += 50;
    }
    else {
        painter.drawText(rec, Qt::AlignHCenter | Qt::TextWordWrap,
             "That was pathetic. You can uninstall my game now"); // hoping for stockholm syndrome
        y += 200;
    }
    restart_button->setText("New Game");
    menu_button->setText("Main Menu");
    int but_width = 150;
    font.setPointSize(20);
    menu_button->setFont(font);
    restart_button->setFont(font);
    menu_button->setFixedSize(but_width,32);
    restart_button->setFixedSize(but_width,32);
    restart_button->move(x, y);
    menu_button->move(x + but_width, y);
    menu_button->show();
    restart_button->show();
}

void EndGameMessage::set_parent_width(int w)
{
    parent_width = w;
    setFixedWidth(w);
    update();
}

void EndGameMessage::set_parent_height(int h)
{
    parent_height = h;
    setFixedHeight(h);
    update();
}

void EndGameMessage::set_total_moves(int m)
{
    total_moves = m;
}
