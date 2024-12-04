/*
 * Harbour SDL2 (HBSDL) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
 *
 */

#include "hbsdl.ch"
#include "hbsdlbox.ch"

PROCEDURE Main()

   LOCAL quit := .F.
   LOCAL event
   LOCAL sdl
   LOCAL text
   LOCAL numLines
   LOCAL i

   sdl := CreateWindow( 830, 450, "Test sdl_DrawBox", "FFFFFF" )

   sdl_LoadFont( sdl, "../docs/assets/font/9x18.pcf.gz", 18 );

   text := {;
      "",;
      "                                                                    █",;
      "                                                                    ▉",;
      "╔══╦══╗  ┌──┬──┐  ╭──┬──╮  ╭──┬──╮  ┏━━┳━━┓  ┎┒┏┑   ╷  ╻ ┏┯┓ ┌┰┐    ▊ ╱╲╱╲╳╳╳",;
      "║┌─╨─┐║  │╔═╧═╗│  │╒═╪═╕│  │╓─╁─╖│  ┃┌─╂─┐┃  ┗╃╄┙  ╶┼╴╺╋╸┠┼┨ ┝╋┥    ▋ ╲╱╲╱╳╳╳",;
      "║│╲ ╱│║  │║   ║│  ││ │ ││  │║ ┃ ║│  ┃│ ╿ │┃  ┍╅╆┓   ╵  ╹ ┗┷┛ └┸┘    ▌ ╱╲╱╲╳╳╳",;
      "╠╡ ╳ ╞╣  ├╢   ╟┤  ├┼─┼─┼┤  ├╫─╂─╫┤  ┣┿╾┼╼┿┫  ┕┛┖┚     ┌┄┄┐ ╎ ┏┅┅┓ ┋ ▍ ╲╱╲╱╳╳╳",;
      "║│╱ ╲│║  │║   ║│  ││ │ ││  │║ ┃ ║│  ┃│ ╽ │┃  ░░▒▒▓▓██ ┊  ┆ ╎ ╏  ┇ ┋ ▎",;
      "║└─╥─┘║  │╚═╤═╝│  │╘═╪═╛│  │╙─╀─╜│  ┃└─╂─┘┃  ░░▒▒▓▓██ ┊  ┆ ╎ ╏  ┇ ┋ ▏",;
      "╚══╩══╝  └──┴──┘  ╰──┴──╯  ╰──┴──╯  ┗━━┻━━┛  ▗▄▖▛▀▜   └╌╌┘ ╎ ┗╍╍┛ ┋  ▁▂▃▄▅▆▇█",;
      "                                             ▝▀▘▙▄▟" }

   numLines := Len( text )

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

         FOR i := 1 TO numLines
            sdl_DrawFont( sdl, 1, i -1, text[ i ], "" )
         NEXT

         sdl_DrawBox( sdl, 0, 11, 77, 5, BOX_SINGLE, "FFFFFF/000000" )
         sdl_DrawBox( sdl, 0, 16, 77, 5, BOX_DOUBLE, "FFFFFF/000000" )
         sdl_DrawBox( sdl, 0, 21, 77, 5, BOX_SINGLE_DOUBLE, "FFFFFF/000000" )
         sdl_DrawBox( sdl, 0, 26, 77, 5, BOX_DOUBLE_SINGLE, "FFFFFF/000000" )

      sdl_EndDraw( sdl )

   ENDDO

RETURN
