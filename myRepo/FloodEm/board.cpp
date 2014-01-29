#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <QKeyEvent>

Board::Board(QWidget* parent_in, QColor* colorset)
    : QWidget(parent_in), squares_claimed(0)
{
    srand(time(NULL));
    setFixedSize(SIDELENGTH*50, (SIDELENGTH + 2)*50);
    for (int i = 0; i < NUMCOLORS; ++i){
        color_array[i] = *(colorset + i);
    }

    for (int row = 0; row < SIDELENGTH; ++row){
        for (int col = 0; col < SIDELENGTH; ++col){
            square_array[row][col] = new ColorSquare(this, generate_rand_color());
            square_array[row][col]->move(row*50,col*50);
            QObject::connect(square_array[row][col],SIGNAL(square_clicked(QColor)),
                             this,SLOT(color_selected(QColor)));
            QObject::connect(square_array[row][col],SIGNAL(square_clicked(QColor)),
                             this,SIGNAL(move_made(QColor)));
            frontier_array[row][col] = false;
            matched_array[row][col] = false;
        }
    }
    frontier_array[0][0] = true;
    matched_array[0][0] = true;
    find_matching_colors();

    for (int i = 0; i < NUMCOLORS; ++i){
        button_array[i] = new ColorButton(this, color_array[i]);
        button_array[i]->move(80 + i*75, 50*12);
        QObject::connect(button_array[i],SIGNAL(triggered(QColor)),this,SLOT(color_selected(QColor)));
        QObject::connect(button_array[i],SIGNAL(triggered(QColor)),this,SIGNAL(move_made(QColor)));
    }
}

QColor Board::generate_rand_color()
{
    int x = rand() % NUMCOLORS;
    return color_array[x];
}

void Board::reset_board()
{
    for (int row = 0; row < SIDELENGTH; ++row){
        for (int col = 0; col < SIDELENGTH; ++col){
            square_array[row][col]->set_color(generate_rand_color());
            frontier_array[row][col] = false;
            matched_array[row][col] = false;
        }
    }
    frontier_array[0][0] = true;
    matched_array[0][0] = true;
    find_matching_colors(); // add all colors that spawn matching the upper left color to the array
    update();
}

QColor Board::get_first_color()
{
    return square_array[0][0]->get_color();
}

void Board::find_matching_colors()
{
    for (int row = 0; row < SIDELENGTH; ++row){
        for (int col = 0; col < SIDELENGTH; ++col){
            if (matched_array[row][col]){
                match(row, col);
            }
        }
    }
}

void Board::match(int row, int col)
{
    if (left(row, col)) {
        if (!matched_array[row][col - 1]) {
            matched_array[row][col - 1] = true;
            ++squares_claimed;
            match(row, col - 1);
        }
    }
    if (right(row, col)) {
        if (!matched_array[row][col + 1]){
            matched_array[row][col + 1] = true;
            ++squares_claimed;
            match(row, col + 1);
        }
    }
    if (top(row, col)) {
        if (!matched_array[row - 1][col]){
            matched_array[row - 1][col] = true;
            ++squares_claimed;
            match(row - 1, col);
        }
    }
    if (down(row, col)) {
        if (!matched_array[row + 1][col]) {
            matched_array[row + 1][col] = true;
            ++squares_claimed;
            match(row + 1, col);
        }
    }
}
bool Board::check_if_frontier(int row, int col)
{
    if (row <= 0 || row >= 11 || col <= 0 || col >= 11) return true;
    else return !(left(row, col) && right(row,col) && top(row,col) && down(row,col));
}

bool Board::left(int row, int col)
{
    if (col <= 0) return false;
    return square_array[row][col]->get_color() == square_array[row][col - 1]->get_color();
}

bool Board::right(int row, int col)
{
    if (col >= 11) return false;
    return square_array[row][col]->get_color() == square_array[row][col + 1]->get_color();
}

bool Board::top(int row, int col)
{
    if (row <= 0) return false;
    return square_array[row][col]->get_color() == square_array[row - 1][col]->get_color();
}

bool Board::down(int row, int col)
{
    if (row >= 11) return false;
    return square_array[row][col]->get_color() == square_array[row + 1][col]->get_color();
}

void Board::color_selected(QColor color)
{
    squares_claimed = 0;
    square_array[0][0]->set_color(color);
    find_matching_colors();
    for (int row = 0; row < SIDELENGTH; ++row){
        for (int col = 0; col < SIDELENGTH; ++col){
            if (matched_array[row][col]) {
                square_array[row][col]->set_color(color);
            }
        }
    }
    find_matching_colors();
    if (boardIsFlooded()) emit board_complete();
}

bool Board::boardIsFlooded()
{
    for (int row = 0; row < SIDELENGTH; ++row){
        for (int col = 0; col < SIDELENGTH; ++col){
            if (!matched_array[row][col]) return false;
        }
    }
    return true;
}

void Board::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A) emit button_array[0]->triggered(color_array[0]);
    else if (event->key() == Qt::Key_S) emit button_array[1]->triggered(color_array[1]);
    else if (event->key() == Qt::Key_D) emit button_array[2]->triggered(color_array[2]);
    else if (event->key() == Qt::Key_F) emit button_array[3]->triggered(color_array[3]);
    else if (event->key() == Qt::Key_G) emit button_array[4]->triggered(color_array[4]);
    else if (event->key() == Qt::Key_H) emit button_array[5]->triggered(color_array[5]);
}

int Board::squares_claimed_by_move()
{
    return squares_claimed;
}
