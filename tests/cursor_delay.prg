/*
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

#include "hbsdl.ch"
/* TODO */
PROCEDURE Main()

   LOCAL quit := .F.
   LOCAL sdl
   LOCAL event
   LOCAL waitMode := .T.
   LOCAL lastEventTime
   LOCAL currentTime

   sdl := CreateWindow( 830, 450, "Test Cursor Delay", "F1F1F1" )

   lastEventTime := c_time( NIL )

   DO WHILE( !quit )

      currentTime := c_time( NIL )

      IF( waitMode .OR. c_difftime( currentTime, lastEventTime ) >= 10 )

         // Wyświetl kursor na stałe i włącz tryb `WaitEvent`
         sdl_setCursorVisible( sdl, .T. )
         sdl_WaitEvent( @event)

         IF( event != NIL )
            lastEventTime := currentTime // Ustaw czas dla aktywności
            waitMode := .F.              // Przełącz na tryb `PollEvent` przez 10 sekund
         ENDIF

      ELSE
         // Przechwytywanie zdarzeń w trybie `PollEvent`
         DO WHILE( sdl_PollEvent( @event ) )

            lastEventTime := currentTime // Zaktualizuj czas dla aktywności

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
      ENDIF
      // Po 10 sekundach bez zdarzeń wróć do trybu `WaitEvent`
      IF( c_difftime( c_time( NIL ), lastEventTime ) >= 10 )
         waitMode := .T.
      ENDIF

      sdl_BeginDraw( sdl )
         // ...
      sdl_EndDraw( sdl )

   ENDDO

RETURN
