#ifndef __BOARD_H__
#define __BOARD_H__
#include <SFML/Window.hpp>

enum Cell {
  EMPTY,
  FOOD,
  SNAKE,
};

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

class Snake;
class Board {
  Snake* snake;
  Cell board[40][40];
  Direction direction_selected;

  private:
    void Place_Food();
  public:
    Board();
    ~Board();
    bool Update_Board();
    Cell Get_Cell(int x, int y);
    void Change_Direction(const sf::Event& event);
    int Get_Length(void);
    int Get_Score(void);
};
#endif
