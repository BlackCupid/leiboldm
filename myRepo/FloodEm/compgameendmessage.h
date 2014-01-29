#ifndef COMPGAMEENDMESSAGE_H
#define COMPGAMEENDMESSAGE_H

#include "endgamemessage.h"

class CompGameEndMessage : public EndGameMessage
{
    Q_OBJECT
public:
    CompGameEndMessage(QWidget* parent_in, int moves_in, int p1score, int p2score, int parwidth,
                        int parheight);

private:
    void paintEvent(QPaintEvent *);
    int player1score;
    int player2score;
};

#endif // COMPGAMEENDMESSAGE_H
