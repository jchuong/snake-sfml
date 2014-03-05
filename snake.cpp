#include "snake.h"
#include "board.h"
Snake::Snake() : direction(UP)
{
  Point head;
  head.x = 20;
  head.y = 20;
  body.push_back(head);
  head.y = 21;
  body.push_back(head);
}

Point Snake::Get_Head_Point(void)
{
  return body.front();
}

Point Snake::Get_Tail_Point(void)
{
  return body.back();
}

int Snake::Get_Length(void)
{
  return body.size();
}

bool Snake::Move(void)
{
  Point newHead = Get_Head_Point();
  switch (direction)
  {
    case UP:
    {
      newHead.y -= 1;
      break;
    }
    case DOWN:
    {
      newHead.y += 1;
      break;
    }
    case RIGHT:
    {
      newHead.x += 1;
      break;
    }
    case LEFT:
    {
      newHead.x -= 1;
      break;
    }
    default:
    {
      return false;
    }
  }
  // If out of bounds, do nothing, game will be over
  if (newHead.y < 0 || newHead.y >= 40 || newHead.x < 0 || newHead.x >= 40)
  {
    return false;
  }

  body.push_front(newHead);
  return true;
}

void Snake::Place_Snake_On_Board(Cell board[40][40])
{
   for (int i = 0; i < Get_Length(); ++i)
   {
     int x = body[i].x;
     int y = body[i].y;
     board[x][y] = SNAKE;
   }
}

void Snake::Remove_Tail()
{
  body.pop_back();
}

void Snake::Change_Direction(Direction dir)
{
  // Must not allow complete reverse of direction
  if ((direction == UP && dir == DOWN) ||
      (direction == LEFT && dir == RIGHT) ||
      (direction == RIGHT && dir == LEFT) ||
      (direction == DOWN && dir == UP))
  {
    return;
  }
  direction = dir;
}
