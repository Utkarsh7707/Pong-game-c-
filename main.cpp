#include <iostream>
#include <raylib.h>
#include<vector>
using namespace std;


int player_score = 0;
int cpu_score = 0;
Color Green = Color{38,185,154,255};
Color Dark_Green = Color{20,160,133,255};
Color Light_Green = Color{129,204,184,255};
Color Yellow = Color{243,213,91,255};

class Ball{
    protected:
    void reset_ball()
    {
        posx = GetScreenWidth()/2;
        posy = GetScreenHeight()/2;
        vector<int> choices = {-1,1};
        speed_x *= choices[GetRandomValue(0,1)];   
        speed_y *= choices[GetRandomValue(0,1)];   
    }
    public:
    float posx,posy;
    float speed_x;
    float speed_y;
    int radius;
    void Draw()
    {
        DrawCircle(posx,posy,radius,Yellow);
    }
    void update()
    {
        posx += speed_x;
        posy += speed_y;

        if(posx + radius >= GetScreenWidth())
        {
            cpu_score++;
            reset_ball();
        }
        
        if(posx - radius <= 0)
        {
            // speed_x *= -1;
            player_score++;
            reset_ball();
        }
        if(posy + radius >= GetScreenHeight() || posy - radius <= 0)
        {
            speed_y *= -1;
        }
    }
};

class platform{
    protected:
    void limitMovement()
    {
         if(posy <= 0)
        {
            posy = 0;
        }
        if(posy + height >= GetScreenHeight())
        {
            posy = GetScreenHeight()-height;
        }
    }
    public:
    float posx,posy;
    float speed;
    float width ,height;
    void draw()
    {
        DrawRectangleRounded(Rectangle{posx,posy,width,height},0.8,0,WHITE);
    }
    void update()
    {
        if(IsKeyDown(KEY_UP))
        {
            posy = posy - speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            posy = posy+speed;
        }
        limitMovement();
    }
};

class CPU_platform :public platform{
    public:
    void update(float ball_pos_y)
    {
        if(posy + height/2 > ball_pos_y)
        {
            posy = posy - speed;
        }
        if(posy + height/2 <= ball_pos_y )
        {
            posy = posy + speed;
        }
        limitMovement();
    }

};
Ball ball;
platform p1;
CPU_platform p2;
int main () {
    cout<<"Starting game"<<endl;
    const int screen_width = 1200;
    const int screen_height = 800;
    const char* title = "my pong game !";
    InitWindow(screen_width,screen_height,title);
    SetTargetFPS(60);
    ball.posx = screen_width/2;
    ball.posy = screen_height/2;
    ball.radius = 20;
    ball.speed_x = 6.5;
    ball.speed_y = 6.5;
    p1.posx = screen_width-35;
    p1.posy = screen_height/2 - (120/2); 
    p1.width = 25;
    p1.height = 120;
    p1.speed = 10;

    p2.posx = 10;
    p2.posy = screen_height/2 - 120/2;
    p2.width = 25;
    p2.height = 120;
    p2.speed = 5.5;
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width/2,0,screen_width/2,screen_height,Green);
        DrawCircle(screen_width/2,screen_height/2,150,Light_Green);
        ball.update();
        p1.update();
        p2.update(ball.posy);
        
        if(CheckCollisionCircleRec(Vector2{ball.posx,ball.posy},ball.radius,Rectangle{p1.posx,p1.posy,p1.width,p1.height}))
        {
            ball.speed_x *= -1;
            // ball.posx = ball.posx - ball.radius;
        }
        if(CheckCollisionCircleRec(Vector2{ball.posx,ball.posy},ball.radius,Rectangle{p2.posx,p2.posy,p2.width,p2.height}))
        {
            ball.speed_x *= -1;
            // ball.posx = ball.posx - ball.radius + p2.width;
        }
        DrawText(TextFormat("%i",cpu_score),screen_width/4,20,80,WHITE);
        DrawText(TextFormat("%i",player_score),3*screen_width/4,20,80,WHITE);
        DrawLine(screen_width/2,screen_height,screen_width/2,0,WHITE);
        ball.Draw();
        p1.draw();
        p2.draw();
        EndDrawing();
    }
    return 0;
}