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
Garbage Collector SDL_Window
------------------------------------------------------------------------- */
static HB_GARBAGE_FUNC( hb_sdl_window_Destructor )
{
   SDL_Window **ppSDL_Window = ( SDL_Window ** ) Cargo;

   if( ppSDL_Window && *ppSDL_Window )
   {
      SDL_DestroyWindow( *ppSDL_Window );

      Uint32 subsystems = SDL_WasInit( 0 );
      Uint32 sdlFlags[] =
      {
         SDL_INIT_TIMER,
         SDL_INIT_AUDIO,
         SDL_INIT_VIDEO,
         SDL_INIT_JOYSTICK,
         SDL_INIT_HAPTIC,
         SDL_INIT_GAMECONTROLLER,
         SDL_INIT_EVENTS,
         SDL_INIT_SENSOR
      };

      for( size_t i = 0; i < sizeof( sdlFlags ) / sizeof( sdlFlags[ 0 ] ); i++ )
      {
         if( subsystems & sdlFlags[ i ] )
         {
            SDL_QuitSubSystem( sdlFlags[ i ] );
         }
      }

      SDL_Quit();

      *ppSDL_Window = NULL;
   }
}

static const HB_GC_FUNCS s_gc_sdl_window_Funcs =
{
   hb_sdl_window_Destructor,
   hb_gcDummyMark
};

