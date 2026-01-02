#include "raylib.h"
#include <stdio.h>

#define FPS 120
#define WIDTH 900
#define HEIGHT 600
#define THICK 5
#define MASS_SIDE_LENGTH 100
#define FLOOR_Y (HEIGHT * 0.6)

#define NUMBER_SPRING_ELEMENTS 8
#define SPRING_ELEMENT_LENGTH 15

float xMass;
void drawSpring() {
    float xSpringDelta = xMass / NUMBER_SPRING_ELEMENTS;
    for (int i = 0; i < NUMBER_SPRING_ELEMENTS; i++) {
        Vector2 start = {xSpringDelta * xMass, FLOOR_Y - (float)MASS_SIDE_LENGTH / 2};
        Vector2 end = {start.x};
    }
}

void drawFloor() {
    Vector2 start = {0, FLOOR_Y};
    Vector2 end = {WIDTH, FLOOR_Y};
    DrawLineEx(start, end, THICK, GRAY);
}

void drawMass() {
    Rectangle rect = {xMass, FLOOR_Y - MASS_SIDE_LENGTH - (float)THICK / 2, MASS_SIDE_LENGTH,
                      MASS_SIDE_LENGTH};
    DrawRectangleRec(rect, RED);
}

int main() {
    printf("Hello Spring simulation\n");
    InitWindow(WIDTH, HEIGHT, "Spring on Mass Simulation");
    SetTargetFPS(FPS);

    float velocity = 20;
    float deltaTime;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);

        deltaTime = GetFrameTime();
        xMass += velocity * deltaTime;
        drawFloor();
        drawMass();
        drawSpring();
        DrawText("Spring on Mass Simulation", WIDTH / 10, 100, 30, GREEN);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
