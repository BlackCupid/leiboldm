#include "testgame.h"

#include <QPainter>

TestGame::TestGame(QWidget* parent_in)
    : QWidget(parent_in), moves_made(0), game_finished(false), gf1(false)
{
    QColor default_colorset[6] = {Qt::blue, Qt::red, Qt::yellow, Qt::green, Qt::magenta, Qt::cyan};
    board = new Board(this, default_colorset);
    last_color = board->get_first_color();
    QObject::connect(board, SIGNAL(move_made(QColor)),this,SLOT(button_clicked(QColor)));
    QObject::connect(board,SIGNAL(board_complete()),this,SLOT(game_complete()));
    msg = new EndGameMessage(this, 0, 0, 0);
    msg->hide();
}

void TestGame::button_clicked(QColor color)
{
    if (game_finished) return; // don't waste resources re-rendering
    if (color != last_color) {
        moves_made++;
        last_color = color;
        update();
    }
    if (gf1) game_finished = true;
}

void TestGame::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    QFont font("Arial");
    font.setBold(true);
    font.setPointSize(20);
    painter.setFont(font);
    QString moveString;
    moveString = QString("Moves made: %1").arg(moves_made);
    painter.drawText(50, 690, moveString);
}

void TestGame::game_complete()
{
    gf1 = true;
    delete msg;
    msg = new EndGameMessage(this, moves_made, width(), height());
    msg->show();
    QObject::connect(msg, SIGNAL(restart_button_clicked()),this,SLOT(new_game()));
    QObject::connect(msg,SIGNAL(menu_button_clicked()),this,SIGNAL(goto_menu()));
}

void TestGame::new_game()
{
    gf1 = false;
    game_finished = false;
    msg->hide();
    moves_made = 0;
    board->reset_board();
    board->update();
    last_color = board->get_first_color();
    update();
}
