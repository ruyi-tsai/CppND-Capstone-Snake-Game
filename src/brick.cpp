#include "brick.h"

void bricks::initial_brick(void)
{
    for(int i=0;i<BRICK_ROW_NF;i++)
    {
        for(int j=0;j<BRICK_COL_NF;j++)
        {
            Brick[j][i].type = rand()%4;
            Brick[j][i].state = true;
        }
    }

}
bricks::bricks(SDL_Renderer *renderer)
{
    initial_brick();
    ResetPaddle();
}
bricks::~bricks()
{
  

}
void bricks::Render(SDL_Renderer *renderer)
{
   
    for(int i=0;i<BRICK_COL_NF;i++) 
    {
        for(int j=0;j<BRICK_ROW_NF;j++)
        {
            brick _brick =  Brick[i][j];
            if(!_brick.state)
                continue;
            SDL_Rect src_brick;
            src_brick.x = (_brick.type %2)*BRICK_WIDTH;
            src_brick.y = (_brick.type >>1)*BRICK_HEIGH;
            src_brick.w = BRICK_WIDTH;
            src_brick.h = BRICK_HEIGH;

            SDL_Rect dst_brick;
            dst_brick.x =  x+ i*BRICK_WIDTH;
            dst_brick.y =  y +j*BRICK_HEIGH;
            dst_brick.w = BRICK_WIDTH;
            dst_brick.h = BRICK_HEIGH;
           
            switch(_brick.type)
            {
                case 0: 
                SDL_SetRenderDrawColor(renderer, 0x00, 0x7A, 0xCC, 0xFF);
                break;
                case 1:
                SDL_SetRenderDrawColor(renderer, 0x7A, 0x00, 0xCC, 0xFF);
                break;
                case 2:
                SDL_SetRenderDrawColor(renderer, 0x7A, 0x7A, 0x00, 0xFF);
                break;
                case 3:
                SDL_SetRenderDrawColor(renderer, 0x7A, 0xCC, 0x10, 0xFF);
                break;

            }
            
            SDL_RenderFillRect(renderer, &dst_brick);
            //std::cout << j<<"\n"<<i<<"\n";
        }
    }
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xFF);
    SDL_Rect _paddle;
    _paddle.x = Paddle.x;
    _paddle.y = Paddle.y;
    _paddle.w = Paddle.width;
    _paddle.h = Paddle.height;
    SDL_RenderFillRect(renderer, &_paddle);
    
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xFF);
    SDL_Rect _ball;
    _ball.x = Ball.x;
    _ball.y = Ball.y;
    _ball.w = Ball.width;
    _ball.h = Ball.height;
    SDL_RenderFillRect(renderer, &_ball);
    update();
    //std::cout << "bricks Render!\n";
    
}

void bricks::SetPaddleX(float x)
{

   float mx = x;
   if(mx<Paddle.width/2.0f)
   {
        Paddle.x = Paddle.width/2.0f;   
   }
   else if(mx>640-Paddle.width/2.0f) 
   {
        Paddle.x=640-Paddle.width/2.0f;
   }
   else
   {
       Paddle.x = mx;

   }

}
void bricks::SetScreen(int width,int height)
{
    ScreenWidth = width;
    ScreenHeight = height;

}
 void bricks::ResetPaddle()
 {
    Paddle.width = 128;
    Paddle.height = 32;
    Paddle.x = 280;
    Paddle.y = 560;
    Ball.x=280;
    Ball.y=530;
    Ball.width = 30;
    Ball.height = 30;
    SetBallDirection(1,-1);
 }
void bricks::SetBallDirection(float dirx,float diry)
{
    float length = sqrt(dirx*dirx+diry*diry);
    Ball.dirx = BALL_SPEED*(dirx/length);
    Ball.diry = BALL_SPEED*(diry/length);

}
void bricks::update()
{
    Ball.x +=Ball.dirx*0.01;
    Ball.y +=Ball.diry*0.01;
    BoardCollision();
    PaddleCollision();
    BrickCollision();
    HandleMouseInput();
}


void bricks::BoardCollision()
{
    if(Ball.y<-Ball.height/2.0f)
    {
        //Ball.y = Ball.height;
        Ball.diry *=-1;
    }
    else if((Ball.y+Ball.height/2.0f)>640-Ball.height)
    {
        ResetPaddle();
    }
    if(Ball.x<-Ball.width/2.0f)
    {
       // Ball.x = Ball.width;
        Ball.dirx *=-1;
    }
    else if(Ball.x>640-Ball.width/2.0f)
    {
        //Ball.x = 640-Ball.width;
        Ball.dirx *=-1;
    }


}

bool bricks::PaddleCollision()
{
   if(Ball.x+Ball.width>Paddle.x && Ball.x<Paddle.x+Paddle.width &&  
      Ball.y+Ball.height>Paddle.y && Ball.y<Paddle.y+Paddle.height)
      {
          Ball.diry *=-1;
          return true;
          
      } 
      return false;

}

void bricks::BrickCollision()
{
    for(int i=0;i<BRICK_ROW_NF;i++)
    {
        for(int j=0;j<BRICK_COL_NF;j++)
        {
            brick _brick =  Brick[i][j];
            if(!_brick.state)
                continue;
            float brickx = i*BRICK_WIDTH;
            float bricky = j*BRICK_HEIGH;
            float ballcenterX = Ball.x+Ball.width/2.0f;
            float ballcenterY = Ball.y+Ball.height/2.0f;
            float brickcenterX = brickx+BRICK_WIDTH/2.0f;
            float brickcenterY = bricky+BRICK_HEIGH/2.0f;
            if(ballcenterX<=brickx+BRICK_WIDTH && ballcenterX>=brickx && ballcenterY<=bricky+BRICK_HEIGH && ballcenterY>=bricky)
            {
                Brick[i][j].state = false;
                 Ball.diry *=-1;
                
            }
            
            
        }
    }


}

void bricks::HandleMouseInput()  
{
    int mx,my;
    int mstate = SDL_GetMouseState(&mx,&my);
    SetPaddleX(mx-Paddle.width/2.0f);
    //std::cout<<mx<<"\n"<<my<<"\n";
}
