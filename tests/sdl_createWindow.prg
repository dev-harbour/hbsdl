/*
 * Harbour SDL2 (HBSDL) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
 *
 */

#include "hbsdl.ch"

PROCEDURE Main()

   LOCAL quit := .F.
   LOCAL sdl
   LOCAL event

   sdl := CreateWindow( 830, 450, "Test Create Window", "F1F1F1" )

   DO WHILE( !quit )

      event := sdl_WaitEvent()

      SWITCH( sdl_EventType( event ) )

         CASE SDL_QUIT
            OutStd( e"\nWindow closed" )
            quit := .T.
            EXIT

      ENDSWITCH

      sdl_BeginDraw( sdl )
         // ...
      sdl_EndDraw( sdl )

   ENDDO

RETURN
