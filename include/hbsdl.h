#ifndef HBSDL_H_
#define HBSDL_H_

#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "hbapi.h"
#include "hbapierr.h"
#include "hbapiitm.h"

#define FONT_CELL_WIDTH   9
#define FONT_CELL_HEIGHT 18

typedef struct _MR   MR; // Memory Record
typedef struct _SDL SDL;

typedef enum _bool bool;

enum _bool
{
   F = 0,
   T = ( ! 0 )
};

struct _MR
{
   void       *ptr;
   size_t      size;
   const char *file;
   int         line;
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
extern void *debug_malloc( size_t size, const char *file, int line );
extern void  debug_free( void *ptr, const char *file, int line );
extern void  debug_memory_report( void );
HB_EXTERN_END

/* -------------------------------------------------------------------------
Macro Definitions
------------------------------------------------------------------------- */
#define hb_xgrab( size ) debug_malloc( size, __FILE__, __LINE__ )
#define hb_xfree( ptr ) debug_free( ptr, __FILE__, __LINE__ )

#define HB_ERR_ARGS() ( hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS ) )

#define MAX( a, b ) \
   ( { typeof( a ) _a = ( a ); typeof( b ) _b = ( b ); _a < _b ? _b : _a; } )
#define MIN( a, b ) \
   ( { typeof( a ) _a = ( a ); typeof( b ) _b = ( b ); _a < _b ? _a : _b; } )
#define UNUSED( n ) ( ( void )( n ) )
#define LEN( n ) ( sizeof( n ) / sizeof( ( n )[ 0 ] ) )
#define IIF( condition, trueValue, falseValue ) ( ( condition ) ? ( trueValue ) : ( falseValue ) )

#endif /* End HBSDL_H_ */
