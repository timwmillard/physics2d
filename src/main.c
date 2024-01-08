#include <stdio.h>
#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void);     // Update and Draw one frame

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Dodge Ball");

    // Main game loop
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();

    return 0;
}

void UpdateDrawFrame(void)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Build your cool app", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}

