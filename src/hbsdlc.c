/*
 * Harbour SDL2 (HBSDL) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
 *
 */

#include "hbsdl.h"

/* -------------------------------------------------------------------------
C collection of functions
------------------------------------------------------------------------- */
HB_FUNC( C_TIME )
{
   time_t rawtime;
   time( &rawtime );
   hb_retnint( ( HB_LONGLONG ) rawtime );
}

HB_FUNC( C_DIFFTIME )
{
   time_t time_end = ( time_t ) hb_parnint( 1 );
   time_t time_beg = ( time_t ) hb_parnint( 2 );

   double diff = difftime( time_end, time_beg );
   hb_retnd( diff );
}
