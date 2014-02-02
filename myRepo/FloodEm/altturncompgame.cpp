#include "altturncompgame.h"
#include <QPainter>

AltTurnCompGame::AltTurnCompGame(QWidget* parent_in)
    : QWidget(parent_in), player1_score(0), player2_score(0), game_finished(false),
      current_player('1'), gf1(false)
{
    msg = new CompGameEndMessage(this, 0, 0, 0, 0, 0);
    msg->hide();
    QColor default_colorset[6] = {Qt::blue, Qt::red, Qt::yellow, Qt::green, Qt::magenta, Qt::cyan};
    board = new Board(this, default_colorset);
    last_color = board->get_first_color();
    QObject::connect(board, SIGNAL(move_made(QColor)),this,SLOT(button_clicked(QColor)));
    QObject::connect(board,SIGNAL(board_complete()),this,SLOT(game_complete()));
}

void AltTurnCompGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font("Arial");
    font.setBold(true);
    font.setPointSize(20);
    painter.setFont(font);
    QString p1scoreString;
    p1scoreString = QString("Player 1:  %1").arg(player1_score);
    painter.drawText(50, 690, p1scoreString);
    QString p2scoreString;
    p2scoreString = QString("Player 2:  %1").arg(player2_score);
    painter.drawText(300, 690, p2scoreString);
}

void AltTurnCompGame::button_clicked(QColor color)
{
    if (game_finished) return; // don't waste resources re-rendering
    if (color != last_color) {
        if (current_player == '1') {
            player1_score += board->squares_claimed_by_move();
            current_player = '2';
        }
        else {
            player2_score += board->squares_claimed_by_move();
            current_player = '1';
        }
        last_color = color;
        update();
    }
    if (gf1) game_finished = true;

}
void AltTurnCompGame::game_complete()
{
    gf1 = true;
    delete msg;
    msg = new CompGameEndMessage(this, 0, player1_score, player2_score, width(), height());
    msg->show();
    QObject::connect(msg, SIGNAL(restart_button_clicked()),this,SLOT(new_game()));
    QObject::connect(msg,SIGNAL(menu_button_clicked()),this,SIGNAL(goto_menu()));
}

void AltTurnCompGame::new_game()
{
    gf1 = false;
    game_finished = false;
    msg->hide();
    player1_score = 0;
    player2_score = 0;
    current_player = '1';
    board->reset_board();
    board->update();
    last_color = board->get_first_color();
    update();
}