SDL_Window *hb_sdl_window_Param( int iParam )
{
   SDL_Window **ppSDL_Window = ( SDL_Window ** ) hb_parptrGC( &s_gc_sdl_window_Funcs, iParam );

   if( ppSDL_Window && *ppSDL_Window )
   {
      return *ppSDL_Window;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

PHB_ITEM hb_sdl_window_ItemPut( PHB_ITEM pItem, SDL_Window *pSDL_Window )
{
   SDL_Window **ppSDL_Window = ( SDL_Window ** ) hb_gcAllocate( sizeof( SDL_Window * ), &s_gc_sdl_window_Funcs );

   *ppSDL_Window = pSDL_Window;
   return hb_itemPutPtrGC( pItem, ppSDL_Window );
}

void hb_sdl_window_Return( SDL_Window *pSDL_Window )
{
   if( pSDL_Window )
   {
      hb_sdl_window_ItemPut( hb_param( -1, HB_IT_ANY ), pSDL_Window );
   }
   else
   {
      hb_ret();
   }
}

/* -------------------------------------------------------------------------
Harbour Implementation
------------------------------------------------------------------------- */
// int SDL_WindowFlags( [ flags... ] )
HB_FUNC( SDL_WINDOWFLAGS )
{
   Uint32 flags = 0;
   int argc = hb_pcount();

   for( int i = 1; i <= argc; i++ )
   {
      if( hb_param( i, HB_IT_NUMERIC ) != NULL )
      {
         flags |= ( Uint32 ) hb_parni( i );
      }
      else
      {
         HB_ERR_ARGS();
      }
   }
   hb_retni( flags );
}

/* -------------------------------------------------------------------------
SDL API
------------------------------------------------------------------------- */
// int SDL_GetNumVideoDrivers(void);
// const char *SDL_GetVideoDriver(int index);
// int SDL_VideoInit(const char *driver_name);
// void SDL_VideoQuit(void);
// const char *SDL_GetCurrentVideoDriver(void);
// int SDL_GetNumVideoDisplays(void);
// const char * SDL_GetDisplayName(int displayIndex);
// int SDL_GetDisplayBounds(int displayIndex, SDL_Rect * rect);
// int SDL_GetDisplayUsableBounds(int displayIndex, SDL_Rect * rect);
// int SDL_GetDisplayDPI(int displayIndex, float * ddpi, float * hdpi, float * vdpi);
// SDL_DisplayOrientation SDL_GetDisplayOrientation(int displayIndex);
// int SDL_GetNumDisplayModes(int displayIndex);
// int SDL_GetDisplayMode(int displayIndex, int modeIndex, SDL_DisplayMode * mode);
// int SDL_GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode * mode);
// int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode);
// SDL_DisplayMode * SDL_GetClosestDisplayMode(int displayIndex, const SDL_DisplayMode * mode, SDL_DisplayMode * closest);
// int SDL_GetPointDisplayIndex(const SDL_Point * point);
// int SDL_GetRectDisplayIndex(const SDL_Rect * rect);
// int SDL_GetWindowDisplayIndex(SDL_Window * window);
// int SDL_SetWindowDisplayMode(SDL_Window * window, const SDL_DisplayMode * mode);
// int SDL_GetWindowDisplayMode(SDL_Window * window, SDL_DisplayMode * mode);
// void* SDL_GetWindowICCProfile(SDL_Window * window, size_t* size);
// Uint32 SDL_GetWindowPixelFormat(SDL_Window * window);

// SDL_Window *SDL_CreateWindow( const char *title, int x, int y, int w, int h, Uint32 flags );
HB_FUNC( SDL_CREATEWINDOW )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL &&
       hb_param( 2, HB_IT_NUMERIC ) != NULL &&
       hb_param( 3, HB_IT_NUMERIC ) != NULL &&
       hb_param( 4, HB_IT_NUMERIC ) != NULL &&
       hb_param( 5, HB_IT_NUMERIC ) != NULL &&
       hb_param( 6, HB_IT_NUMERIC ) != NULL )
   {
      hb_sdl_window_Return( SDL_CreateWindow( hb_parc( 1 ), hb_parni( 2 ), hb_parni( 3 ), hb_parni( 4 ), hb_parni( 5 ), ( Uint32 ) hb_parni( 6 ) ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// SDL_Window * SDL_CreateWindowFrom(const void *data);
// Uint32 SDL_GetWindowID(SDL_Window * window);
// SDL_Window * SDL_GetWindowFromID(Uint32 id);
// Uint32 SDL_GetWindowFlags(SDL_Window * window);
// void SDL_SetWindowTitle(SDL_Window * window, const char *title);
// const char *SDL_GetWindowTitle(SDL_Window * window);
// void SDL_SetWindowIcon(SDL_Window * window, SDL_Surface * icon);
// void* SDL_SetWindowData(SDL_Window * window, const char *name, void *userdata);
// void *SDL_GetWindowData(SDL_Window * window, const char *name);
// void SDL_SetWindowPosition(SDL_Window * window, int x, int y);
// void SDL_GetWindowPosition(SDL_Window * window, int *x, int *y);
// void SDL_SetWindowSize(SDL_Window * window, int w, int h);
// void SDL_GetWindowSize(SDL_Window * window, int *w, int *h);
// int SDL_GetWindowBordersSize(SDL_Window * window, int *top, int *left, int *bottom, int *right);
// void SDL_GetWindowSizeInPixels(SDL_Window * window, int *w, int *h);
// void SDL_SetWindowMinimumSize(SDL_Window * window, int min_w, int min_h);
// void SDL_GetWindowMinimumSize(SDL_Window * window, int *w, int *h);
// void SDL_SetWindowMaximumSize(SDL_Window * window, int max_w, int max_h);
// void SDL_GetWindowMaximumSize(SDL_Window * window, int *w, int *h);
// void SDL_SetWindowBordered(SDL_Window * window, SDL_bool bordered);
// void SDL_SetWindowResizable(SDL_Window * window, SDL_bool resizable);
// void SDL_SetWindowAlwaysOnTop(SDL_Window * window, SDL_bool on_top);
// void SDL_ShowWindow(SDL_Window * window);
// void SDL_HideWindow(SDL_Window * window);
// void SDL_RaiseWindow(SDL_Window * window);
// void SDL_MaximizeWindow(SDL_Window * window);
// void SDL_MinimizeWindow(SDL_Window * window);
// void SDL_RestoreWindow(SDL_Window * window);
// int SDL_SetWindowFullscreen(SDL_Window * window, Uint32 flags);
// SDL_bool SDL_HasWindowSurface(SDL_Window *window);
// SDL_Surface * SDL_GetWindowSurface(SDL_Window * window);
// int SDL_UpdateWindowSurface(SDL_Window * window);
// int SDL_UpdateWindowSurfaceRects(SDL_Window * window, const SDL_Rect * rects, int numrects);
// int SDL_DestroyWindowSurface(SDL_Window *window);
// void SDL_SetWindowGrab(SDL_Window * window, SDL_bool grabbed);
// void SDL_SetWindowKeyboardGrab(SDL_Window * window, SDL_bool grabbed);
// void SDL_SetWindowMouseGrab(SDL_Window * window, SDL_bool grabbed);
// SDL_bool SDL_GetWindowGrab(SDL_Window * window);
// SDL_bool SDL_GetWindowKeyboardGrab(SDL_Window * window);
// SDL_bool SDL_GetWindowMouseGrab(SDL_Window * window);
// SDL_Window * SDL_GetGrabbedWindow(void);
// int SDL_SetWindowMouseRect(SDL_Window * window, const SDL_Rect * rect);
// const SDL_Rect * SDL_GetWindowMouseRect(SDL_Window * window);
// int SDL_SetWindowBrightness(SDL_Window * window, float brightness);
// float SDL_GetWindowBrightness(SDL_Window * window);
// int SDL_SetWindowOpacity(SDL_Window * window, float opacity);
// int SDL_GetWindowOpacity(SDL_Window * window, float * out_opacity);
// int SDL_SetWindowModalFor(SDL_Window * modal_window, SDL_Window * parent_window);
// int SDL_SetWindowInputFocus(SDL_Window * window);
// int SDL_SetWindowGammaRamp(SDL_Window * window, const Uint16 * red, const Uint16 * green, const Uint16 * blue);
// int SDL_GetWindowGammaRamp(SDL_Window * window, Uint16 * red, Uint16 * green, Uint16 * blue);
// typedef SDL_HitTestResult (*SDL_HitTest)(SDL_Window *win, const SDL_Point *area, void *data);
// int SDL_SetWindowHitTest(SDL_Window * window, SDL_HitTest callback, void *callback_data);
// int SDL_FlashWindow(SDL_Window * window, SDL_FlashOperation operation);
// void SDL_DestroyWindow(SDL_Window * window);
// SDL_bool SDL_IsScreenSaverEnabled(void);
// void SDL_EnableScreenSaver(void);
// void SDL_DisableScreenSaver(void);
// int SDL_GL_LoadLibrary(const char *path);
// void *SDL_GL_GetProcAddress(const char *proc);
// void SDL_GL_UnloadLibrary(void);
// SDL_bool SDL_GL_ExtensionSupported(const char *extension);
// void SDL_GL_ResetAttributes(void);
// int SDL_GL_SetAttribute(SDL_GLattr attr, int value);
// int SDL_GL_GetAttribute(SDL_GLattr attr, int *value);
// SDL_GLContext SDL_GL_CreateContext(SDL_Window * window);
// int SDL_GL_MakeCurrent(SDL_Window * window, SDL_GLContext context);
// SDL_Window* SDL_GL_GetCurrentWindow(void);
// SDL_GLContext SDL_GL_GetCurrentContext(void);
// void SDL_GL_GetDrawableSize(SDL_Window * window, int *w, int *h);
// int SDL_GL_SetSwapInterval(int interval);
// int SDL_GL_GetSwapInterval(void);
// void SDL_GL_SwapWindow(SDL_Window * window);
// void SDL_GL_DeleteContext(SDL_GLContext context);
