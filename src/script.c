
#include <stdio.h>
#include <raylib.h>

#include "../lib/draw_physics2d.h"


Object ball;



void Init(int width, int height)
{
    Vec2 pos = vec2(100, 100);
    double radius = 50;
    body_init(&ball.body, pos, radius);
    collider_add_shape(&ball.colliers, rect(10, -10, 500, 50));
    collider_add_shape(&ball.colliers, circle(50, 50, 50));
    collider_add_shape(&ball.colliers, circle(100,100, 10));
    collider_add_shape(&ball.colliers, line(0,0, -100, -100));

    /* ball.body.max_speed = 100; */
}

void ProcessEvents(void)
{
    if (GetKeyPressed() == 'F') {
        ToggleFullscreen();
    }
}

void Update(float dt)
{
    Vec2 wind = vec2(0, 500);
    body_apply_force(&ball.body, wind);

    object_update(&ball, dt);
}

void Draw(void)
{
    ClearBackground(LIGHTGRAY);

    object_draw(&ball);
}

