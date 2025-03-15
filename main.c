#include "src/config.h"
#include "src/networking/socket.h"
#include <raylib.h>
#include <stdio.h>

int main(int argc, char **argv) {
   Conn *c = conCreate(0, NULL);
   conKill(c);
   InitWindow(INIT_WIN_WIDTH, INIT_WIN_HEIGHT, "projekt grafika II");
   Camera3D mainCammera = {0};
   mainCammera.position = (Vector3){0.0f, 10.0f, 10.0f};
   mainCammera.target = (Vector3){0.0f, 0.0f, 0.0f};
   mainCammera.up = (Vector3){0.0f, 1.0f, 0.0f};
   mainCammera.fovy = 45.0f;
   mainCammera.projection = CAMERA_PERSPECTIVE;
   DisableCursor();
   SetTargetFPS(TARGET_FPS);
   char timeText[100];
   unsigned long time = 1201;
   float frameTime = 0;

   while (!WindowShouldClose()) {
      frameTime += GetFrameTime();
      if (frameTime >= 1) {
         frameTime -= 1;
         time -= 1;
      }

      sprintf(timeText, "Time: %lu:%lu", time / 60, time % 60);

      UpdateCamera(&mainCammera, CAMERA_FREE);
      BeginDrawing();
      ClearBackground(WHITE);

      BeginMode3D(mainCammera);

      // DrawGrid(32, 1.0f);

      // szachownica
      for (int y = 0; y < 8; y++)
         for (int x = 0; x < 8; x++) {
            DrawCube((Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * y}, 2, 0, 2,
                     (x + y) & 1 ? BLACK : LIGHTGRAY);
            if (x == 0) {
               DrawCube((Vector3){-7.0f + 2 * (x - 1), 0, -7.0f + 2 * y}, 2, 0,
                        2, RED);
            }
            if (y == 0) {
               DrawCube((Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * (y - 1)}, 2, 0,
                        2, GREEN);
            }
         }
      EndMode3D();

      DrawRectangle(0, 0, 300, 100, Fade(BLUE, 0.8f));
      DrawText(timeText, 10, 10, 20, BLACK);
      DrawText(timeText, 10, 30, 20, BLACK);

      // DrawFPS(10, 10);
      EndDrawing();
   }
}
