#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainmenu.h"
#include "sologame.h"
#include "altturncompgame.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    MainMenu mainmenu;
};

#endif // MAINWINDOW_H
