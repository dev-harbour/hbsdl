/*
 * Harbour SDL2 (HBSDL) Project
 * Copyright 2014 - 2024 Rafał Jopek
 * Website: https://harbour.pl
 *
 */

#include "hbsdl.h"

/* -------------------------------------------------------------------------
Garbage Collector SDL
------------------------------------------------------------------------- */
static HB_GARBAGE_FUNC( hb_hbsdl_Destructor )
{
   SDL **ppSDL = ( SDL ** ) Cargo;

   if( ppSDL && *ppSDL )
   {
      if( ( *ppSDL )->font )
      {
         TTF_CloseFont( ( *ppSDL )->font );
      }
      if( ( *ppSDL )->renderer )
      {
         SDL_DestroyRenderer( ( *ppSDL )->renderer );
      }
      if( ( *ppSDL )->window )
      {
         SDL_DestroyWindow( ( *ppSDL )->window );
      }

      TTF_Quit();
      SDL_Quit();

      hb_xfree( *ppSDL );
      *ppSDL = NULL;
   }
}

static const HB_GC_FUNCS s_gc_hb_sdl_Funcs =
{
   hb_hbsdl_Destructor,
   hb_gcDummyMark
};

SDL *hb_sdl_Param( int iParam )
{
   SDL **ppSDL = ( SDL ** ) hb_parptrGC( &s_gc_hb_sdl_Funcs, iParam );

   if( ppSDL && *ppSDL )
      return *ppSDL;

   HB_ERR_ARGS();
   return NULL;
}

PHB_ITEM hb_sdl_ItemPut( PHB_ITEM pItem, SDL *pSDL )
{
   SDL **ppSDL = ( SDL ** ) hb_gcAllocate( sizeof( SDL * ), &s_gc_hb_sdl_Funcs );
   *ppSDL = pSDL;
   return hb_itemPutPtrGC( pItem, ppSDL );
}

static void hb_sdl_Return( SDL *pSDL )
{
   if( pSDL )
      hb_sdl_ItemPut( hb_param( -1, HB_IT_ANY ), pSDL );
   else
      hb_ret();
}

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

PHB_ITEM hb_sdl_event_ItemPut( PHB_ITEM pItem, SDL_Event *pSDL_Event )
{
   SDL_Event **ppSDL_Event = ( SDL_Event ** ) hb_gcAllocate( sizeof( SDL_Event * ), &s_gc_sdl_event_Funcs );
   *ppSDL_Event = pSDL_Event;
   return hb_itemPutPtrGC( pItem, ppSDL_Event );
}

static void hb_sdl_event_Return( SDL_Event *pSDL_Event )
{
   if( pSDL_Event )
      hb_sdl_event_ItemPut( hb_param( -1, HB_IT_ANY ), pSDL_Event );
   else
      hb_ret();
}

/* ------------------------------------------------------------------------- */
static void sdl_cleanup( SDL *pSDL )
{
   if( pSDL )
   {
      if( pSDL->font )
      {
         TTF_CloseFont( pSDL->font );
         pSDL->font = NULL;
      }
      if( pSDL->renderer )
      {
         SDL_DestroyRenderer( pSDL->renderer );
         pSDL->renderer = NULL;
      }
      if( pSDL->window )
      {
         SDL_DestroyWindow( pSDL->window );
         pSDL->window = NULL;
      }

      TTF_Quit();
      SDL_Quit();

      hb_xfree( pSDL );
   }
}

static SDL_Color sdl_hex_to_color( const char *hexColor )
{
   SDL_Color color = { 0, 0, 0, 255 };
   int r, g, b, a = 255;

   if( strlen( hexColor ) == 6 ) // Format: RRGGBB
   {
      sscanf( hexColor, "%02x%02x%02x", &r, &g, &b );
      color.r = r;
      color.g = g;
      color.b = b;
      color.a = 255;
   }
   else if( strlen( hexColor ) == 8 ) // Format: RRGGBBAA
   {
      sscanf( hexColor, "%02x%02x%02x%02x", &r, &g, &b, &a );
      color.r = r;
      color.g = g;
      color.b = b;
      color.a = a;
   }
   else
   {
      fprintf( stderr, "Invalid hex color format: sdl_hex_to_color() - defaulting to gray.\n" );
      color.r = 128;
      color.g = 128;
      color.b = 128;
      color.a = 255;
   }

   return color;
}

