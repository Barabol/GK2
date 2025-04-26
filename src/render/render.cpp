#include "render.h"
#include "../config.h"
#include <cstdio>
#include <raylib.h>
#include <raymath.h>
void renderBoard(board *board, Conn *con) {
   static const char *names[2] = {"White", "Black"};
   InitWindow(INIT_WIN_WIDTH, INIT_WIN_HEIGHT, WINDOW_NAME);
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
   unsigned long time[2] = {PLAYER_TIME, PLAYER_TIME};
   float frameTime = 0;
   int piece[2] = {-1, -1};
   int hit[2] = {-1, -1};
   bool selected = false;
   bool notMoved = false;
   bool handled = true;
   bool notVin = true;
   Image background = LoadImage("src/img/background.jpg");
   ImageResize(&background, INIT_WIN_WIDTH, INIT_WIN_HEIGHT);
   Texture2D texture = LoadTextureFromImage(background);
   int selfColor = con->flags & IS_SERVER ? 0 : 1;
   BMatrix moves;
   Model piecesObj[6] = {LoadModel("src/pieces/pionek.obj"),
                         LoadModel("src/pieces/konik.obj"),
                         LoadModel("src/pieces/ksiadz.obj"),
                         LoadModel("src/pieces/wieza.obj"),
                         LoadModel("src/pieces/szpetna_krolowa.obj"),
                         LoadModel("src/pieces/szpetny_krol.obj")};
   Texture2D pieceTx[6][2] = {
       {LoadTexture("src/pieces/pionek_bialy.png"),
        LoadTexture("src/pieces/pionek_czarny.png")},

       {LoadTexture("src/pieces/konik_bialy.png"),
        LoadTexture("src/pieces/konik_czarny.png")},

       {LoadTexture("src/pieces/ksiadz_bialy.png"),
        LoadTexture("src/pieces/ksiadz_czarny.png")},

       {LoadTexture("src/pieces/wieza_biala.png"),
        LoadTexture("src/pieces/wieza_czarna.png")},

       {LoadTexture("src/pieces/szpetna_krolowa_biala.png"),
        LoadTexture("src/pieces/szpetna_krolowa_czarna.png")},

       {LoadTexture("src/pieces/szpetny_krol_bialy.png"),
        LoadTexture("src/pieces/szpetny_krol_czarny.png")}};
   float knightRotation = 1.57079633f;
   while (!WindowShouldClose()) {
      if (notVin) {
         if (con->flags & CONNECTED)
            frameTime += GetFrameTime();
         if (frameTime >= 1) {
            frameTime -= 1;
            time[board->playing] -= 1;
				if(time[board->playing] == 0)
					notVin = false;
         } 
      }
      UpdateCamera(&mainCammera, CAMERA_FREE);
      BeginDrawing();
      ClearBackground(WHITE);
      DrawTexture(texture, INIT_WIN_WIDTH / 2 - texture.width / 2,
                  INIT_WIN_HEIGHT / 2 - texture.height / 2, WHITE);
      DrawRectangleLines(0, 0, INIT_WIN_WIDTH / 2 - texture.width / 2,
                         INIT_WIN_HEIGHT / 2 - texture.height / 2, WHITE);

      BeginMode3D(mainCammera);

      // collision check
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
         selfColor = con->flags & IS_SERVER ? 0 : 1;
         if (board->playing == selfColor && con->flags & CONNECTED && notVin) {
            handled = false;
            selected = false;
            ray = GetScreenToWorldRay(GetMousePosition(), mainCammera);
            printf("gg: %d\n", board->playing == selfColor);
            for (int x = 0; x < 8; x++) {
               for (int y = 0; y < 8; y++) {
                  collision = GetRayCollisionBox(
                      ray, (BoundingBox){
                               (Vector3){-8.0f + 2 * x, 1, -8.0f + 2 * y},
                               (Vector3){-6.0f + 2 * x, 1, -6.0f + 2 * y}});
                  if (collision.hit) {
                     printf("hit, %d:%d\n", x, y);
                     hit[0] = x;
                     hit[1] = y;
                     con->packet.content.x = x;
                     con->packet.content.y = y;
                     conSend(con);
                     break;
                  }
               }
            }
         }
      }
      if (con->flags & RECIVED) {
         handled = false;
         selected = false;
         conDropFlag(con, RECIVED);
         hit[0] = con->recived.x;
         hit[1] = con->recived.y;
         selfColor = con->flags & IS_SERVER ? 1 : 0;
      }
      DrawGrid(16, 1.0f);
      // grid drawing
      for (int y = 0; y < 8; y++)
         for (int x = 0; x < 8; x++) {
            if (board->layout[x][y] != NULL) {
               if (x == hit[0] && y == hit[1] &&
                   board->layout[x][y]->color == board->playing) {
                  selected = true;
                  if (board->layout[x][y]->typ == 1) {
                     piecesObj[1].transform = MatrixRotateXYZ(
                         (Vector3){0,
                                   board->layout[x][y]->color ? -knightRotation
                                                              : knightRotation,
                                   0});
                  }
                  piecesObj[board->layout[x][y]->typ]
                      .materials[0]
                      .maps[MATERIAL_MAP_DIFFUSE]
                      .texture = pieceTx[board->layout[x][y]->typ]
                                        [board->layout[x][y]->color];
                  DrawModel(piecesObj[board->layout[x][y]->typ],
                            (Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * y}, 8.0f,
                            RED);
                  if (!handled) {
                     board->clearAllFlags();
                     if (board->layout[x][y]->typ == KING)
                        board->kinglogic(x, y);
                     else {
                        board->flag(x, y);
                     }
                     moves.setto(0);
                     moves |= board->flags[board->playing][ATTACK];
                     moves |= board->flags[board->playing][MOVE];
                     if (board->szach[board->playing] &&
                         board->layout[x][y]->typ != KING)
                        moves &= board->kingFlagging(board->playing);
                     piece[0] = x;
                     piece[1] = y;
                     notMoved = true;
                     handled = true;
                  }
               } else {
                  piecesObj[board->layout[x][y]->typ]
                      .materials[0]
                      .maps[MATERIAL_MAP_DIFFUSE]
                      .texture = pieceTx[board->layout[x][y]->typ]
                                        [board->layout[x][y]->color];
                  if (board->layout[x][y]->typ == 1) {
                     piecesObj[1].transform = MatrixRotateXYZ(
                         (Vector3){0,
                                   board->layout[x][y]->color ? -knightRotation
                                                              : knightRotation,
                                   0});
                  }
                  DrawModel(piecesObj[board->layout[x][y]->typ],
                            (Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * y}, 8.0f,
                            WHITE);
               }
            }
            if (selected &&
                (board->flags[board->playing][MOVE] & moves).value(x, y) == 1)
               DrawCube((Vector3){-7.0f + 2 * x, 0, -7.0f + 2 * y}, 2, 0, 2,
                        GREEN);
            else if (selected && (board->flags[board->playing][ATTACK] & moves)
                                         .value(x, y) == 1)
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
      if (notMoved && moves.value(hit[0], hit[1]) &&
          board->layout[piece[0]][piece[1]] != NULL &&
          board->playing == selfColor) {
         if (board->layout[piece[0]][piece[1]]->typ == KING) {
            board->kings[board->playing][0] = hit[0];
            board->kings[board->playing][1] = hit[1];
         }
         if (board->move(piece[0], piece[1], hit[0], hit[1]).szach ==
             SZACH_MAT) {
            notVin = false;
         }
         notMoved = false;
      }

      EndMode3D();
      selfColor = con->flags & IS_SERVER ? 0 : 1;

      DrawRectangle(0, 0, 170, 80, Fade(BLUE, 0.8f));

      sprintf(timeText, "%s time: %lu:%lu", names[selfColor],
              time[selfColor] / 60, time[selfColor] % 60);
      DrawText(timeText, 10, 10, 20, BLACK);

      sprintf(timeText, "Playing %s", names[selfColor]);
      DrawText(timeText, 10, 50, 20, BLACK);

      selfColor ^= 1;

      sprintf(timeText, "%s time: %lu:%lu", names[selfColor],
              time[selfColor] / 60, time[selfColor] % 60);
      DrawText(timeText, 10, 30, 20, BLACK);
      if (!notVin) {
         sprintf(timeText, "       %s won", names[board->playing ^ 1]);
         DrawRectangle(240, 290, 530, 40, Fade(BLUE, 0.8f));
         DrawText(timeText, 265, 290, 40, BLACK);
      } else if (!(con->flags & CONNECTED)) {
         DrawRectangle(240, 290, 530, 40, Fade(BLUE, 0.8f));
         if (con->flags & CON_CLOASED)
            DrawText("Player #2 quit the game", 265, 290, 40, BLACK);
         else
            DrawText("Player #2 not connected", 250, 290, 40, BLACK);
      }
      DrawFPS(INIT_WIN_WIDTH - 90, 10);
      EndDrawing();
   }
   for (int x = 0; x < 6; x++) {
      UnloadModel(piecesObj[x]);
      UnloadTexture(pieceTx[x][0]);
      UnloadTexture(pieceTx[x][1]);
   }
   UnloadTexture(texture);
   UnloadImage(background);
}
