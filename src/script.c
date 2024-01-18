
#include <stdio.h>
#include <raylib.h>

#include "../lib/draw_physics2d.h"


Object ball;



void Init(int width, int height)
{

    Vec2 pos = vec2(100, 100);
    double radius = 50;
    body_init(&ball.body, pos, radius);
    collider_add_shape(ball.colliers, circlev(pos, radius));
}

void ProcessEvents(void)
{
}

void Update(float dt)
{
    object_update(&ball, dt);
}

void Draw(void)
{
    ClearBackground(LIGHTGRAY);


    draw_circle(ball.colliers[0].circle, BLUE);
    object_draw(&ball);
}

