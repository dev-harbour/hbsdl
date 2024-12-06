#ifndef HBSDL_H_
#define HBSDL_H_

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "hbapi.h"
#include "hbapierr.h"
#include "hbapiitm.h"

#define FONT_CELL_WIDTH   9
#define FONT_CELL_HEIGHT 18

typedef struct _SDL SDL;

typedef enum _bool bool;

enum _bool
{
   F = 0,
   T = ( ! 0 )
};

struct _SDL
{
   SDL_Window   *window;
   SDL_Renderer *renderer;
   int           width;
   int           height;
   int           widthPos;
   int           heightPos;
   int           mouseX;
   int           mouseY;

   int           cursorCol;
   int           cursorRow;
   SDL_TimerID   cursorTimer;
   bool          cursorVisible;

   TTF_Font     *font;
   int           fontCellWidth;
   int           fontCellHeight;
   int           fontSize;

   const char   *background;
};

HB_EXTERN_BEGIN
extern SDL_Window *hb_sdl_window_Param( int iParam );
extern PHB_ITEM    hb_sdl_window_ItemPut( PHB_ITEM pItem, SDL_Window *pSDL_Window );
extern void        hb_sdl_window_Return( SDL_Window *pSDL_Window );

extern SDL_Event  *hb_sdl_event_Param( int iParam );
extern SDL_Event  *hb_sdl_event_ParamGet( int iParam );
extern SDL_Event  *hb_sdl_event_ItemGet( PHB_ITEM pItem );
extern PHB_ITEM    hb_sdl_event_ItemPut( PHB_ITEM pItem, SDL_Event *pSDL_Event );
extern void        hb_sdl_event_ItemClear( PHB_ITEM pItem );
extern void        hb_sdl_event_StorPtr( SDL_Event *pSDL_Event, int iParam );
extern void        hb_sdl_event_Return( SDL_Event *pSDL_Event );
HB_EXTERN_END

/* -------------------------------------------------------------------------
Macro Definitions
------------------------------------------------------------------------- */
#define HB_ERR_ARGS() ( hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS ) )

#define MAX( a, b ) \
   ( { typeof( a ) _a = ( a ); typeof( b ) _b = ( b ); _a < _b ? _b : _a; } )
#define MIN( a, b ) \
   ( { typeof( a ) _a = ( a ); typeof( b ) _b = ( b ); _a < _b ? _a : _b; } )
#define UNUSED( n ) ( ( void )( n ) )
#define LEN( n ) ( sizeof( n ) / sizeof( ( n )[ 0 ] ) )
#define IIF( condition, trueValue, falseValue ) ( ( condition ) ? ( trueValue ) : ( falseValue ) )

#endif /* End HBSDL_H_ */
