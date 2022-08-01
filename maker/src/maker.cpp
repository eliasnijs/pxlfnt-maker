///////////////////////////////////////////////////////////
//// NOTE(Elias): Keyboard

inline internal B32 
key_down(GameButtonState button)
{
  return(button.ended_down);
}

inline internal B32 
key_down_single(GameButtonState button)
{
  return(button.ended_down && !button.was_down);
}

inline internal B32 
key_up_single(GameButtonState button)
{
  return(!button.ended_down && button.was_down);
} 

///////////////////////////////////////////////////////////
//// NOTE(Elias): Files

internal void
file_read(FILE *file_connection, S32 *length, U8 *storage) 
{
  if (!storage) {
    fseek(file_connection, 0, SEEK_END);
    *length = ftell(file_connection);
    fseek(file_connection, 0, 0);
  } else {
    fread(storage, *length, 1, file_connection);
  }
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Letter

internal void
fnt_ppmletter_bytes_compress(U8 *pixels, U8 *letter_bits)
{
  S32 i, j, i_letter, i_byte, i_bit, c_threshold;
  B32 active;
  U8 *pxl_d; 
  FILE *file; 
  
  c_threshold = 0xFE;
  i = 0; i_letter = 0;
  while (i < 16)
  {
    j = 0;
    while (j < 16)
    {
      i_byte = i_letter / 8;
      i_bit  = i_letter - (i_byte * 8); 
      active = (pixels[i*16*3 + j*3] >= c_threshold) && 
               (pixels[i*16*3 + j*3 + 1] >= c_threshold) &&
               (pixels[i*16*3 + j*3 + 2] >= c_threshold);
      if (active)
      {
        letter_bits[i_byte] |= 1 << i_bit;
      }
      ++j; ++i_letter;
    }
    ++i;
  } 
} 

///////////////////////////////////////////////////////////
//// NOTE(Elias): Font

internal void
fnt_pxlfnt_load(char *path, Font *font)
{
  FILE *file = fopen(path, "rb");
  if (file) 
  {
    S32 file_length = ArrayCount(font->letters) * 
                      ArrayCount(font->letters[0]);
    if (file_length == 4096)
    {
      file_read(file, &file_length, (U8 *)font->letters[0]); 
    }
    else
    {
      // TODO(Elias): logging
      printf("faile to load font, file is corrupted!");
    }
    fclose(file); 
  } 
  else 
  {
    // TODO(Elias): logging
    printf("failed to open file for reading!\n");
  }
}

internal void
fnt_render_letter(SDL_Surface *surface, Font *font, U8 letter_id, V2S32 pos, S32 s, S32 c)
{
  S32 i_d, j_d, i_letter, 
      i_letter_i, i_letter_j,
      i_byte, i_bit;
  B32 active;
  U8 *pxl_d, *letter; 
 
  letter = font->letters[letter_id];
  i_d = pos.y, i_letter_i = 0;
  while (i_d < pos.y + 16 * s && i_d < surface->h)
  {
    j_d = pos.x; i_letter_j = 0;
    while (j_d < pos.x + 16 * s && j_d < surface->w)
    {
      i_letter = i_letter_i*16 + i_letter_j;
      i_byte = i_letter / 8;
      i_bit  = i_letter - (i_byte * 8); 
      active = letter[i_byte] & (1 << i_bit);
      if (active && i_d > 0 && j_d > 0)
      {
        pxl_d = (U8 *)surface->pixels + 
                (i_d*surface->pitch) + 
                (j_d*surface->format->BytesPerPixel);
        *(U32 *)pxl_d = c;
      } 
      ++j_d; 
      if (j_d % s == 0)
        ++i_letter_j;
    }
    ++i_d;
    if (i_d % s == 0)
      ++i_letter_i;
  } 
} 


// render string (don't forget newlines)
// - param : 
//      [x] font, [x] txt, [x] pos, [x] scale, [x] color, [x] alignment, 
//      [x] kerning (space between letters), 
//      [ ] leading (space from baseline to next baseline)
//  - font anatomy:
//      https://www.oakton.edu/user/2/rcapacci/typography/images/typography-blueprint.png

internal void
fnt_render(SDL_Surface *surface, Font *font, char *txt,
           V2S32 pos, S32 s, U32 c, S32 krn, S32 ld,
           Font_Align_H a_h, Font_Align_V a_v)
{
  S32 i, l, l_c, nl_cnt, w, h;
  V2S32 pos_c, offset = {};

  // NOTE(Elias): Determine the 
  // length of the text and the amount of lines
  i = 0; l = 0; nl_cnt = 0; l_c = 0;
  while(txt[i] != '\0')
  {
    if (txt[i] == '\n')
    {
      l = Max(l, l_c);
      ++nl_cnt;
    }
    ++l_c; ++i;
  }
  l = Max(l, l_c);

  // NOTE(Elias): Set Kerning and leading to more correct values
  // TODO(Elias): Seek a better way to define this offset.
  krn += -32; 
  ld += -32;

  // NOTE(Elias): Calculate Horizontal Alignment
  w = l*16*s + (l-1)*krn;
  switch (a_h)
  {
    case(Font_Align_Left): 
    {
      offset.x = 0; 
    } break;
    case(Font_Align_Center_H): 
    {
      offset.x = -w/2; 
    } break;
    case(Font_Align_Right):
    {
      offset.x = -w; 
    } break;
  }
  
  // NOTE(Elias): Calculate Vertical Alignment
  h = nl_cnt*(16*s); 
  switch (a_v)
  {
    case(Font_Align_Top): 
    {
      offset.y = 0; 
    } break;
    case(Font_Align_Center_V): 
    {
      offset.y = -(s*5 - h/2); 
    } break;
    case(Font_Align_Bottom):
    {
      offset.y = -(s*16 - h); 
    } break;
  } 

  // NOTE(Elias): Draw Text 
  pos_c = pos + offset;
  i = 0;
  while (txt[i] != '\0')
  {
    fnt_render_letter(surface, font, txt[i], pos_c, s, c);
    pos_c = pos_c + v2s32(krn + 16*s, 0);
    ++i;
  }
}



///////////////////////////////////////////////////////////
//// NOTE(Elias): Drawing Functions

internal void
render_background(SDL_Surface *surface)
{
  S32 i_bg_col = 0, w_pxl = SCREEN_HEIGHT / 16;
  S32 bytes_per_pixel = surface->format->BytesPerPixel; for (S32 row = 0;
       row < surface->h;
       ++row)
  {
    for (S32 column = 0;
         column < surface->w;
         ++column)
    {
      if (column % w_pxl == 0) 
      {
        i_bg_col = ((i_bg_col + 1) % ArrayCount(BG_COLORS));
      }
      U8 *p = (U8 *)surface->pixels + (row * surface->pitch) + (column * surface->format->BytesPerPixel);
      *(U32 *)p = BG_COLORS[i_bg_col];
    }
    if (row % w_pxl == 0) 
    {
      i_bg_col = ((i_bg_col + 1) % ArrayCount(BG_COLORS));
    }
  }
}

internal void 
draw_box(SDL_Surface *surface, V2S32 pos, S32 w, S32 h, S32 c)
{
  for (S32 row = ClampBot(0, pos.y);
       (row < pos.y + h) && (row < surface->h);
       ++row)
  {
    for (S32 column = ClampBot(0, pos.x);
         (column < pos.x + w) && (column < surface->w);
         ++column)
    {
      U8 *p = (U8 *)surface->pixels + 
              (row * surface->pitch) + 
              (column * surface->format->BytesPerPixel);
      *(U32 *)p = c;
    }
  }
}

internal void 
draw_box_overlay(SDL_Surface *surface, V2S32 pos, S32 w, S32 h, U8 c)
{
  for (S32 row = ClampBot(0, pos.y);
       (row < pos.y + h) && (row < surface->h);
       ++row)
  {
    for (S32 column = ClampBot(0, pos.x);
         (column < pos.x + w) && (column < surface->w);
         ++column)
    {
      U8 *p = (U8 *)surface->pixels + 
              (row * surface->pitch) + 
              (column * surface->format->BytesPerPixel);
      
      U8 r = *(p + 0);
      if (r < 128)
        r += c;
      else
        r -= c;
          
      U8 g = *(p + 1);
      if (g < 128)
        g += c;
      else
        g -= c;

      U8 b = *(p + 2);
      if (b < 128)
        b += c;
      else
        b -= c;
    
      *(U32 *)p = (r << 16) + (g << 8) + b;
    }
  }
}


///////////////////////////////////////////////////////////
//// NOTE(Elias): Pxlfont 

internal void
letter_save(char c, B8 tiles[16][16], char *path)
{
  S32 i, j, i_byte, i_bit;
  U8 bytes[32] = {};
  FILE *file;

  i_byte = 0, i_bit = 0;
  for (i = 0; 
       i < 16; 
       ++i)
  {
    for (j = 0; 
         j < 16; 
         ++j)
    {
      bytes[i_byte] |= ((tiles[i][j]? 1 : 0) << i_bit);
      ++i_bit;
      if (j % 8 == 7)
      {
        ++i_byte;
        i_bit = 0;
      }
    }
  }

  file = fopen(path, "r+b");
  if (file)
  {
    fseek(file, 32 * (S32)c, SEEK_SET);
    fwrite(bytes, sizeof(char), sizeof(bytes), file); 
    fclose(file); 
  }
  else
  {
    // TODO(Elias): logging
  }
}

internal void
letter_delete(B8 tiles[16][16])
{
  S32 i;
  for (i = 0; 
       i < 16*16; 
       ++i)
  {
    *((B8 *)tiles + i) = 0;
  }
}

internal void
letter_load(char c, B8 tiles[16][16], char *path)
{
  FILE* file; 
  S32 i, j, i_byte, i_bit;
  U8 bytes[32] = {};
  
  file = fopen(path, "rb");
  if (file)
  {
    fseek(file, 32 * (S32)c, SEEK_SET);
    fread(&bytes[0], 1, 32, file);
    fclose(file); 
  }
  else
  {
    // TODO(Elias): logging
    goto err1; // NOTE(Elias): ERROR JUMP
  }

  i_byte = 0; i_bit = 0;
  for (i = 0; 
       i < 16;
       ++i)
  {
    for (j = 0; 
         j < 16;
         ++j)
    {
      tiles[i][j] = bytes[i_byte] & (1 << i_bit);
      ++i_bit;
      if (j % 8 == 7)
      {
        ++i_byte;
        i_bit = 0;
      }
    }
  }
err1: // NOTE(Elias): Wrong command line arguments 
  return;
} 

///////////////////////////////////////////////////////////
//// NOTE(Elias): Tiles 

internal V2S32
tileindices_to_screencoord(S32 i, S32 j)
{
  S32 w_tile = SCREEN_HEIGHT / 16;
  V2S32 result = { j*w_tile, i*w_tile }; return(result);
}

internal V2S32
screencoord_to_tileindices(S32 x, S32 y)
{
  S32 w_tile = SCREEN_HEIGHT / 16;
  V2S32 result = { y/w_tile, x/w_tile };
  return(result);
}

internal void
render_tiles(SDL_Surface *surface, B8 tiles[16][16], S32 c)
{
  S32 i, j, w_tile;
  V2S32 pos;

  w_tile = SCREEN_HEIGHT / 16;
  for (i = 0; 
       i < 16;
       ++i)
  {
    for (j = 0; 
         j < 16;
         ++j)
    {
      if (tiles[i][j])
      {
        pos = tileindices_to_screencoord(i, j);
        draw_box(surface, pos, w_tile, w_tile, c);
      }
    }
  }
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Game

internal void
game_initialise(GameState *game_state, SDL_Surface *surface, 
                char letter, char *file_path)
{
  game_state->file_path = file_path;
  game_state->letter = letter;
  letter_load(game_state->letter, game_state->tiles, game_state->file_path);
} 

internal void
game_update(GameState *game_state, GameInput *game_input, 
            SDL_Surface *surface, U64 counter)
{ 
  
  V2S32 ij = screencoord_to_tileindices(
      game_input->mouse_x, game_input->mouse_y);
 
  game_state->pos = tileindices_to_screencoord(ij.x, ij.y);
  
  if (key_down(game_input->mouse_left))
  {
    game_state->tiles[ij.x][ij.y] = 1;
  }
  if (key_down(game_input->mouse_right))
  {
    game_state->tiles[ij.x][ij.y] = 0;
  }

  // MUST HAVES:  
  // action1: SAVE ~ S
  // action2: RELOAD ~ R
  // action3: DELETE ~ D
  if (key_down_single(game_input->action1))
  {
    letter_save(game_state->letter, game_state->tiles, game_state->file_path);
  }
  if (key_down_single(game_input->action2))
  {
    letter_load(game_state->letter, game_state->tiles, game_state->file_path);
  }
  if (key_down_single(game_input->action3))
  {
    letter_delete(game_state->tiles);
  }

  // OPIONAL TODOS:  
  // (action3: UNDO)
  // (action4: REDO)
}

internal void
game_render(SDL_Surface *surface, GameState *game_state)
{
  render_background(surface); 
  render_tiles(surface, game_state->tiles, 0x00000);

  S32 w_tile = SCREEN_HEIGHT / 16;
  draw_box_overlay(surface, game_state->pos + v2s32(0,1), w_tile, w_tile, 64);
}


