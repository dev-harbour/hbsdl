/*
 * Harbour SDL2 (HBSDL) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
 *
 * This software is released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "hbsdl.h"

// SDL_Window *SDL_GetMouseFocus(void);

// Uint32 SDL_GetMouseState( int *x, int *y );
HB_FUNC( SDL_GETMOUSESTATE )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL && hb_param( 2, HB_IT_BYREF ) != NULL )
   {
      int x, y;
      hb_retnint( SDL_GetMouseState( &x, &y ) );
      hb_storni( x, 1 );
      hb_storni( y, 2 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// Uint32 SDL_GetGlobalMouseState(int *x, int *y);
// Uint32 SDL_GetRelativeMouseState(int *x, int *y);
// void SDL_WarpMouseInWindow(SDL_Window * window, int x, int y);
// int SDL_WarpMouseGlobal(int x, int y);
// int SDL_SetRelativeMouseMode(SDL_bool enabled);
// int SDL_CaptureMouse(SDL_bool enabled);
// SDL_bool SDL_GetRelativeMouseMode(void);
// SDL_Cursor *SDL_CreateCursor(const Uint8 * data, const Uint8 * mask, int w, int h, int hot_x, int hot_y);
// SDL_Cursor *SDL_CreateColorCursor(SDL_Surface *surface, int hot_x, int hot_y);
// SDL_Cursor *SDL_CreateSystemCursor(SDL_SystemCursor id);
// void SDL_SetCursor(SDL_Cursor * cursor);
// SDL_Cursor *SDL_GetCursor(void);
// SDL_Cursor *SDL_GetDefaultCursor(void);
// void SDL_FreeCursor(SDL_Cursor * cursor);
// int SDL_ShowCursor(int toggle);