static size_t sdl_utf8Len( const char *utf8String )
{
   size_t len = 0;
   while( *utf8String )
   {
      unsigned char byte = *utf8String;

      if( ( byte & 0x80 ) == 0 )         // ASCII (0xxxxxxx)
         utf8String += 1;
      else if( ( byte & 0xE0 ) == 0xC0 ) // (110xxxxx)
         utf8String += 2;
      else if( ( byte & 0xF0 ) == 0xE0 ) // (1110xxxx)
         utf8String += 3;
      else if( ( byte & 0xF8 ) == 0xF0 ) // (11110xxx)
         utf8String += 4;
      else
         utf8String += 1;

      len++;
   }

   return len;
}

/* ------------------------------------------------------------------------- */
// SDL *sdl_CreateWindow( int width, int height, const char *title, const char *hexColor )
HB_FUNC( SDL_CREATEWINDOW )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL &&  hb_param( 3, HB_IT_STRING ) != NULL &&  hb_param( 4, HB_IT_STRING ) != NULL )
   {
      int width = hb_parni( 1 );
      int height = hb_parni( 2 );
      const char *title = hb_parc( 3 );
      const char *hexColor = hb_parc( 4 );

      SDL *pSDL = hb_xgrab( sizeof( SDL ) );
      if( !pSDL )
      {
         fprintf( stderr, "Memory allocation failed for SDL structure.\n" );
      }

      memset( pSDL, 0, sizeof( SDL ) );
      pSDL->width  = width;
      pSDL->height = height;

      pSDL->background = hexColor;

      if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
      {
         fprintf( stderr, "Unable to initialize SDL: %s\n", SDL_GetError() );
         sdl_cleanup( pSDL );
      }

      if( TTF_Init() == - 1 )
      {
         fprintf( stderr, "Unable to initialize SDL_ttf: %s\n", TTF_GetError() );
         sdl_cleanup( pSDL );
      }

      pSDL->window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
      if( !pSDL->window )
      {
         fprintf( stderr, "Could not create window: %s\n", SDL_GetError() );
         sdl_cleanup( pSDL );
      }

      pSDL->renderer = SDL_CreateRenderer( pSDL->window, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if( !pSDL->renderer )
      {
         fprintf( stderr, "Could not create renderer: %s\n", SDL_GetError() );
         sdl_cleanup( pSDL );
      }

      SDL_SetWindowMinimumSize( pSDL->window, width, height );

      hb_sdl_Return( pSDL );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sdl_BeginDraw( SDL *pSDL )
HB_FUNC( SDL_BEGINDRAW )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL *pSDL = hb_sdl_Param( 1 );

      int newWidth, newHeight;
      int newWidthPos, newHeightPos;
      int newMouseX, newMouseY;

      SDL_GetWindowSize( pSDL->window, &newWidth, &newHeight );
      pSDL->width = newWidth;
      pSDL->height = newHeight;

      SDL_GetWindowPosition( pSDL->window, &newWidthPos, &newHeightPos );
      pSDL->widthPos = newWidthPos;
      pSDL->heightPos = newHeightPos;

      SDL_GetMouseState( &newMouseX, &newMouseY );
      pSDL->mouseX = newMouseX;
      pSDL->mouseY = newMouseY;

      SDL_Color bgColor = { 50, 50, 50, 255 };
      if( pSDL->background && strlen( pSDL->background ) > 0 )
      {
         bgColor = sdl_hex_to_color( pSDL->background );
      }

      SDL_SetRenderDrawColor( pSDL->renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a );
      SDL_RenderClear( pSDL->renderer );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

//void sdl_EndDraw( SDL *pSDL )
HB_FUNC( SDL_ENDDRAW )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL *pSDL = hb_sdl_Param( 1 );

      SDL_RenderPresent( pSDL->renderer );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* ------------------------------------------------------------------------- */
// SDL_Event *sdl_WaitEvent( void )
HB_FUNC( SDL_WAITEVENT )
{
   SDL_Event *pEvent = hb_xgrab( sizeof( SDL_Event ) );

   if( pEvent == NULL )
   {
      fprintf( stderr, "Memory allocation failed for SDL_Event.\n" );
      hb_ret();
      return;
   }

   if( SDL_WaitEvent( pEvent ) )
   {
      hb_sdl_event_Return( pEvent );
   }
   else
   {
      hb_xfree( pEvent );
      hb_ret();
   }
}

// SDL_Event *sdl_PollEvent( void )
HB_FUNC( SDL_POLLEVENT )
{
   SDL_Event *pEvent = hb_xgrab( sizeof( SDL_Event ) );

   if( pEvent == NULL )
   {
      fprintf( stderr, "Memory allocation failed for SDL_Event.\n" );
      hb_ret();
      return;
   }

   if( SDL_PollEvent( pEvent ) )
   {
      hb_sdl_event_Return( pEvent );
   }
   else
   {
      hb_xfree( pEvent );
      hb_ret();
   }
}

// SDL_Event *sdl_WaitEventTimeout( int timeout );
HB_FUNC( SDL_WAITEVENTTIMEOUT )
{
   SDL_Event *pEvent = hb_xgrab( sizeof( SDL_Event ) );

   if( pEvent == NULL )
   {
      fprintf( stderr, "Memory allocation failed for SDL_Event.\n" );
      hb_ret();
      return;
   }

   int timeout = hb_parni( 1 );
   if( SDL_WaitEventTimeout( pEvent, timeout ) )
   {
      hb_sdl_event_Return( pEvent );
   }
   else
   {
      hb_xfree( pEvent );
      hb_ret();
   }
}

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

/* ------------------------------------------------------------------------- */
// bool sdl_LoadFont( SDL *pSdl, const char *fontPath, int fontSize )
HB_FUNC( SDL_LOADFONT )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_STRING ) != NULL && hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );
      const char *fontPath = hb_parc( 2 );
      int fontSize = hb_parni( 3 );

      pSdl->font = TTF_OpenFont( fontPath, fontSize );
      if( !pSdl->font )
      {
         fprintf( stderr, "Failed to load font: %s\n", TTF_GetError() );
         hb_retl( F );
      }

      int advance;
      TTF_GlyphMetrics( pSdl->font, 'M', NULL, NULL, NULL, NULL, &advance );

      pSdl->fontCellWidth  = advance;
      pSdl->fontCellHeight = TTF_FontHeight( pSdl->font );
      pSdl->fontSize       = fontSize;

      hb_retl( T );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

