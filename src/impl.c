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
C collection
------------------------------------------------------------------------- */
// time_t time( time_t *arg );
HB_FUNC( C_TIME )
{
   if( hb_param( 1, HB_IT_NIL ) != NULL )
   {
      time_t rawtime;
      time( &rawtime );
      hb_retnint( ( HB_LONGLONG ) rawtime );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// double difftime( time_t time_end, time_t time_beg );
HB_FUNC( C_DIFFTIME )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      time_t time_end = ( time_t ) hb_parnint( 1 );
      time_t time_beg = ( time_t ) hb_parnint( 2 );

      double diff = difftime( time_end, time_beg );
      hb_retnd( diff );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void perror( const char *s );
HB_FUNC( C_PERROR )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      perror( hb_parc( 1 ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int system( const char *command );
HB_FUNC( C_SYSTEM )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retni( system( hb_parc( 1 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

