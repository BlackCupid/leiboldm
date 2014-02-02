#include "compgameendmessage.h"
#include <QPainter>

CompGameEndMessage::CompGameEndMessage(QWidget* parent_in, int moves_in, int p1score,
                                       int p2score, int parwidth, int parheight)
    : EndGameMessage(parent_in, moves_in, parwidth, parheight), player1score(p1score),
      player2score(p2score)
{
}

void CompGameEndMessage::paintEvent(QPaintEvent* )
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
    if (player1score > player2score) {
        painter.drawText(rec, Qt::AlignHCenter, "Player 1 Wins!");
    }
    else if (player2score > player1score) {
        painter.drawText(rec, Qt::AlignHCenter, "Player 2 Wins!");
    }
    else {
        painter.drawText(rec, Qt::AlignCenter, "Tie Game!");
    }
    y += 50;
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
