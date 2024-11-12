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
   LOCAL waitMode := .T.
   LOCAL lastEventTime
   LOCAL currentTime

   sdl := sdl_CreateWindow( 830, 450, "Test Cursor Delay", "F1F1F1" )

   lastEventTime := c_time()

   DO WHILE( !quit )

      currentTime := c_time()

      // Sprawdź, czy należy przełączyć na `SDL_WaitEvent`
      IF( waitMode .OR. c_difftime( currentTime, lastEventTime ) >= 10 )

         // Ustaw kursor na widoczny przed wejściem w tryb oczekiwania
         sdl_setCursorVisible( sdl, .T. )
         event := sdl_WaitEvent()
         IF( event != NIL )
            lastEventTime := c_time() // Ustaw aktualny czas zdarzenia
            waitMode := .F.           // Przełącz na tryb `PollEvent` przez 10 sekund
         ENDIF

      ELSE
         // Polling events przez 10 sekund po zdarzeniu
         DO WHILE( ( event := sdl_PollEvent() ) != NIL )

            lastEventTime := c_time() // Zaktualizuj czas dla każdego zdarzenia

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

         ENDDO
         // Po 10 sekundach bez zdarzeń wróć do trybu `WaitEvent`
         IF( c_difftime( currentTime, lastEventTime ) >= 10 )
            waitMode := .T.
         ENDIF

      ENDIF

      sdl_BeginDraw( sdl )
         // ...
      sdl_EndDraw( sdl )

   ENDDO

RETURN
