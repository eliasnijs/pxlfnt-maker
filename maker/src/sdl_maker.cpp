#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdint.h>

#include "baselayer.h"
#include "baselayer.cpp"
#include "config.h"

#include "maker.h"
#include "maker.cpp"
#include "sdl_maker.h"


///////////////////////////////////////////////////////////
//// NOTE(Elias): Global Variables

global_variable B32 global_running = true;

///////////////////////////////////////////////////////////
//// NOTE(Elias): SDL Input 

internal void
SDL_process_keyboard_input(GameButtonState *state, B32 is_down)
{
  state->was_down = state->ended_down;
  state->ended_down = is_down;
}

internal void
SDL_process_keyboard(GameInput *game_input)
{
  const U8 *state = SDL_GetKeyboardState(0); 
  SDL_process_keyboard_input(&game_input->action1, 
                             state[SDL_SCANCODE_S]); 
  SDL_process_keyboard_input(&game_input->action2, 
                             state[SDL_SCANCODE_R]); 
  SDL_process_keyboard_input(&game_input->action3, 
                             state[SDL_SCANCODE_D]); 
} 

///////////////////////////////////////////////////////////
//// NOTE(Elias): SDL Basics

internal B32 
SDL_initialise(SDL_Context *sdl_context)
{
  B32 success = true;
  if (SDL_Init(SDL_INIT_VIDEO) >= 0)
  {
    sdl_context->window = SDL_CreateWindow(PROGRAM_NAME, 
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (sdl_context->window)
    {
      sdl_context->surface = SDL_GetWindowSurface(sdl_context->window);
      SDL_FillRect(sdl_context->surface, 0, 
                   SDL_MapRGB(sdl_context->surface->format, 0x00 , 0x00 , 0x00 ));
      SDL_UpdateWindowSurface(sdl_context->window);
    }
    else
    {
      // TODO (Elias): logging
      success = false;
    }
  }
  else
  {
    // TODO (Elias): logging
    success = false;
  }
  return(success);
}

internal void 
SDL_die(SDL_Context *sdl_context)
{
  SDL_FreeSurface(sdl_context->surface);
  SDL_DestroyWindow(sdl_context->window);
  SDL_Quit();
}

internal void
SDL_process_pending_messages(GameInput *game_input)
{
  SDL_Event sdl_event; 
  while (SDL_PollEvent(&sdl_event))
  {
    B32 key_is_down = false;
    switch (sdl_event.type) {
      case (SDL_QUIT): 
      {
        global_running = false;
      } break;
      case (SDL_MOUSEMOTION): 
      {
        game_input->mouse_x = sdl_event.motion.x; 
        game_input->mouse_y = sdl_event.motion.y;
      } break;
      case (SDL_MOUSEBUTTONDOWN):
        key_is_down = true;
      case (SDL_MOUSEBUTTONUP):
      {
        U8 button = sdl_event.button.button;
        if (button == SDL_BUTTON_LEFT) 
        {
          SDL_process_keyboard_input(&game_input->mouse_left, key_is_down);
        }
        else if (button == SDL_BUTTON_RIGHT)
        {
          SDL_process_keyboard_input(&game_input->mouse_right, key_is_down);
        }
      } break;
    }
  }
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Commandline Arguments 
internal void
help(void)
{
  printf("   \n");
  printf("   Pxlfnt Maker\n");
  printf("   \n");
  printf("   Syntax: ./pxlfnt-maker <character> <pxlfnt file>\n");
  printf("   <character>      ASCII character to edit/make\n");
  printf("   <pxlfnt file>    path to the font file to edit\n");
  printf("    \n");
  printf("   Keybinds:\n");
  printf("   mouse L          Draw pixel\n");
  printf("   mouse R          Erase pixel\n");
  printf("   D                Clear all pixels\n");
  printf("   S                Save letter to pxlfnt file\n");
  printf("   R                Reload letter from pxlfnt file\n");
  printf("   \n");
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): MAIN


S32 
main(S32 argc, char *argv[])
{
  char c, *file_path;
  
  FILE* file;
  S32 file_length;
  char create_file_answ;

  SDL_Context sdl_context = {}; 
  
  S32 start_tick; 
  U64 counter;
  
  GameInput game_input = {}; 
  GameState *game_state;

  // NOTE(Elias): Gather Commandline Arguments
  if (argc == 1)
  {
    // TODO(Elias): Logging
    printf("no arguments were provided!\n");
    goto err1; // NOTE(Elias): ERROR JUMP
  }
  if (argc == 2) 
  {
    if (strcmp(argv[1], "--help") == 0 || 
        strcmp(argv[1], "-h") == 0)
    {
      help();
    }
    else 
    {
      // TODO(Elias): Logging
      printf("wrong number of arguments was provided!\n");
    }
    goto err1; // NOTE(Elias): ERROR JUMP
  }
  if (argc > 3)
  {
    // TODO(Elias): Logging
    printf("wrong number of arguments was provided!\n");
    goto err1; // NOTE(Elias): ERROR JUMP
  }
  if (strlen(argv[1]) != 1)
  {
    printf("failed to edit... character argument is longer then 1!\n");
    goto err1; // NOTE(Elias): ERROR JUMP
  }
  c = argv[1][0];
  file_path = argv[2];
  
  // check if file exists
  file = fopen(file_path, "r");
  if (file)
  {
    file_read(file, &file_length, 0);
    fclose(file);
    if (file_length != 4096)
    {
      printf("pxlfnt file is corrupted!\n");
      goto err1; // NOTE(Elias): ERROR JUMP
    }
  }
  else
  {
    printf("File does not exist. Would you like to create it? [y/n]? ");
    scanf("%c", &create_file_answ);
    if (create_file_answ == 'y' || 
        create_file_answ == 'Y')
    {
      file = fopen(file_path, "wb");
      if (file)
      {
        U8 bytes[4096] = {};
        fwrite(bytes, sizeof(char), sizeof(bytes), file); 
        fclose(file);
      } 
    }
    else 
    {
      goto err1; // NOTE(Elias): ERROR JUMP
    }
  }


  // NOTE(Elias): Initliase SDL 
  if (! SDL_initialise(&sdl_context))
  {
    // TODO(Elias): Logging
    printf("failed to initliase SDL\n");
    goto err2; // NOTE(Elias): ERROR JUMP
  }

  // NOTE(Elias): Initialise Gme
  game_state = (GameState *)calloc(1, sizeof(GameState));
  if (!game_state)
  {
    // TODO(Elias): logging
    goto err3; // NOTE(Elias): ERROR JUMP
  } 
  game_initialise(game_state, sdl_context.surface, c, file_path); 
    
  // NOTE(Elias): Game loop
  counter = 0;
  while (global_running)
  { 
    start_tick = SDL_GetTicks(); 
    
    SDL_process_pending_messages(&game_input); 
    SDL_process_keyboard(&game_input);
    game_update(game_state, &game_input, sdl_context.surface, counter);
    game_render(sdl_context.surface, game_state); 
    SDL_UpdateWindowSurface(sdl_context.window); 
    
    // NOTE(Elias): cap framerate
    if ((1000.0 / FPS) > (SDL_GetTicks() - start_tick)) 
    {
      SDL_Delay((1000.0 / FPS) - (F64)(SDL_GetTicks() - start_tick));
    }
  }
  
  free(game_state);

err3: // NOTE(Elias): Memory allocation for `game_state` failed
err2: // NOTE(Elias): SDL initialisation failed
  SDL_die(&sdl_context);
err1: // NOTE(Elias): Wrong command line arguments 
  
  return(0);
} 
