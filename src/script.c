
#include <stdio.h>
#include <raylib.h>

#include "../lib/draw_physics2d.h"


Object ball;



void Init(int width, int height)
{
    Vec2 pos = vec2(100, 100);
    double radius = 50;
    body_init(&ball.body, pos, radius);
    collider_add_shape(&ball.colliers, circlev(pos, radius));

    ball.body.max_speed = 100;
}

void ProcessEvents(void)
{
}

void Update(float dt)
{
    Vec2 wind = vec2(1000, 0);
    body_apply_force(&ball.body, wind);

    body_update(&ball.body, dt);

    debug_vec2(ball.body.pos);
    /* object_update(&ball, dt); */
}

void Draw(void)
{
    ClearBackground(LIGHTGRAY);

    draw_shape(ball.body.pos, ball.colliers[0], BLUE);

    /* draw_circle(ball.colliers[0].circle, BLUE); */
    object_draw(&ball);
}

