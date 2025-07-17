#include "raylib.h"

#include "math.h"

#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
#endif

''P = player , S= speed, SZ = size B= base MS = max shoots MX = max
#define PBSZ = 20.0f
#define PS = 6.0f
#define PMS = 10

  
#define METEORS_SPEED  2
#define MAX_BIG_METEORS  4
#define MAX_MEDIUM_METEORS  8
#define MAX_SMALL_METEORS  16

