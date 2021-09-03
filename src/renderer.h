#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, int const &score);
  void UpdateWindowTitle(int score, int fps);
  void UpdateScoreDisplay(int score);
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  // SDL objects for text rendering
  SDL_Surface *sdl_text_surface;
  SDL_Texture *sdl_text_texture;
  TTF_Font *font;
 
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  //My code
  //I want to add some extra space in order to display score and other info
  //It will be the same width than the screen, just height needed
  const std::size_t extra_space_height{50};

  void GameboardPosition(SDL_Rect &block, const SDL_Point &point);

  


};

#endif