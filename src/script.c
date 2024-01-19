
#include <stdio.h>
#include <raylib.h>

#include "../lib/nature2d.h"

Object boundary;

Object ball = {0};
Object ball2 = {0};

Vec2 controller_direction;

void Init(int width, int height)
{
    body_init(&boundary.body,  vec2zero, 0);
    collider_add_shape(&boundary.colliers, rect(10, 10, width-20, height-20));

    body_init(&ball.body,  vec2(100, 100), 50);
    ball.body.max_speed = 150;
    collider_add_shape(&ball.colliers, circle(0, 0, 30));
    collider_add_shape(&ball.colliers, circle(30, 30, 30));
    collider_add_shape(&ball.colliers, circle(0, 30, 30));
    collider_add_shape(&ball.colliers, circle(-30, 0, 30));

    body_init(&ball2.body, vec2(200, 300), 50);
    collider_add_shape(&ball2.colliers, circle(0, 0, 30));
}

void ProcessEvents(void)
{
    /* controller_direction = vec2zero; */

    int key = GetKeyPressed();
    int x = 0, y = 0;

    if (key == 'F') {
        ToggleFullscreen();
    }
    if (IsKeyDown('H')) {
        x += -1;
       /* controller_direction = vec2(-1, 0); */
    }
    if (IsKeyDown('J')) {
        y += 1;
       /* controller_direction = vec2(0, 1); */
    }
    if (IsKeyDown('K')) {
        y += -1;
       /* controller_direction = vec2(0, -1); */
    }
    if (IsKeyDown('L')) {
        x += 1;
       /* controller_direction = vec2(1, 0); */
    }
    controller_direction = vec2(x, y);
}

void Update(float dt)
{
    if (object_detect_collition(&ball, &ball2)) {
        ball.body.vel = vec2_mult(ball.body.vel, -1);
    }

    /* Vec2 wind = vec2(0, 500); */
    /* body_apply_force(&ball.body, wind); */

    Vec2 force = vec2_set_mag(controller_direction, 200000);
    body_apply_force(&ball.body, force);

    object_update(&ball, dt);
    object_update(&ball2, dt);
}

void Draw(void)
{
    ClearBackground(LIGHTGRAY);

    object_draw(&ball);
    object_draw(&ball2);
    object_draw(&boundary);
}

