#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //TTF initialization 
  if( TTF_Init() < 0)
  {
    std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << "\n";
  }
  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height+extra_space_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Load font
	font = TTF_OpenFont("../fonts/pixel-letters.ttf", 40);
	if ( !font ) {
		std::cerr << "Error loading font: " << TTF_GetError() << "\n";
	}

}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, int const &score) {
  SDL_Rect block;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  // My Code
  // Render Extra Info 
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  block.x = 0;
  block.y = 0;
  block.w = screen_width;
  block.h = extra_space_height;
  SDL_RenderFillRect(sdl_renderer, &block);
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  GameboardPosition(block, food);
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    GameboardPosition(block, point);
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  SDL_Point head_point;
  head_point.x = static_cast<int>(snake.head_x);
  head_point.y = static_cast<int>(snake.head_y);
  GameboardPosition(block, head_point);
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
  UpdateScoreDisplay(score);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

//Calculate position within the game board
void Renderer::GameboardPosition(SDL_Rect &block, const SDL_Point &point)
{
  block.x = point.x * block.w;
  block.y = point.y * block.h + extra_space_height;
}

void Renderer::UpdateScoreDisplay(int score)
{
  SDL_Color color = {0, 0, 0};
  std::string score_str = "SCORE " + std::to_string(score);
  sdl_text_surface = TTF_RenderText_Solid( font, score_str.c_str() , color );
  if ( !sdl_text_surface ) {
	  std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  else 
  {
    SDL_Rect  text_rect = {10,10,sdl_text_surface->w,sdl_text_surface->h};
    sdl_text_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_text_surface);
    SDL_RenderCopy(sdl_renderer, sdl_text_texture, NULL, &text_rect);
  }
}