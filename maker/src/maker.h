///////////////////////////////////////////////////////////
//// NOTE(Elias): Input 

struct GameButtonState 
{
  B32 was_down; 
  B32 ended_down; 
};

struct GameInput 
{
  union  
  {
    GameButtonState game_buttons[14];
    struct 
    {
      GameButtonState mouse_left; 
      GameButtonState mouse_right; 
      GameButtonState action1;
      GameButtonState action2;
      GameButtonState action3;
      GameButtonState action4;
      GameButtonState action5;
      GameButtonState action6;
      GameButtonState action7;
      GameButtonState action8;
    };
  };
  union 
  {
    S32 mouse_coordinates[2];
    struct 
    {
      S32 mouse_x;
      S32 mouse_y;
    };
  };
};

inline internal B32 key_down(GameButtonState button);
inline internal B32 key_down_single(GameButtonState button);
inline internal B32 key_up_single(GameButtonState button);


///////////////////////////////////////////////////////////
//// NOTE(Elias): Fonts

// TODO(Elias): Perhaps I can improve pxlfnt by 
// encoding sequences (some sortf of compression);
// TODO(Elias): Possbibly Add ASCII id of letter as first byte; 

enum Font_Align_H {
  Font_Align_Left,
  Font_Align_Center_H,
  Font_Align_Right,
};

enum Font_Align_V {
  Font_Align_Top,
  Font_Align_Center_V,
  Font_Align_Bottom,
};

struct Font 
{
  U8 letters[128][32];
};

internal void fnt_render_letter(SDL_Surface *surface, Font *font, 
                                U8 letter_id, V2S32 pos, S32 s, S32 c);

///////////////////////////////////////////////////////////
//// NOTE(Elias): Drawing 

internal void render_background(SDL_Surface *surface); 
internal void draw_box(SDL_Surface *surface, V2S32 pos, S32 w, S32 h, S32 c);

///////////////////////////////////////////////////////////
//// NOTE(Elias): Game 

// IMPORTANT(Elias): 
// Must be initialised to zero when assigning memory!
struct GameState
{
  char *file_path; 
  char letter;
  B8 tiles[16][16];
  V2S32 pos; 
};

internal void game_initialise(GameState *game_state, SDL_Surface *surface, 
                              char letter, char *file_path);
internal void game_update(GameState *game_state, GameInput *game_input, 
                          SDL_Surface *surface, U64 counter);
internal void game_render(SDL_Surface *surface, GameState *game_state);
