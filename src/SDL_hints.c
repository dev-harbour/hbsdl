/*
 * Harbour SDL2 (HBSDL) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
 *
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

#include "hbsdl.h"

// SDL_bool SDL_SetHintWithPriority( const char *name, const char *value, SDL_HintPriority priority );

// SDL_bool SDL_SetHint( const char *name, const char *value );
HB_FUNC( SDL_SETHINT )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      hb_retl( SDL_SetHint( hb_parc( 1 ), hb_parc( 2 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// SDL_bool SDL_ResetHint(const char *name);
// void SDL_ResetHints(void);
// const char * SDL_GetHint(const char *name);
// SDL_bool SDL_GetHintBoolean(const char *name, SDL_bool default_value);
// typedef void (*SDL_HintCallback)(void *userdata, const char *name, const char *oldValue, const char *newValue);
// void SDL_AddHintCallback(const char *name, SDL_HintCallback callback, void *userdata);
// void SDL_DelHintCallback(const char *name, SDL_HintCallback callback, void *userdata);
// void SDL_ClearHints(void);
