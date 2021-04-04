
#ifndef BRICK_H
#define BRICK_H
#include <cmath>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#define BRICK_WIDTH 64
#define BRICK_HEIGH 24
#define BRICK_ROW_NF 12
#define BRICK_COL_NF 12
#define BALL_SPEED 550

class brick{
public:
    bool state;
    int type;
};
class paddle{
public:
    int x,y;
    int width,height;
};

class ball{
public:
    int x,y;
    int width,height;
    float dirx,diry;
};
class bricks{
public:
    bricks(SDL_Renderer *renderer);//initial brick sence  
    ~bricks();//deconstruction
    void SetScreen(int width,int height);
    void Render(SDL_Renderer *renderer);
    void initial_brick(void);
    void SetPaddleX(float x);
    void ResetPaddle();
    void SetBallDirection(float dirx,float diry);
    void update();
    void BoardCollision();
    bool PaddleCollision();
    void BrickCollision();
    void HandleMouseInput()  ;
    brick Brick[BRICK_ROW_NF][BRICK_COL_NF];
    paddle Paddle;
    ball Ball;
    //int brickOffsetX;
    //int brickOffsetY;
    int x;
    int y;
private:
    int ScreenWidth,ScreenHeight;
    //SDL_Texture *brickTexture;
    //SDL_Texture *sideTexture;
};
#endif