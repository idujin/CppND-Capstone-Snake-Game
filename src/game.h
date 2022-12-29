#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>
#include <future>
#include <chrono>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void TrackingFood(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void MoveFood(const int& target_duration = 10000);
  int GetScore() const;
  int GetSize() const;

 private:
  std::unique_ptr<Snake> snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  std::mutex _mutex;
  std::chrono::time_point<std::chrono::system_clock> _prev_move;
  bool _running{true};
};

#endif