//void sdl_DrawFont( SDL *pSdl, int x, int y, const char *string, const char *hexColor )
HB_FUNC( SDL_DRAWFONT )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL && hb_param( 3, HB_IT_NUMERIC ) != NULL && hb_param( 4, HB_IT_STRING ) != NULL &&  hb_param( 5, HB_IT_STRING ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );

      if( !pSdl->font )
      {
         fprintf( stderr, "Failed to load font: %s\n", TTF_GetError() );
         return;
      }

      int x = hb_parni( 2 );
      int y = hb_parni( 3 );
      const char *string = hb_parc( 4 );
      const char *hexColor = hb_parc( 5 );

      x = x * pSdl->fontCellWidth;
      y = y * pSdl->fontCellHeight;

      SDL_Color bgColor = { 255, 255, 255, 255 };
      SDL_Color fgColor = { 0, 0, 0, 255 };

      if( hexColor && strlen( hexColor ) > 0 )
      {
         const char *separator = strchr( hexColor, '/' );
         if( separator && ( separator - hexColor == 6 ) && strlen( separator + 1 ) == 6 )
         {
            char bgColorStr[ 7 ];
            strncpy( bgColorStr, hexColor, 6 );
            bgColorStr[ 6 ] = '\0';

            bgColor = sdl_hex_to_color( bgColorStr );
            fgColor = sdl_hex_to_color( separator + 1 );
         }
      }

      size_t len = sdl_utf8Len( string );
      if( len == 0 )
      {
         SDL_Rect rect = { x, y, pSdl->fontCellWidth, pSdl->fontCellHeight };
         SDL_SetRenderDrawColor( pSdl->renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a );
         SDL_RenderFillRect( pSdl->renderer, &rect );
         return;
      }

      SDL_Rect rect = { x, y, pSdl->fontCellWidth * len, pSdl->fontCellHeight };
      SDL_SetRenderDrawColor( pSdl->renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a );
      SDL_RenderFillRect( pSdl->renderer, &rect );

      SDL_Surface *textSurface = TTF_RenderUTF8_Shaded( pSdl->font, string, fgColor, bgColor );
      SDL_Texture *textTexture = NULL;

      if( textSurface )
      {
         textTexture = SDL_CreateTextureFromSurface( pSdl->renderer, textSurface );
         SDL_FreeSurface( textSurface );
      }
      else
      {
         fprintf( stderr, "Error: rendering string: %s\n", TTF_GetError() );
      }

      if( textTexture )
      {
         SDL_Rect textRect = { x, y, 0, 0 };
         SDL_QueryTexture( textTexture, NULL, NULL, &textRect.w, &textRect.h );
         SDL_RenderCopy( pSdl->renderer, textTexture, NULL, &textRect );

         SDL_DestroyTexture( textTexture );
      }
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sdl_PrintFontInfo( const SDL *pSdl )
HB_FUNC( SDL_PRINTFONTINFO )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );

      if( pSdl->font )
      {
         printf( "\033[2J" );
         printf( "\033[H" );

         int minx, maxx, miny, maxy, advance;
         TTF_GlyphMetrics( pSdl->font, 'M', &minx, &maxx, &miny, &maxy, &advance );

         int height   = TTF_FontHeight( pSdl->font );
         int ascent   = TTF_FontAscent( pSdl->font );
         int descent  = TTF_FontDescent( pSdl->font );
         int lineSkip = TTF_FontLineSkip( pSdl->font );

         printf( "Font Info\n" );
         printf( "[\n" );
         printf( "   TTF_Font        : %p\n", pSdl->font );
         printf( "   Font minx       : %d\n", minx );
         printf( "   Font maxx       : %d\n", maxx );
         printf( "   Font miny       : %d\n", miny );
         printf( "   Font maxy       : %d\n", maxy );
         printf( "   Font advance    : %d\n", advance );
         printf( "   Font height     : %d\n", height );
         printf( "   Font ascent     : %d\n", ascent );
         printf( "   Font descent    : %d\n", descent );
         printf( "   Font lineSkip   : %d\n", lineSkip );
         printf( "   Font cell width : %d\n", pSdl->fontCellWidth );
         printf( "   Font cell height: %d\n", pSdl->fontCellHeight );
         printf( "   Font size       : %d\n", pSdl->fontSize );
         printf( "]\n" );

         fflush( stdout );
      }
      else
      {
         printf( "Font structure or TTF_Font is NULL\n" );
         hb_ret();
      }
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* -------------------------------------------------------------------------
CategoryKeyboard
------------------------------------------------------------------------- */
// SDL_Keymod sdl_GetModState( void );
HB_FUNC( SDL_GETMODSTATE )
{
   hb_retni( SDL_GetModState() );
}

