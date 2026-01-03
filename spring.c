#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define FPS 120
#define WIDTH 900
#define HEIGHT 600
#define THICK 5
#define MASS_SIDE_LENGTH 100
#define FLOOR_Y (HEIGHT * 0.6)

#define NUMBER_SPRING_ELEMENTS 16
#define SPRING_ELEMENT_LENGTH 60
#define K 20
#define X_REST (WIDTH / 3)
#define FRICTION 0.5

float xMass = WIDTH * 0.7;
float a = 2; // Isso aqui me parece inútil
float velocity = 20;

typedef struct {
    Vector2 start, end;
} SpringElement;

SpringElement springElements[SPRING_ELEMENT_LENGTH];

void drawSpring() {
    float xSpringDelta = xMass / NUMBER_SPRING_ELEMENTS;
    float yEnd = sqrt(pow(SPRING_ELEMENT_LENGTH, 2) - pow(xSpringDelta, 2));
    for (int i = 0; i < NUMBER_SPRING_ELEMENTS; i += 2) {
        Vector2 start = {xSpringDelta * i,
                         FLOOR_Y - (float)MASS_SIDE_LENGTH / 2 + (float)SPRING_ELEMENT_LENGTH / 2};
        Vector2 end = {start.x + xSpringDelta, start.y - yEnd};
        springElements[i] = (SpringElement){start, end};
        DrawLineEx(start, end, THICK, LIGHTGRAY);
    }
    for (int i = 1; i < NUMBER_SPRING_ELEMENTS; i += 2) {
        Vector2 start = springElements[i - 1].end;
        Vector2 end = {start.x + xSpringDelta, start.y + yEnd};
        springElements[i] = (SpringElement){start, end};
        DrawLineEx(start, end, THICK, LIGHTGRAY);
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
    InitWindow(WIDTH, HEIGHT, "Mass on Spring Simulation");
    SetTargetFPS(FPS);

    float deltaTime;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);

        deltaTime = GetFrameTime();
        float friction = a > 0 ? FRICTION : -FRICTION;
        a = -K * (float)(xMass - (float)X_REST) - velocity * FRICTION;
        velocity += a * deltaTime;
        xMass += velocity * deltaTime;
        drawFloor();
        drawMass();
        drawSpring();
        DrawText("Mass on Spring Simulation", WIDTH / 10, 100, 30, GREEN);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
