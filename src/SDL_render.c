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
Garbage Collector SDL_Renderer
------------------------------------------------------------------------- */
static HB_GARBAGE_FUNC( hb_sdl_renderer_Destructor )
{
   SDL_Renderer **ppSDL_Renderer = ( SDL_Renderer ** ) Cargo;

   if( ppSDL_Renderer && *ppSDL_Renderer )
   {
      SDL_DestroyRenderer( *ppSDL_Renderer );

      *ppSDL_Renderer = NULL;
   }
}

static const HB_GC_FUNCS s_gc_sdl_renderer_Funcs =
{
   hb_sdl_renderer_Destructor,
   hb_gcDummyMark
};

SDL_Renderer *hb_sdl_renderer_Param( int iParam )
{
   SDL_Renderer **ppSDL_Renderer = ( SDL_Renderer ** ) hb_parptrGC( &s_gc_sdl_renderer_Funcs, iParam );

   if( ppSDL_Renderer && *ppSDL_Renderer )
   {
      return *ppSDL_Renderer;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

PHB_ITEM hb_sdl_renderer_ItemPut( PHB_ITEM pItem, SDL_Renderer *pSDL_Renderer )
{
   SDL_Renderer **ppSDL_Renderer = ( SDL_Renderer ** ) hb_gcAllocate( sizeof( SDL_Renderer * ), &s_gc_sdl_renderer_Funcs );

   *ppSDL_Renderer = pSDL_Renderer;
   return hb_itemPutPtrGC( pItem, ppSDL_Renderer );
}

void hb_sdl_renderer_Return( SDL_Renderer *pSDL_Renderer )
{
   if( pSDL_Renderer )
   {
      hb_sdl_renderer_ItemPut( hb_param( -1, HB_IT_ANY ), pSDL_Renderer );
   }
   else
   {
      hb_ret();
   }
}

/* -------------------------------------------------------------------------
SDL API
------------------------------------------------------------------------- */

// int SDL_GetNumRenderDrivers(void);
// int SDL_GetRenderDriverInfo(int index, SDL_RendererInfo * info);
// int SDL_CreateWindowAndRenderer(int width, int height, Uint32 window_flags, SDL_Window **window, SDL_Renderer **renderer);

// SDL_Renderer * SDL_CreateRenderer(SDL_Window * window, int index, Uint32 flags);
HB_FUNC( SDL_CREATERENDERER )
{
    if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL && hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
      SDL_Window *pWindow = hb_sdl_window_Param( 1 );
      int index = hb_parni( 2 );
      Uint32 flags = hb_parni( 3 );

      hb_sdl_renderer_Return( SDL_CreateRenderer( pWindow, index, flags ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// SDL_Renderer * SDL_CreateSoftwareRenderer(SDL_Surface * surface);
// SDL_Renderer * SDL_GetRenderer(SDL_Window * window);
// SDL_Window * SDL_RenderGetWindow(SDL_Renderer *renderer);
// int SDL_GetRendererInfo(SDL_Renderer * renderer, SDL_RendererInfo * info);
// int SDL_GetRendererOutputSize(SDL_Renderer * renderer, int *w, int *h);
// SDL_Texture * SDL_CreateTexture(SDL_Renderer * renderer, Uint32 format, int access, int w, int h);
// SDL_Texture * SDL_CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface);
// int SDL_QueryTexture(SDL_Texture * texture, Uint32 * format, int *access, int *w, int *h);
// int SDL_SetTextureColorMod(SDL_Texture * texture, Uint8 r, Uint8 g, Uint8 b);
// int SDL_GetTextureColorMod(SDL_Texture * texture, Uint8 * r, Uint8 * g, Uint8 * b);
// int SDL_SetTextureAlphaMod(SDL_Texture * texture, Uint8 alpha);
// int SDL_GetTextureAlphaMod(SDL_Texture * texture, Uint8 * alpha);
// int SDL_SetTextureBlendMode(SDL_Texture * texture, SDL_BlendMode blendMode);
// int SDL_GetTextureBlendMode(SDL_Texture * texture, SDL_BlendMode *blendMode);
// int SDL_SetTextureScaleMode(SDL_Texture * texture, SDL_ScaleMode scaleMode);
// int SDL_GetTextureScaleMode(SDL_Texture * texture, SDL_ScaleMode *scaleMode);
// int SDL_SetTextureUserData(SDL_Texture * texture, void *userdata);
// void * SDL_GetTextureUserData(SDL_Texture * texture);
// int SDL_UpdateTexture(SDL_Texture * texture, const SDL_Rect * rect, const void *pixels, int pitch);
// int SDL_UpdateYUVTexture(SDL_Texture * texture, const SDL_Rect * rect, const Uint8 *Yplane, int Ypitch, const Uint8 *Uplane, int Upitch, const Uint8 *Vplane, int Vpitch);
// int SDL_UpdateNVTexture(SDL_Texture * texture, const SDL_Rect * rect, const Uint8 *Yplane, int Ypitch, const Uint8 *UVplane, int UVpitch);
// int SDL_LockTexture(SDL_Texture * texture, const SDL_Rect * rect, void **pixels, int *pitch);
// int SDL_LockTextureToSurface(SDL_Texture *texture, const SDL_Rect *rect, SDL_Surface **surface);
// void SDL_UnlockTexture(SDL_Texture * texture);
// SDL_bool SDL_RenderTargetSupported(SDL_Renderer *renderer);
// int SDL_SetRenderTarget(SDL_Renderer *renderer, SDL_Texture *texture);
// SDL_Texture * SDL_GetRenderTarget(SDL_Renderer *renderer);
// int SDL_RenderSetLogicalSize(SDL_Renderer * renderer, int w, int h);
// void SDL_RenderGetLogicalSize(SDL_Renderer * renderer, int *w, int *h);
// int SDL_RenderSetIntegerScale(SDL_Renderer * renderer, SDL_bool enable);
// SDL_bool SDL_RenderGetIntegerScale(SDL_Renderer * renderer);
// int SDL_RenderSetViewport(SDL_Renderer * renderer, const SDL_Rect * rect);
// void SDL_RenderGetViewport(SDL_Renderer * renderer, SDL_Rect * rect);
// int SDL_RenderSetClipRect(SDL_Renderer * renderer, const SDL_Rect * rect);
// void SDL_RenderGetClipRect(SDL_Renderer * renderer, SDL_Rect * rect);
// SDL_bool SDL_RenderIsClipEnabled(SDL_Renderer * renderer);
// int SDL_RenderSetScale(SDL_Renderer * renderer, float scaleX, float scaleY);
// void SDL_RenderGetScale(SDL_Renderer * renderer, float *scaleX, float *scaleY);
// void SDL_RenderWindowToLogical(SDL_Renderer * renderer, int windowX, int windowY, float *logicalX, float *logicalY);
// void SDL_RenderLogicalToWindow(SDL_Renderer * renderer, float logicalX, float logicalY, int *windowX, int *windowY);

// int SDL_SetRenderDrawColor(SDL_Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
HB_FUNC( SDL_SETRENDERDRAWCOLOR )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL && hb_param( 3, HB_IT_NUMERIC ) != NULL && hb_param( 4, HB_IT_NUMERIC ) != NULL && hb_param( 5, HB_IT_NUMERIC ) != NULL )
   {
      SDL_Renderer *pRenderer = hb_sdl_renderer_Param( 1 );
      Uint8 r = ( Uint8 ) hb_parni( 2 );
      Uint8 g = ( Uint8 ) hb_parni( 3 );
      Uint8 b = ( Uint8 ) hb_parni( 4 );
      Uint8 a = ( Uint8 ) hb_parni( 5 );

      hb_retni( SDL_SetRenderDrawColor( pRenderer, r, g, b, a ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int SDL_GetRenderDrawColor(SDL_Renderer * renderer, Uint8 * r, Uint8 * g, Uint8 * b, Uint8 * a);
// int SDL_SetRenderDrawBlendMode(SDL_Renderer * renderer, SDL_BlendMode blendMode);
// int SDL_GetRenderDrawBlendMode(SDL_Renderer * renderer, SDL_BlendMode *blendMode);

// int SDL_RenderClear( SDL_Renderer * renderer );
HB_FUNC( SDL_RENDERCLEAR )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL_Renderer *pRenderer = hb_sdl_renderer_Param( 1 );

      hb_retni( SDL_RenderClear( pRenderer ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}


// int SDL_RenderDrawPoint(SDL_Renderer * renderer, int x, int y);
// int SDL_RenderDrawPoints(SDL_Renderer * renderer, const SDL_Point * points, int count);
// int SDL_RenderDrawLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2);
// int SDL_RenderDrawLines(SDL_Renderer * renderer, const SDL_Point * points, int count);
// int SDL_RenderDrawRect(SDL_Renderer * renderer, const SDL_Rect * rect);
// int SDL_RenderDrawRects(SDL_Renderer * renderer, const SDL_Rect * rects, int count);
// int SDL_RenderFillRect(SDL_Renderer * renderer, const SDL_Rect * rect);
// int SDL_RenderFillRects(SDL_Renderer * renderer, const SDL_Rect * rects, int count);
// int SDL_RenderCopy(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * srcrect, const SDL_Rect * dstrect);
// int SDL_RenderCopyEx(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * srcrect, const SDL_Rect * dstrect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip);
// int SDL_RenderDrawPointF(SDL_Renderer * renderer, float x, float y);
// int SDL_RenderDrawPointsF(SDL_Renderer * renderer, const SDL_FPoint * points, int count);
// int SDL_RenderDrawLineF(SDL_Renderer * renderer, float x1, float y1, float x2, float y2);
// int SDL_RenderDrawLinesF(SDL_Renderer * renderer, const SDL_FPoint * points, int count);
// int SDL_RenderDrawRectF(SDL_Renderer * renderer, const SDL_FRect * rect);
// int SDL_RenderDrawRectsF(SDL_Renderer * renderer, const SDL_FRect * rects, int count);
// int SDL_RenderFillRectF(SDL_Renderer * renderer, const SDL_FRect * rect);
// int SDL_RenderFillRectsF(SDL_Renderer * renderer, const SDL_FRect * rects, int count);
// int SDL_RenderCopyF(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * srcrect, const SDL_FRect * dstrect);
// int SDL_RenderCopyExF(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * srcrect, const SDL_FRect * dstrect, const double angle, const SDL_FPoint *center, const SDL_RendererFlip flip);
// int SDL_RenderGeometry(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Vertex *vertices, int num_vertices, const int *indices, int num_indices);
// int SDL_RenderGeometryRaw(SDL_Renderer *renderer, SDL_Texture *texture, const float *xy, int xy_stride, const SDL_Color *color, int color_stride, const float *uv, int uv_stride, int num_vertices, const void *indices, int num_indices, int size_indices);
// int SDL_RenderReadPixels(SDL_Renderer * renderer, const SDL_Rect * rect, Uint32 format, void *pixels, int pitch);

// void SDL_RenderPresent( SDL_Renderer * renderer );
HB_FUNC( SDL_RENDERPRESENT )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL_Renderer *pRenderer = hb_sdl_renderer_Param( 1 );

      SDL_RenderPresent( pRenderer );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void SDL_DestroyTexture(SDL_Texture * texture);
// void SDL_DestroyRenderer(SDL_Renderer * renderer);
// int SDL_RenderFlush(SDL_Renderer * renderer);
// int SDL_GL_BindTexture(SDL_Texture *texture, float *texw, float *texh);
// int SDL_GL_UnbindTexture(SDL_Texture *texture);
// void *SDL_RenderGetMetalLayer(SDL_Renderer * renderer);
// void *SDL_RenderGetMetalCommandEncoder(SDL_Renderer * renderer);
// int SDL_RenderSetVSync(SDL_Renderer* renderer, int vsync);
