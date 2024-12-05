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

PROCEDURE Main()

   LOCAL nInitFlags
   LOCAL lQuit := .F.
   LOCAL nWindowFlags
   LOCAL pWindow
   LOCAL nRendererFlags
   LOCAL pRenderer
   LOCAL pEvent

   SDL_SetHint( SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0" )

   nInitFlags := SDL_InitFlags( SDL_INIT_VIDEO, SDL_INIT_EVENTS )
   SDL_Init( nInitFlags )

   nWindowFlags := SDL_WindowFlags( SDL_WINDOW_SHOWN, SDL_WINDOW_ALLOW_HIGHDPI, SDL_WINDOW_RESIZABLE )
   pWindow := SDL_CreateWindow( "Test sdl_waitEvent", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 450, nWindowFlags )
   IF( pWindow == NIL )
      OutStd( e"\nError SDL_CreateWindow", SDL_GetError() )
      RETURN
   ENDIF

   nRendererFlags := SDL_RendererFlags( SDL_RENDERER_ACCELERATED, SDL_RENDERER_PRESENTVSYNC )
   pRenderer := SDL_CreateRenderer( pWindow, -1, nRendererFlags )
   IF( pRenderer == NIL )
      OutStd( e"\nError SDL_CreateRenderer", SDL_GetError() )
      RETURN
   ENDIF

   DO WHILE( !lQuit )

      sdl_WaitEvent( @pEvent )

      SWITCH( sdl_EventType( pEvent ) )

         CASE SDL_QUIT
            OutStd( e"\nWindow closed" )
            lQuit := .T.
            EXIT

         CASE SDL_WINDOWEVENT

            IF sdl_EventWindowEvent( pEvent ) == SDL_WINDOWEVENT_CLOSE
               OutStd( e"\nWindow close requested" )
               lQuit := .T.
            ENDIF
            EXIT

         CASE SDL_KEYDOWN

            IF sdl_EventKeyKeysymSym( pEvent ) == SDLK_ESCAPE
               OutStd( e"\nEsc pressed" )
               lQuit := .T.
            ELSE
               OutStd( e"\nOther key pressed (key: ", sdl_EventKeyKeysymSym( pEvent ), ")" )
            ENDIF
            EXIT

         OTHERWISE
            OutStd( e"\nUnhandled pEvent (type:", sdl_EventType( pEvent ), ")" )

      ENDSWITCH

      SDL_SetRenderDrawColor( pRenderer, 12, 12, 12, 255 )
      SDL_RenderClear( pRenderer)
      SDL_RenderPresent( pRenderer )

   ENDDO

RETURN
