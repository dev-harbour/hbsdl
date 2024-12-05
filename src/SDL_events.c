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

/* -------------------------------------------------------------------------
Garbage Collector SDL_Event
------------------------------------------------------------------------- */
static HB_GARBAGE_FUNC( hb_sdl_event_Destructor )
{
   SDL_Event **ppEvent = ( SDL_Event ** ) Cargo;

   if( ppEvent && *ppEvent )
   {
      hb_xfree( *ppEvent );
      *ppEvent = NULL;
   }
}

static const HB_GC_FUNCS s_gc_sdl_event_Funcs =
{
   hb_sdl_event_Destructor,
   hb_gcDummyMark
};

SDL_Event *hb_sdl_event_Param( int iParam )
{
   SDL_Event **ppSDL_Event = ( SDL_Event ** ) hb_parptrGC( &s_gc_sdl_event_Funcs, iParam );

   if( ppSDL_Event && *ppSDL_Event )
      return *ppSDL_Event;

   HB_ERR_ARGS();
   return NULL;
}

SDL_Event *hb_sdl_event_ParamGet( int iParam )
{
   SDL_Event **ppSDL_Event = ( SDL_Event ** ) hb_parptrGC( &s_gc_sdl_event_Funcs, iParam );

   return ppSDL_Event ? *ppSDL_Event : NULL;
}

SDL_Event *hb_sdl_event_ItemGet( PHB_ITEM pItem )
{
   SDL_Event **ppSDL_Event = ( SDL_Event ** ) hb_itemGetPtrGC( pItem, &s_gc_sdl_event_Funcs );

   return ppSDL_Event ? *ppSDL_Event : NULL;
}

PHB_ITEM hb_sdl_event_ItemPut( PHB_ITEM pItem, SDL_Event *pSDL_Event )
{
   SDL_Event **ppSDL_Event = ( SDL_Event ** ) hb_gcAllocate( sizeof( SDL_Event * ), &s_gc_sdl_event_Funcs );

   *ppSDL_Event = pSDL_Event;
   return hb_itemPutPtrGC( pItem, ppSDL_Event );
}

void hb_sdl_event_ItemClear( PHB_ITEM pItem )
{
   SDL_Event **ppSDL_Event = ( SDL_Event ** ) hb_itemGetPtrGC( pItem, &s_gc_sdl_event_Funcs );

   if( ppSDL_Event )
      *ppSDL_Event = NULL;
}

void hb_sdl_event_StorPtr( SDL_Event *pSDL_Event, int iParam )
{
   SDL_Event **ppSDL_Event = ( SDL_Event ** ) hb_gcAllocate( sizeof( SDL_Event * ), &s_gc_sdl_event_Funcs );

   *ppSDL_Event = pSDL_Event;
   hb_storptrGC( ppSDL_Event, iParam );
}

void hb_sdl_event_Return( SDL_Event *pSDL_Event )
{
   if( pSDL_Event )
      hb_sdl_event_ItemPut( hb_param( -1, HB_IT_ANY ), pSDL_Event );
   else
      hb_ret();
}

/* -------------------------------------------------------------------------
Harbour Implementation
------------------------------------------------------------------------- */
// int sdl_EventType( SDL_Event *pEvent )
HB_FUNC( SDL_EVENTTYPE )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL_Event *pEvent = hb_sdl_event_Param( 1 );

      hb_retni( pEvent->type );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int sdl_EventWindowEvent( SDL_Event *pEvent )
HB_FUNC( SDL_EVENTWINDOWEVENT )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL_Event *pEvent = hb_sdl_event_Param( 1 );

      hb_retni( pEvent->window.event );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int sdl_EventKeyKeysymSym( SDL_Event *pEvent )
HB_FUNC( SDL_EVENTKEYKEYSYMSYM )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL_Event *pEvent = hb_sdl_event_Param( 1 );

      hb_retni( pEvent->key.keysym.sym );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* -------------------------------------------------------------------------
SDL API
------------------------------------------------------------------------- */
// void SDL_PumpEvents(void);
// int SDL_PeepEvents(SDL_Event * events, int numevents, SDL_eventaction action, Uint32 minType, Uint32 maxType);
// SDL_bool SDL_HasEvent(Uint32 type);
// SDL_bool SDL_HasEvents(Uint32 minType, Uint32 maxType);
// void SDL_FlushEvent(Uint32 type);
// void SDL_FlushEvents(Uint32 minType, Uint32 maxType);

// int SDL_PollEvent( SDL_Event *event );
HB_FUNC( SDL_POLLEVENT )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL )
   {
      SDL_Event *pEvent = ( SDL_Event * ) hb_xgrab( sizeof( SDL_Event ) );

      if( SDL_PollEvent( pEvent ) )
      {
         hb_retl( T );
         hb_sdl_event_StorPtr( pEvent, 1 );
      }
      else
      {
         hb_xfree( pEvent );
         hb_retl( F );
      }
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int SDL_WaitEvent( SDL_Event *event );
HB_FUNC( SDL_WAITEVENT )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL )
   {
      SDL_Event *pEvent = ( SDL_Event * ) hb_xgrab( sizeof( SDL_Event ) );

      if( SDL_WaitEvent( pEvent ) )
      {
         hb_retl( T );
         hb_sdl_event_StorPtr( pEvent, 1 );
      }
      else
      {
         hb_xfree( pEvent );
         hb_retl( F );
      }
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int SDL_WaitEventTimeout( SDL_Event *event, int timeout );
HB_FUNC( SDL_WAITEVENTTIMEOUT )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      SDL_Event *pEvent = ( SDL_Event * ) hb_xgrab( sizeof( SDL_Event ) );

      if( SDL_WaitEventTimeout( pEvent, hb_parni( 2 ) ) )
      {
         hb_retl( T );
         hb_sdl_event_StorPtr( pEvent, 1 );
      }
      else
      {
         hb_xfree( pEvent );
         hb_retl( F );
      }
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int SDL_PushEvent(SDL_Event * event);
// void SDL_SetEventFilter(SDL_EventFilter filter, void *userdata);
// SDL_bool SDL_GetEventFilter(SDL_EventFilter * filter, void **userdata);
// void SDL_AddEventWatch(SDL_EventFilter filter, void *userdata);
// void SDL_DelEventWatch(SDL_EventFilter filter, void *userdata);
// void SDL_FilterEvents(SDL_EventFilter filter, void *userdata);
// Uint8 SDL_EventState(Uint32 type, int state);
// Uint32 SDL_RegisterEvents(int numevents);



