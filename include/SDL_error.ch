#ifndef SDL_ERROR_CH_
#define SDL_ERROR_CH_

#define SDL_OutOfMemory()               SDL_Error( SDL_ENOMEM )
#define SDL_Unsupported()               SDL_Error( SDL_UNSUPPORTED )

#define SDL_ENOMEM                      0
#define SDL_EFREAD                      1
#define SDL_EFWRITE                     2
#define SDL_EFSEEK                      3
#define SDL_UNSUPPORTED                 4
#define SDL_LASTERROR                   5

#endif /* End SDL_ERROR_CH_ */
