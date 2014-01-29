#include "mainwindow.h"

MainWindow::MainWindow()
    : mainmenu(MainMenu(this))
{
    mainmenu.show();
}
