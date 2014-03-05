#include <cassert>
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "board.h"

enum State
{
  START,
  PLAYING,
  GAMEOVER,
};

Board* board;
static State Game_State = START;

void Initialize_Game(void)
{
  board = new Board();
}

void Cleanup(void)
{
  if (board != 0)
  {
    delete board;
  }
}

void Restart_Game(void)
{
  Cleanup();
  Initialize_Game();
  Game_State = PLAYING;
}

void Draw_Board(sf::RenderWindow& window)
{
  for (int i = 0; i < 40; ++i)
  {
    for (int j = 0; j < 40; ++j)
    {
      Cell cell = board->Get_Cell(i, j);
      sf::RectangleShape cell_shape(sf::Vector2f(10, 10));
      cell_shape.setOutlineColor(sf::Color(0, 0, 0));
      cell_shape.setOutlineThickness(1);
      cell_shape.setPosition(i * 10, j * 10);
      switch (cell)
      {
        case EMPTY:
        {
          cell_shape.setFillColor(sf::Color(255, 255, 255));
          break;
        }
        case SNAKE:
        {
          cell_shape.setFillColor(sf::Color(0, 0, 255));
          break;
        }
        case FOOD: {
          cell_shape.setFillColor(sf::Color(255, 0, 0));
          break;
        }
        default:
        {
          throw;
        }
      }
      window.draw(cell_shape);
    }
  }
}

int main(void)
{
  sf::Font font;
  font.loadFromFile("Arial.ttf");
  sf::RenderWindow window(sf::VideoMode(400, 400), "Snake Copy!");
  window.setFramerateLimit(120);
  sf::RectangleShape background(sf::Vector2f(400, 400));
  background.setFillColor(sf::Color(255, 255, 255));

  sf::Clock clock;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      } else if (event.type == sf::Event::KeyPressed)
      {
        switch (Game_State)
        {
          case START:
          {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
              Game_State = PLAYING;
              Initialize_Game();
            }
            break;
          }
          case PLAYING:
          {
            if (event.type == sf::Event::KeyPressed)
            {
              board->Change_Direction(event);
            }
            break;
          }
          case GAMEOVER:
          {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
              {
                Game_State = PLAYING;
                Restart_Game();
              }
            break;
          }

          default:
            return 1;
        }
      }
    }
    if (Game_State == PLAYING)
    {
      assert(board);
      sf::Time time = clock.getElapsedTime();
      if (time.asMilliseconds() >= (std::max(200, 500 - 10 * board->Get_Length())))
      {
        if(!board->Update_Board())
        {
          // Game over
          Game_State = GAMEOVER;
        }
        clock.restart();
      }
    }
    window.clear();
    window.draw(background);
    switch (Game_State)
    {
      case GAMEOVER:
      {
        sf::Text score_Text("Score: " + std::to_string(board->Get_Score()), font);
        score_Text.setColor(sf::Color::Black);
        window.draw(score_Text);
        sf::Text text("Press Space to Restart", font);
        text.setCharacterSize(30);
        text.setColor(sf::Color::Black);
        text.setPosition(0, 30);
        window.draw(text);
        break;
      }
      case START:
      {
        sf::Text text("Press Space to begin", font);
        text.setCharacterSize(30);
        text.setColor(sf::Color::Black);
        window.draw(text);
        break;
      }
      case PLAYING:
      {
        Draw_Board(window);
        break;
      }
    }
    if (Game_State == PLAYING)
    {
      Draw_Board(window);
    }
    window.display();
  }

  Cleanup();
  return 0;
}

