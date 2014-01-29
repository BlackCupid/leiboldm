#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include "altturncompgame.h"
#include "sologame.h"
#include "testgame.h"


class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget* parent_in);

private:
    void paintEvent(QPaintEvent *);
    void hide_buttons();
    void show_buttons();
    double i;

    AltTurnCompGame atc;
    SoloGame sg;
    QTableWidget* lb;
    QPushButton quit_button;
    QPushButton solo_button; // solo game button
    QPushButton atc_button; // alternating turn competitive game button
    QPushButton lb_button; // leader board button


private slots:
    void play_solo_game();
    void play_competitive_game();
    void end_solo_game();
    void end_competitive_game();
    void show_leaderboard();
    void end_leaderboard();
};

#endif // MAINMENU_H
