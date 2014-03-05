#include "board.h"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "snake.h"

Board::Board() {
  snake = new Snake();

  for (int i = 0; i < 40; ++i) {
    for (int j = 0; j < 40; ++j) {
      board[i][j] = EMPTY;
    }
  }

  snake->Place_Snake_On_Board(board);
  srand(time(0));
  Place_Food();
  direction_selected = UP;
}

Board::~Board() {
  delete snake;
}

void Board::Place_Food() {
  // Not exactly efficient if the board is large and the player takes up most of the space
  // but should be good enough
  while (true) {
    int x = rand() % 40;
    int y = rand() % 40;
    Cell cell = board[x][y];
    if (cell == EMPTY) {
      board[x][y] = FOOD;
      return;
    }
  }
}

// Returns false if the game is over
bool Board::Update_Board() {
  snake->Change_Direction(direction_selected);
  if(!snake->Move())
  {
    return false;
  }
  
  // The only changing positions will be the head and tail
  Point body = snake->Get_Head_Point();
  Cell new_head = board[body.x][body.y];
  if (new_head == EMPTY)
  {
    board[body.x][body.y] = SNAKE;
    body = snake->Get_Tail_Point();
    board[body.x][body.y] = EMPTY;
    // Now remove tail
    snake->Remove_Tail();
  }
  else if (new_head == SNAKE)
  {
    // Game over
    return false;
  }
  else if (new_head == FOOD)
  {
    // extend body, replace food
    Place_Food();
    board[body.x][body.y] = SNAKE;
  }
  return true;
}

Cell Board::Get_Cell(int x, int y) {
  assert(x >= 0 && x < 40);
  assert(y >= 0 && y < 40);
  return board[x][y];
}

void Board::Change_Direction(const sf::Event& event)
{
  switch(event.key.code)
  {
    case sf::Keyboard::Up:
      direction_selected = UP;
      break;
    case sf::Keyboard::Right:
      direction_selected = RIGHT;
      break;
    case sf::Keyboard::Down:
      direction_selected = DOWN;
      break;
    case sf::Keyboard::Left:
      direction_selected = LEFT;
      break;
    default:
      break;
  }
}

int Board::Get_Length(void)
{
  return snake->Get_Length();
}

int Board::Get_Score(void)
{
  return Get_Length() - 2; // Original two body parts don't count
}
