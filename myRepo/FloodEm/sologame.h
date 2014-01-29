#ifndef SOLOGAME_H
#define SOLOGAME_H

#include <QWidget>
#include "endgamemessage.h"
#include "board.h"

class SoloGame : public QWidget
{
    Q_OBJECT
public:
    SoloGame(QWidget* parent_in=0);
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

#endif // SOLOGAME_H
