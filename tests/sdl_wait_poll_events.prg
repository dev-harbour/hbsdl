/*
 *
 */

#include "hbsdl.ch"

PROCEDURE Main()

   LOCAL quit := .F.
   LOCAL sdl
   LOCAL event

   sdl := sdl_CreateWindow( 830, 450, "Test SDL_WaitEvent .AND. SDL_PollEvent", "F1F1F1" )

   DO WHILE( !quit )

      event := sdl_WaitEvent()

      IF( event != NIL )

         DO WHILE( event != NIL )

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

            // Sprawdzamy kolejne zdarzenia w kolejce
            event := sdl_PollEvent()

         ENDDO
      ENDIF

      sdl_BeginDraw( sdl )
         // ...
      sdl_EndDraw( sdl )

   ENDDO

RETURN
