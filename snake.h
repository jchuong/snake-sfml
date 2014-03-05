#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <deque>
#include "board.h"

struct Point
{
  int x;
  int y;
};

class Snake
{
  std::deque<Point> body; // All coordinates of the body
  Direction direction;

  public:
  Snake(void);
  Point Get_Head_Point(void);
  Point Get_Tail_Point(void);
  int Get_Length(void);
  bool Move(void);
  void Place_Snake_On_Board(Cell board[40][40]);
  void Remove_Tail(void);
  void Change_Direction(Direction dir);
};
#endif
