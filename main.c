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


typedef struct Player {
Vector2 position;
Vector2 speed;
float acceleration;
float rotation;
Vector3 collider;
Color color;
};

typedef struct Shoot {
Vector2 position;
Vector2 speed;
float radius;
float rotation;
int lifeSpawn;
bool active;
Color color;
};

typedef struct Meteor {
Vector2 position;
Vector2 speed;
float radius;
bool active;
Color color;
};

static const int screenWidth = 800
static const int screenHeight = 450
  
static bool gameOver = false;
static bool pause = false;
static bool victory = false;

static float shipHeight = 0.0f;

static Player player = { 0 };
static Shoot shoot[PMS] = { 0 };
static Meteor bigMeteor[MAX_BIG_METEORS] = { 0 };
static Meteor mediumMeteor[MAX_MEDIUM_METEORS] = { 0 };
static Meteor smallMeteor[MAX_SMALL_METEORS] = { 0 };

static int midMeteorsCount = 0;
static int smallMeteorsCount = 0;
static int destroyedMeteorsCount = 0;

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);

int main(void){

  InitWindow(screenWidth,screenheight,"Classic Game: Asteroids");

InitGame();

#if defined(PLATFORM_WEB)
emscripten_set_main_loop(UpdateDrawFrame,60,1);
#else
SetTargetFPS(60);

while (!WindowShoudClose())
{
UpdateDrawFrame();
};
#endif

UnloadGame();
CloseWindow();

return 0;
};

void InitGame(void){
  int posx, posy;
  int velx, vely;
  bool correctRange = false;
  victory = false;
  pause = false;

  shipHeight = (PLAYER_BASE_SIZE/2)/tanf(20*DEG2RAD);








