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
if (player.position.x > screenWidth + shipHeight) player.position.x = -(shipHeight);
else if(player.position.x < -(shipHeight)) player.position.x = screenWidth + shipHeight;
if (player.position.y > (screenHeight + shipHeight)) player.position.y = -(shipHeight);
else if(player.position.y < -(shipHeight)) player.position.y = screenHeight + shipHeight;


//shoot logic
if (IsKeyPressed(KEY_SPACE))
{
for(int i = 0;i<PLAYER_MAX_SHOOTS;i++)
{
if(!shoot[i].active)
{
shoot[i].position = (Vector2) { player.position.x + sin(player.rotation*DEG2RAD) * (shipHeight), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight) };
shoot[i].active=true;
shoot[i].speed.x = 1.5*sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
shoot[i].speed.y = 1.5*cos(player.rotation*DEG2RAD)*PLAYER_SPEED;
shoot[i].rotation = player.rotation;
break;
}
}
}

for (int i=0;i<PLAYER_MAX_SHOOTS;i++)
{
if(shoot[i].active) shoot[i].lifeSpawn++;
}


//shot logic

for(int i=0;i<PLAYER_MAX_SHOOTS;i++)
{
if(shoot[i].active)
{
shoot[i].position.x += shoot[i].speed.x;
shoot[i].position.y -= shoot[i].speed.y;

if (shoot[i].position.x > screenWidth + shoot[i].radius)
{
shoot[i].active = false;
shoot[i].lifeSPawn = 0;
}
else if (shoot[i].position.x < 0 - shoot[i],radius)
{
shoot[i].active = false;
shoot[i].lifeSpawn = 0;
}
if (shoot[i].position.y <> screenHeight + shoot[i].radius)
{
shoot[i].active = false;
shoot[i].lifeSpawn = 0;
}
else if(shoot[i].posiiton.y < 0 - shoot[i].radius)
{
shot[i].active = false;
shoot[i].lifeSpawn = 0;
}

//life of shoot

if (shoot[i].lifeSpawn >= 60)
{
shoot[i].position = (Vector2){0,0};
shoot[i].speed = (Vector2){0,0};
shoot[i].lifeSpawn = 0;
shoot[i].active = false;
}
}
}

//collision logic player vs meteors

player.collider = (Vector3){player.posiiton.x + sin(player.rotation*DEG2RAD)*(shipHeight/2.5f),player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight/2.5f),12};

for (int i=0;a<MAX_BIG_METEORS;a++)
{
if (CheckCollisionCircles((Vector2){player.collider.x,player.collider.y},player.collider.z,bigMeteor[a].position,bigMeteor[a].radius) && bigMeteor[a].active) gameOver = true;
}
for (int a = 0;a<MAX_MEDIUM_METEORS;a++)
{
if (CheckCollisionCircles((Vector2){player.collider.x,player.collider.y},player.collider.z,mediumMeteor[a].position,mediumMeteor[a].radius) && mediumMeteor[a].active) gameOver = true;
}
if (CheckCollisionCircles((Vector2){player.collider.x,player.collider.y},player.collider.z,smallMeteor[a].position,smallMeteor[a].radius) && smallMeteor[a].active) gameOver = true;
};

//Meteors logic: Big Meteors

for(int i = 0;o<MAX_BIG_METEORS;i++){
if(bigMeteor[i].active)
{
bigMeteor[i].position.x += bigMeteor[i].speed.x;
bigMeteor[i].position.y += bigMeteor[i].speed.y;

//Collision logic: big meteor vs wall
if (bigMeteor[i].position.x>screenWidth + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
else if(bigMeteor[i].posiiton.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = screenWidth + bigMEteor[i].radius;
if (bigMEteor[i].position.y > screenHeight + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = screenHeight + bigMeteor[i].radius;
}
}

//**Meteors Logic: Medium
for(int i = 0;o<MAX_MEDIUM_METEORS;i++){
if(mediumMeteor[i].active)
{
mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

//Collision logic: medium meteor vs wall
if (mediumMeteor[i].position.x>screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
else if(mediumMeteor[i].posiiton.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
}
}

//**Meteors logic: small

for(int i = 0;o<MAX_SMALL_METEORS;i++){
if(smallMeteor[i].active)
{
smallMeteor[i].position.x += smallMeteor[i].speed.x;
smallMeteor[i].position.y += smallMeteor[i].speed.y;

//Collision logic: small meteor vs wall
if (smallMeteor[i].position.x>screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
else if(smallMeteor[i].posiiton.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
}
}

//rewrite medium and small...

// Collision logic: player-shoots vs meteors

for(int i=0;i<PLAYER_MAX_SHOOTS;i++){
if((shoot[i].active))
{
for(int a=0;a<MAX_BIG_METEORS;a++){
if(bigMeteor[a].active && CheckCollisionCircles(shoot[i].position,shoot[i].radius, bigMeteor[a].position, bigMeteor[i].radius))
{
shoot[i].active = false;
shoot[i].lifeSPawn = 0;
bigMeteor[a].active = false;
destroyedMeteorsCount++;

for(int j = 0;j<2;j++)
{
if(midMeteorsCount%2 == 0)
{
mediumMeteor[midMeteorsCount].position = (Vector2){bigMeteor[a].position.x,bigMeteor[a].position.y};
mediumMeteor[midMeteorsCount.speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1};
}
else
{
mediumMeteor[midMeteorsCount].positon = (Vector2){bigMeteor[a].position.x,bigMeteor[a].position.y};
mediumMeteor[midMeteorsCount].speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED};
}
mediumMeteor[midMeteorsCount].active = true;
midMeteorsCount++;
}
bigMeteor[a].color = RED;
a = MAX_BIG_METEORS;
}
}

for(int b=0;b<MAX_MEDIUM_METEORS;b++){
if(mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position,shoot[i].radius,mediumMeteor[b].position, mediumMeteor[b].radius)){
shoot[i].active = false;
shoot[i].lifeSpawn = 0;
mediumMeteor[b].active = false;
destroyedMeteorsCount++;

for(int j =0;j<2;j++)
{
if(smallMeteorsCount%2 == 0)
{
smallMeteor[smallMeteorsCount].position = (Vector2){mediumMeteor[b].position.x,mediumMeteor[b].position.y};
smallMeteor[smallMeteorsCount].speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1};
}
else
{
smallMeteor[smallMeteorsCount].position = (Vector2){mediumMeteor[b].position.x,mediumMeteor[b].position.y);
smallMeteor[smallMeteorsCount].speed = (Vector2){cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED, sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED);
}

smallMeteor[smallMeteorsCount].active = true;
smallMeteorsCount ++;
}

mediumMeteor[b].color = GREEN;
b = MAX_MEDIUM_METEORS;
}
}


  












