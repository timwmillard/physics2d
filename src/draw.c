// #include <stdio.h>
#include <raylib.h>
#include <time.h>

#include "../lib/physics2d.h"


typedef struct Ball {
    int radius;
    Color color;

    Body body;
} Ball;

Ball player = {
    .color = BLUE,
    .radius = 50,
    .body = {
        .pos = {100, 100},
        .mass = 50,
    }
};

Ball player1 = {
    .color = GREEN,
    .radius = 100,
    .body = {
        .pos = {400, 100},
        .mass = 100,
    }
};

Vec2 gravity = {0, 6};
Vec2 mouse =  {0, 0};


bool start = false;

void Init()
{
    srand(time(NULL));

    Vec2 r = vec2_random();
    debug_vec2(r);
}

void ProcessEvents()
{
    int key = GetKeyPressed();
    if (key == 'S') {
        if (start) {
            player.body.pos = vec2(100, 100);
            player1.body.pos = vec2(400, 100);
        }
        start = !start;
    }

    int mouse_x = GetMouseX();
    int mouse_y = GetMouseY();
    mouse = vec2(mouse_x, mouse_y);

    /* if (IsMouseButtonDown(0)) { */
    /*     Vec2 wind = vec2(mouse_x, mouse_y); */
    /*     wind = vec2_set_mag(wind, -200); */
    /*     body_apply_force(&player.body, wind); */
    /*     body_apply_force(&player1.body, wind); */
    /* } */
}

void body_bounce(Body *body, Rect bounds)
{
    double min_y = bounds.pos.y + bounds.height;
    if (body->pos.y > min_y) {
        // Apply Normal force
        Vec2 n = vec2_mult(gravity, -1);
        body->vel = n;
        body->pos.y = min_y;
    }
}


void Update(float dt)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    Rect screen = {0,0, screenWidth, screenHeight};

    if (start) {
        body_bounce(&player.body, screen);
        body_bounce(&player1.body, screen);

        /* Vec2 acc = vec2(3, 0); */
        /* Vec2 acc = vec2_random(); */
        /* acc = vec2_mult(acc, 1000); */
        /* Vec2 acc = vec2_mult(mouse, 0.1); */
        Vec2 acc = vec2_sub(mouse, player.body.pos);
        double fac = vec2_mag(acc);
         acc = vec2_set_mag(acc, fac);
        
        body_apply_force(&player.body, acc);

        /* body_apply_gravity(&player.body, gravity); */
        body_update(&player.body, dt);
        /* body_apply_gravity(&player1.body, gravity); */
        body_update(&player1.body, dt);

    }
}

void draw_ball(Ball ball)
{
    DrawCircle(ball.body.pos.x, ball.body.pos.y, ball.radius, ball.color);
}

void Draw()
{
    ClearBackground(RAYWHITE);
    draw_ball(player);
    draw_ball(player1);

    DrawText("Inside draw.c", 190, 200, 20, LIGHTGRAY);
}

