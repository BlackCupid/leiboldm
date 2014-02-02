#ifndef BOARD_H
#define BOARD_H

#include "colorsquare.h"
#include "colorbutton.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    static const int NUMCOLORS = 6;
    static const int SIDELENGTH = 12;

    //REQUIRES: colorset is an array of 6 different colors
    Board(QWidget* parent_in, QColor* colorset);
    void reset_board();
    QColor get_first_color();
    int squares_claimed_by_move();

private:
    //EFFECTS: selects a color from color_array at random
    //TODO: should have some method for increasing probability of
    //      there being roughly equal numbers of each color
    QColor generate_rand_color();

    //Binds a,s,d,f,g,h to the six colors
    void keyPressEvent(QKeyEvent *event);
    bool boardIsFlooded();
    void match(int row, int col);
    bool left(int row, int col);
    bool right(int row, int col);
    bool top(int row, int col);
    bool down(int row, int col);
    bool check_if_frontier(int row, int col);
    void find_matching_colors();

    QColor color_array[NUMCOLORS];
    ColorSquare* square_array[SIDELENGTH][SIDELENGTH];
    ColorButton* button_array[NUMCOLORS];
    bool matched_array[SIDELENGTH][SIDELENGTH];
    bool frontier_array[SIDELENGTH][SIDELENGTH];
    int squares_claimed; // counts number of squares claimed in most recent move

private slots:
    void color_selected(QColor color);

signals:
    void move_made(QColor);
    void board_complete();
};

#endif // BOARD_H
