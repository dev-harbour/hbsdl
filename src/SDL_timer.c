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

// Uint32 SDL_GetTicks(void);
// Uint64 SDL_GetTicks64(void);
// Uint64 SDL_GetPerformanceCounter(void);
// Uint64 SDL_GetPerformanceFrequency(void);

// void SDL_Delay( Uint32 ms );
HB_FUNC( SDL_DELAY )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      SDL_Delay( hb_parni( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// SDL_TimerID SDL_AddTimer(Uint32 interval, SDL_TimerCallback callback, void *param);

// SDL_bool SDL_RemoveTimer( SDL_TimerID id );
HB_FUNC( SDL_REMOVETIMER )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      SDL_TimerID id = ( SDL_TimerID ) hb_parni( 1 );
      hb_retl( ( int ) SDL_RemoveTimer( id ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}



