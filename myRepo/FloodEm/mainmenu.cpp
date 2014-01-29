#include "mainmenu.h"
#include <QPushButton>
#include <QPainter>
#include "altturncompgame.h"
#include "sologame.h"
#include "testgame.h"
#include <cmath>
#include <QTableWidget>


MainMenu::MainMenu(QWidget *parent_in)
    : QWidget(parent_in), sg(SoloGame(this)), atc(AltTurnCompGame(this)),
      lb(new QTableWidget(1,2,this))
{
    setFixedSize(600,700);
    quit_button.setParent(this);
    solo_button.setParent(this);
    atc_button.setParent(this);
    lb_button.setParent(this);

    quit_button.setText("Quit");
    QObject::connect(&quit_button,SIGNAL(clicked()),parentWidget(),SLOT(close()));

    solo_button.setText("Solo Game");
    QObject::connect(&solo_button,SIGNAL(clicked()),this,SLOT(play_solo_game()));

    atc_button.setText("Competitive Game");
    QObject::connect(&atc_button,SIGNAL(clicked()),this,SLOT(play_competitive_game()));

    lb_button.setText("Leader Board");
    QObject::connect(&lb_button,SIGNAL(clicked()),this,SLOT(show_leaderboard()));

    QObject::connect(&atc,SIGNAL(goto_menu()),this,SLOT(end_competitive_game()));
    QObject::connect(&sg,SIGNAL(goto_menu()),this,SLOT(end_solo_game()));
    sg.hide();
    atc.hide();

    lb->setFixedSize(400,500);
    lb->move(100,50);
    lb->hide();

    QFont font("Arial");
    font.setBold(true);
    font.setPointSize(20);
    solo_button.setFont(font);
    quit_button.setFont(font);
    atc_button.setFont(font);
    lb_button.setFont(font);

    solo_button.setFixedSize(250, 50);
    atc_button.setFixedSize(300, 50);
    quit_button.setFixedSize(250, 50);
    lb_button.setFixedSize(300, 50);

    int h = height();
    solo_button.move(175, h/2 - 175);
    atc_button.move(150,h/2 - 75);
    lb_button.move(150, h/2 + 25);
    quit_button.move(175,h/2 + 125);

    i = 0;
}

static QColor randColor() {
    QColor colorArray[6] = {Qt::blue, Qt::red, Qt::cyan, Qt::magenta,
                         Qt::yellow, Qt::green};
    return colorArray[rand() % 6];

}

void MainMenu::paintEvent(QPaintEvent* )
{
    setFixedSize(parentWidget()->width(),parentWidget()->height());
    QPainter painter(this);
    double w = width();
    double h = height();
    QFont font("Times");
    font.setStyleHint(QFont::Monospace);
    font.setPointSize(w/12);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::blue);
    QString str = "Flood Em!";
    for (int i = 0; i < 9; i++) {
        painter.setPen(Qt::black);
        // Drawing each letter 5 times to get our wacky outlined font
        painter.drawText((w/6 + i*2*w/27 + w/120), h/8, w/9, 3*h/4, 1, QString(str[i]));
        painter.drawText((w/6 + i*2*w/27), h/8 + w/120, w/9, 3*h/4, 1, QString(str[i]));
        painter.drawText((w/6 + i*2*w/27 - w/120), h/8, w/9, 3*h/4, 1, QString(str[i]));
        painter.drawText((w/6 + i*2*w/27), h/8 - w/120, w/9, 3*h/4, 1, QString(str[i]));
        painter.setPen(randColor().lighter(100));
        painter.drawText((w/6 + i*2*w/27), h/8, w/9, 3*h/4, 1, QString(str[i]));
    }
}

void MainMenu::play_solo_game()
{
    hide_buttons();
    sg.board->grabKeyboard();
    sg.new_game();
    sg.show();
}

void MainMenu::end_solo_game()
{
    sg.hide();
    sg.board->releaseKeyboard();
    show_buttons();
}

void MainMenu::play_competitive_game()
{
    hide_buttons();
    atc.new_game();
    atc.board->grabKeyboard();
    atc.show();
}

void MainMenu::end_competitive_game()
{
    atc.hide();
    atc.board->releaseKeyboard();
    show_buttons();
}

void MainMenu::show_leaderboard()
{
    hide_buttons();
    QPushButton* to_menu = new QPushButton(this);
    to_menu->setText("Back to Menu");
    QObject::connect(to_menu,SIGNAL(clicked()),this,SLOT(end_leaderboard()));
    to_menu->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(to_menu,SIGNAL(clicked()),to_menu,SLOT(close()));
    to_menu->setFixedSize(200,40);
    to_menu->move(width()/2 - 100, 550);
    QFont font("Arial");
    font.setPointSize(20);
    font.setBold(true);
    to_menu->setFont(font);
    to_menu->show();
    
    
    lb->show();
}

void MainMenu::end_leaderboard()
{
    lb->hide();
    show_buttons();
}


void MainMenu::show_buttons()
{
    atc_button.show();
    solo_button.show();
    quit_button.show();
    lb_button.show();
}

void MainMenu::hide_buttons()
{
    atc_button.hide();
    solo_button.hide();
    quit_button.hide();
    lb_button.hide();
}
