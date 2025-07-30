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

player.position =(Vector2){screenWidth/2,screenHeight/2 -shipHeight/2};
player.speed =(Vector2){0,0};
player.acceleration = 0;
player.rotation =0;
player.collider=(Vector3){player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight/2.5f),player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight/2.5f),12);
player.color=LIGHTGRAY;


destroyedMeteorsCount = 0;

for(int i=0;i<PLAYER_MAX_SHOOTS;i++){
shoot[i].position=(Vector2){0,0};
shoot[i].speed=(Vector2){0,0};
shoot[i].radius=2;
shoot[i].active=false;
shoot[i].lifeSpawn=0;
shoot[i].color=WHITE;
};

for(int i=0;i<MAX_BIG_METEORS;i++){
posx=GetRandomValue(0,screenWidth);
while(!correctRange){
if(posx>screenWidth/2-150 && posx < screenWidth/2 + 150) {
posx = GetRandomValue(0,screenWidth);
};
else{
  correctRange=true;
    };

correctRange = false;

posy=GetRandomValue(0,screenHeight);

while(!correctRange)
{
if(posy > screenHeight/2 - 150 && posy < screenHeight/2 + 150){
posy=GetRandomValue(0;screenHeight);
};
else{
correctRange=true;
};

bigMeteor[i].position = (Vector2){posx,posy};

correctRange=false;
velx = GetRandomValue(-METEORS_SPEED,METEORS_SPEED);
vely = GetRandomValue(-METEORS_SPEED,METEORS_SPEED);

while(!correctRange){
if(velx == 0 && vely ==0){
velx = GetRandomValue(-METEORS_SPEED,METEORS_SPEED);
vely = GetRandomValue(-METEORS_SPEED,METEORS_SPEED);
};
else{
correctRange = true;
};

bigMeteor[i].speed=(Vector2){velx,vely};
bigMeteor[i].radius=40;
bigMeteor[i].active=true;
bigMeteor[i].color=BLUE;
}

for(int i =0;i<MAX_MEDIUM_METEORS;i++){
mediumMeteor[i].position=;
mediumMeteor[i].speed=;
mediumMeteor[i].radius=;
mediumMeteor[i].active=;
mediumMeteor[i].color=BLUE;
};


for(int i=0;i<MAX_SMALL_METEORS;i++){
smallMeteor[i].position=;
smallMeteor[i].speed=;
smallMeteor[i].radius=;
smallMeteor[i].active=;
smallMeteor[i].color=BLUE;
};

midMeteorsCount = 0;
smallMeteorsCount = 0;

};

//update game frame

void UpdateGame(void)
{
  if(!gameOVer)
{
if(IsKeyPressed('P')) pause = !pause;

if (!pause)
{
if (IsKeyDown(KEY_LEFT)) player.rotation -=5;
if (IsKeyDown(KEY_RIGHT)) play.rotation +=5;

player.speed.x = sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
player.speed.y = cos(player.rotation.DEG2RAD)*PLAYER_SPEED;

if(IsKeyDown(KEY_UP))
{
if(player.acceleration <1) player.acceleration += 0.04f;
}
else
{
if(player.acceleration > 0) player.acceleration -= 0.02f;
else if(player.acceleration < 0) player.acceleration = 0;
}
if (IsKeyDown(KEY_DOWN))
{
if(player.acceleration > 0) player.acceleration -= 0.04f;
else if(player.acceleration < 0) player.acceleration = 0;
}

player.position.x += (player.position.x*player.acceleration);
  player.position.y -= (player.position.y*player.acceleration);

//collision logic