// void sdl_StartTextInput( void );
HB_FUNC( SDL_STARTTEXTINPUT )
{
   SDL_StartTextInput();
}

// void sdl_StopTextInput( void );
HB_FUNC( SDL_STOPTEXTINPUT )
{
   SDL_StopTextInput();
}

/* -------------------------------------------------------------------------
CategoryVideo
------------------------------------------------------------------------- */
// int sdl_MaxCol( SDL *pSdl )
HB_FUNC( SDL_MAXCOL )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );

      hb_retni( pSdl->width / IIF( pSdl->fontCellWidth == 0, FONT_CELL_WIDTH, pSdl->fontCellWidth ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// int sdl_MaxRow( SDL *pSdl )
HB_FUNC( SDL_MAXROW )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );

      hb_retni( pSdl->height / IIF( pSdl->fontCellHeight == 0, FONT_CELL_HEIGHT, pSdl->fontCellHeight ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sdl_GetWindowPosition( SDL *pSdl, int *x, int *y );
HB_FUNC( SDL_GETWINDOWPOSITION )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_BYREF ) != NULL && hb_param( 3, HB_IT_BYREF ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );
      int w, h;
      SDL_GetWindowPosition( pSdl->window, &w, &h );
      hb_storni( w, 2 );
      hb_storni( h, 3 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sdl_GetWindowSize( SDL *pSdl, int *w, int *h );
HB_FUNC( SDL_GETWINDOWSIZE )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_BYREF ) != NULL && hb_param( 3, HB_IT_BYREF ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );
      int w, h;
      SDL_GetWindowSize( pSdl->window, &w, &h );
      hb_storni( w, 2 );
      hb_storni( h, 3 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sdl_SetWindowPosition( SDL *pSdl, int x, int y );
HB_FUNC( SDL_SETWINDOWPOSITION )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL && hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );
      int x = hb_parni( 2 );
      int y = hb_parni( 3 );
      SDL_SetWindowPosition( pSdl->window, x, y );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sdl_SetWindowSize( SDL *pSdl, int w, int h );
HB_FUNC( SDL_SETWINDOWSIZE )
{
   if( hb_param( 1, HB_IT_POINTER ) != NULL && hb_param( 2, HB_IT_NUMERIC ) != NULL && hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
      SDL *pSdl = hb_sdl_Param( 1 );
      int w = hb_parni( 2 );
      int h = hb_parni( 3 );
      SDL_SetWindowSize( pSdl->window, w, h );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

/* -------------------------------------------------------------------------
CategoryMouse
------------------------------------------------------------------------- */
//Uint32 sdl_GetMouseState( int *x, int *y );
HB_FUNC( SDL_GETMOUSESTATE )
{
   if( hb_param( 1, HB_IT_BYREF ) != NULL && hb_param( 2, HB_IT_BYREF ) != NULL )
   {
      int x, y;
      hb_retnint( SDL_GetMouseState( &x, &y ) );
      hb_storni( x, 1 );
      hb_storni( y, 2 );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
