#ifndef TESTGAME_H
#define TESTGAME_H

#include <QWidget>
#include "board.h"
#include "endgamemessage.h"

class TestGame : public QWidget
{
    Q_OBJECT
public:
    TestGame(QWidget* parent_in=0);
    Board* board;
    EndGameMessage* msg;

private:
    int moves_made;
    QColor last_color;
    void paintEvent(QPaintEvent *);
    bool game_finished;
    bool gf1;

public slots:
    void button_clicked(QColor color);
    void game_complete();
    void new_game();

signals:
    void goto_menu();
};

#endif // TESTGAME_H
