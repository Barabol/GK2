#include "render.h"
#include "../config.h"
#include <cstdio>
#include <raylib.h>
void renderBoard(board *board) {
   InitWindow(INIT_WIN_WIDTH, INIT_WIN_HEIGHT, "projekt grafika II");
   Camera3D mainCammera = {0};
   mainCammera.position = (Vector3){0.0f, 10.0f, 10.0f};
   mainCammera.target = (Vector3){0.0f, 0.0f, 0.0f};
   mainCammera.up = (Vector3){0.0f, 1.0f, 0.0f};
   mainCammera.fovy = 45.0f;
   mainCammera.projection = CAMERA_PERSPECTIVE;
   Ray ray = {0};
   RayCollision collision = {0};
   // DisableCursor();
   SetTargetFPS(TARGET_FPS);
   char timeText[100];
   unsigned long time = 1201;
   float frameTime = 0;
   int piece[2] = {-1, -1};
   int hit[2] = {-1, -1};
   bool selected = false;
   bool notMoved = false;

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

      // collision check
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
         selected = false;
         ray = GetScreenToWorldRay(GetMousePosition(), mainCammera);
         for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
               collision = GetRayCollisionBox(
                   ray,
                   (BoundingBox){(Vector3){-8.0f + 2 * x, 1, -8.0f + 2 * y},
                                 (Vector3){-6.0f + 2 * x, 1, -6.0f + 2 * y}});
               if (collision.hit) {
                  printf("hit, %d:%d\n", x, y);
                  hit[0] = x;
                  hit[1] = y;
                  break;
               }
            }
         }
      }
      DrawGrid(16, 1.0f);
      // grid drawing
      for (int y = 0; y < 8; y++)
         for (int x = 0; x < 8; x++) {
            if (board->layout[x][y] != NULL) {
               if (x == hit[0] && y == hit[1] &&
                   board->layout[x][y]->color == board->playing) {
                  selected = true;
                  DrawCube((Vector3){-7.0f + 2 * x, 1, -7.0f + 2 * y}, 1.8, 2,
                           1.8, RED);
                  board->flag(x, y);
                  piece[0] = x;
                  piece[1] = y;
                  notMoved = true;
               } else
                  DrawCube((Vector3){-7.0f + 2 * x, 1, -7.0f + 2 * y}, 1.8, 2,
                           1.8,
                           board->layout[x][y]->color == 1 ? BLACK : LIGHTGRAY);
            }
            if (selected && board->flags[board->playing][MOVE].value(x, y) == 1)
               DrawCube((Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * y}, 2, 0, 2,
                        GREEN);
            else if (selected &&
                     board->flags[board->playing][ATTACK].value(x, y) == 1)
               DrawCube((Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * y}, 2, 0, 2,
                        RED);
            else
               DrawCube((Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * y}, 2, 0, 2,
                        (x + y) & 1 ? BLACK : LIGHTGRAY);
            if (x == 0) {
               DrawCube((Vector3){-7.0f + 2 * (x - 1), 0, -7.0f + 2 * y}, 2, 0,
                        2, RED);
            }
            if (y == 7) {
               DrawCube((Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * (y + 1)}, 2, 0,
                        2, GREEN);
            }
         }
      if (notMoved &&
          (board->flags[board->playing][MOVE] |
           board->flags[board->playing][ATTACK])
              .value(hit[0], hit[1]) &&
          board->layout[piece[0]][piece[1]] != NULL) {
         board->move(piece[0], piece[1], hit[0], hit[1]);
         notMoved = false;
      }

      EndMode3D();

      DrawRectangle(0, 0, 300, 100, Fade(BLUE, 0.8f));
      DrawText(timeText, 10, 10, 20, BLACK);
      DrawText(timeText, 10, 30, 20, BLACK);

      // DrawFPS(10, 10);
      EndDrawing();
   }
}
