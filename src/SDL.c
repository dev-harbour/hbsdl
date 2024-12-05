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

/* -------------------------------------------------------------------------
Harbour Implementation
------------------------------------------------------------------------- */
// void sdl_print_initialized_subsystems( void )
HB_FUNC( SDL_PRINT_INITIALIZED_SUBSYSTEMS )
{
   Uint32 subsystems = SDL_WasInit( 0 );

   if( subsystems & SDL_INIT_TIMER )
      printf( "SDL_INIT_TIMER is initialized.\n" );
   if( subsystems & SDL_INIT_AUDIO )
      printf( "SDL_INIT_AUDIO is initialized.\n" );
   if( subsystems & SDL_INIT_VIDEO )
      printf( "SDL_INIT_VIDEO is initialized.\n" );
   if( subsystems & SDL_INIT_JOYSTICK )
      printf( "SDL_INIT_JOYSTICK is initialized.\n" );
   if( subsystems & SDL_INIT_HAPTIC )
      printf( "SDL_INIT_HAPTIC is initialized.\n" );
   if( subsystems & SDL_INIT_GAMECONTROLLER )
      printf( "SDL_INIT_GAMECONTROLLER is initialized.\n" );
   if( subsystems & SDL_INIT_EVENTS )
      printf( "SDL_INIT_EVENTS is initialized.\n" );
   if( subsystems & SDL_INIT_SENSOR )
      printf( "SDL_INIT_SENSOR is initialized.\n" );
}

// int SDL_InitFlags( [ flags... ] )
HB_FUNC( SDL_INITFLAGS )
{
   Uint32 flags = 0;
   int argc = hb_pcount();

   for( int i = 1; i <= argc; i++ )
   {
      if( hb_param( i, HB_IT_NUMERIC ) != NULL )
      {
         flags |= ( Uint32 ) hb_parni( i );
      }
      else
      {
         HB_ERR_ARGS();
      }
   }
   hb_retni( flags );
}

/* -------------------------------------------------------------------------
SDL API
------------------------------------------------------------------------- */
// int SDL_Init( Uint32 flags );
HB_FUNC( SDL_INIT )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
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

// Uint32 SDL_WasInit( Uint32 flags );
HB_FUNC( SDL_WASINIT )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      hb_retni( SDL_WasInit( ( Uint32 ) hb_parni( 1 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
// void SDL_Quit( void );


