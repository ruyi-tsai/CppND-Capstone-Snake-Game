# CppND-Capstone-Snake-Game
This gaming is modified by snake game source . I try to build brick game. In The Pong Tutorial, we introduced paddle movement, ball movement and simple collisions. In Breakout, there is no Artificial Intelligence. The player has to clear a board of bricks by shooting a ball against them. He controls a horizontal paddle and must prevent the ball from leaving the bottom part of the screen. When all of the bricks are removed from the board, a new level should be presented. In addition to the mechanics we implemented for Pong, a game like Breakout needs level management and more complex brick-ball collisions.
# Basic Build Instructions
- 1.Clone this repo.
- 2.Make a build directory in the top level directory: mkdir build && cd build
- 3.Compile: cmake .. && make
- 4.Run it: ./SnakeGame.
# Define brick states

```ruby
//state means : brick is alive or death
//type : determin brick color
class brick{
public:
    bool state;
    int type;
};
```
For this tutorial, I generated a very simple level, where every brick is present, but has a random color. The type is generated in the initial_brick function.
```ruby
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
           
```
 #Ball-Brick Collisions
 The most complex feature of a Breakout game is determining and resolving collisions between a ball and the bricks. 
 We can divide this feature in three steps:
 - Determine that there is a collision
 ```ruby

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

           
```
 - Give a collision response 
  ```ruby


    if(ballcenterX<=brickx+BRICK_WIDTH && ballcenterX>=brickx && ballcenterY<=bricky+BRICK_HEIGH && ballcenterY>=bricky)
    {
       
        #Ball.diry *=-1;
                
    }
 
           
```
 
