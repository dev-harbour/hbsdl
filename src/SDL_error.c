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

// int SDL_SetError(const char *fmt, ... )
HB_FUNC( SDL_SETERROR )
{
   if( hb_param( 1, HB_IT_STRING) != NULL )
   {
      const char *fmt = hb_parc( 1 );
      char buffer[ 512 ];
      int argc = hb_pcount();
      int offset = snprintf( buffer, sizeof( buffer ), "%s", fmt );

      for( int i = 2; i <= argc; i++ )
      {
         if( hb_param( i, HB_IT_STRING ) != NULL )
         {
            const char *arg = hb_parc( i );
            offset += snprintf( buffer + offset, sizeof( buffer ) - offset, " %s", arg );
         }
         else if( hb_param( i, HB_IT_NUMERIC ) != NULL )
         {
            offset += snprintf( buffer + offset, sizeof( buffer ) - offset, " %g", hb_parnd( i ) );
         }
         else
         {
            HB_ERR_ARGS();
         }
      }
      int result = SDL_SetError( "%s", buffer );
      hb_retni( result );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// const char *SDL_GetError( void );
HB_FUNC( SDL_GETERROR )
{
   hb_retc( SDL_GetError() );
}

// void SDL_ClearError( void );
HB_FUNC( SDL_CLEARERROR )
{
   SDL_ClearError();
}

// int SDL_Error( SDL_errorcode code );
HB_FUNC( SDL_ERROR )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      hb_retni( SDL_Error( hb_parni( 1 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
