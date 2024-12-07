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

   sdl := CreateWindow( 830, 450, "Test SDL_WaitEvent .AND. SDL_PollEvent", "F1F1F1" )

   DO WHILE( !quit )

      sdl_WaitEvent( @event )

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
            sdl_PollEvent( @event )

         ENDDO
      ENDIF

      sdl_BeginDraw( sdl )
         // ...
      sdl_EndDraw( sdl )

   ENDDO

RETURN

