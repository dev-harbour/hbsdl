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

   sdl := CreateWindow( 830, 450, "Test sdl_waitEvent", "F1F1F1" )

   DO WHILE( !quit )

      event := sdl_WaitEvent()

      SWITCH( sdl_EventType( event ) )

         CASE SDL_QUIT
            OutStd( e"\nWindow closed" )
            quit := .T.
            EXIT

         CASE SDL_WINDOWEVENT

            IF sdl_EventWindowEvent( event ) == SDL_WINDOWEVENT_CLOSE
               OutStd( e"\nWindow close requested" )
               quit := .T.
            ENDIF
            EXIT

         CASE SDL_KEYDOWN

            IF sdl_EventKeyKeysymSym( event ) == SDLK_ESCAPE
               OutStd( e"\nEsc pressed" )
               quit := .T.
            ELSE
               OutStd( e"\nOther key pressed (key: ", sdl_EventKeyKeysymSym( event ), ")" )
            ENDIF
            EXIT

         OTHERWISE
            OutStd( e"\nUnhandled event (type:", sdl_EventType( event ), ")" )

      ENDSWITCH

      sdl_BeginDraw( sdl )
         // ...
      sdl_EndDraw( sdl )

   ENDDO

RETURN
