#ifndef ALTTURNCOMPGAME_H
#define ALTTURNCOMPGAME_H

#include <QWidget>
#include "board.h"
#include "compgameendmessage.h"

// An Competitive game where two players alternate turns
class AltTurnCompGame : public QWidget
{
    Q_OBJECT
public:
    AltTurnCompGame(QWidget *parent_in);
    Board* board;
    CompGameEndMessage* msg;

private:
    int player1_score;
    int player2_score;
    QColor last_color;
    void paintEvent(QPaintEvent *);
    bool game_finished;
    bool gf1;
    char current_player; // '1' is player1, '2' is player2

public slots:
    void button_clicked(QColor color);
    void game_complete();
    void new_game();

signals:
    void goto_menu();
};

#endif // ALTTURNCOMPGAME_H
