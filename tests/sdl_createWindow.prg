/*
 *
 */

#include "hbsdl.ch"

PROCEDURE Main()

   LOCAL quit := .F.
   LOCAL sdl
   LOCAL event

   sdl := sdl_CreateWindow( 830, 450, "Test Create Window", "" )

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
