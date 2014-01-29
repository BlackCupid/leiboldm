#ifndef ENDGAMEMESSAGE_H
#define ENDGAMEMESSAGE_H

#include <QWidget>
#include <QPushButton>

class EndGameMessage : public QWidget
{
    Q_OBJECT
public:
    EndGameMessage(QWidget *parent_in, int moves_in, int parwidth, int parheight);
    void set_parent_width(int w);
    void set_parent_height(int h);
    void set_total_moves(int m);

protected:
    virtual void paintEvent(QPaintEvent *);
    int parent_width;
    int parent_height;
    int total_moves;
    QPushButton* restart_button;
    QPushButton* menu_button;

signals:
    void menu_button_clicked();
    void restart_button_clicked();
};

#endif // ENDGAMEMESSAGE_H
