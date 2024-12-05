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
   LOCAL event
   LOCAL sdl
   LOCAL text
   LOCAL numLines
   LOCAL i

   sdl := CreateWindow( 830, 450, "Test sdl_drawFont", "FFFFFF" )

   sdl_LoadFont( sdl, "../docs/assets/font/9x18.pcf.gz", 18 );

   text := {;
      "",;
      "Mathematics and sciences:",;
      "",;
      "  ∮ E⋅da = Q,  n → ∞, ∑ f(i) = ∏ g(i),      ⎧⎡⎛┌─────┐⎞⎤⎫",;
      "                                            ⎪⎢⎜│a²+b³ ⎟⎥⎪",;
      "  ∀x∈ℝ: ⌈x⌉ = −⌊−x⌋, α ∧ ¬β = ¬(¬α ∨ β),    ⎪⎢⎜│───── ⎟⎥⎪",;
      "                                            ⎪⎢⎜⎷ c₈   ⎟⎥⎪",;
      "  ℕ ⊆ ℕ₀ ⊂ ℤ ⊂ ℚ ⊂ ℝ ⊂ ℂ,                   ⎨⎢⎜       ⎟⎥⎬",;
      "                                            ⎪⎢⎜ ∞     ⎟⎥⎪",;
      "  ⊥ < a ≠ b ≡ c ≤ d ≪ ⊤ ⇒ (⟦A⟧ ⇔ ⟪B⟫),      ⎪⎢⎜ ⎲     ⎟⎥⎪",;
      "                                            ⎪⎢⎜ ⎳aⁱ-bⁱ⎟⎥⎪",;
      "  2H₂ + O₂ ⇌ 2H₂O, R = 4.7 kΩ, ⌀ 200 mm     ⎩⎣⎝i=1    ⎠⎦⎭",;
      "",;
      "Linguistics and dictionaries:",;
      "",;
      "  ði ıntəˈnæʃənəl fəˈnɛtık əsoʊsiˈeıʃn",;
      "  Y [ˈʏpsilɔn], Yen [jɛn], Yoga [ˈjoːgɑ]",;
      "",;
      "APL:",;
      "",;
      "  ((V⍳V)=⍳⍴V)/V←,V    ⌷←⍳→⍴∆∇⊃‾⍎⍕⌈" }

   numLines := Len( text )

   DO WHILE( !quit )

      sdl_WaitEvent( @event )

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

      sdl_EndDraw( sdl )

   ENDDO

RETURN
