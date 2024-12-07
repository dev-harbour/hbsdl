#ifndef SDL_RENDER_CH_
#define SDL_RENDER_CH_

#define SDL_RENDERER_SOFTWARE       0x00000001
#define SDL_RENDERER_ACCELERATED    0x00000002
#define SDL_RENDERER_PRESENTVSYNC   0x00000004
#define SDL_RENDERER_TARGETTEXTURE  0x00000008

#define SDL_ScaleModeNearest        0
#define SDL_ScaleModeLinear         1
#define SDL_ScaleModeBest           2

#define SDL_TEXTUREACCESS_STATIC    0
#define SDL_TEXTUREACCESS_STREAMING 1
#define SDL_TEXTUREACCESS_TARGET    2

#define SDL_TEXTUREMODULATE_NONE    0x00000000
#define SDL_TEXTUREMODULATE_COLOR   0x00000001
#define SDL_TEXTUREMODULATE_ALPHA   0x00000002

#define SDL_FLIP_NONE               0x00000000
#define SDL_FLIP_HORIZONTAL         0x00000001
#define SDL_FLIP_VERTICAL           0x00000002

#endif /* End SDL_RENDER_CH_ */
