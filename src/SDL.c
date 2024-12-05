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

// int SDL_Init( Uint32 flags );
HB_FUNC( SDL_INIT )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_retni( SDL_Init( ( Uint32 ) hb_parni( 1 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int SDL_InitSubSystem(Uint32 flags);
// void SDL_QuitSubSystem(Uint32 flags);
// Uint32 SDL_WasInit(Uint32 flags);
// void SDL_Quit(void);


