#include "raylib.h"
#include <iostream>
#include <cmath>

//Defining the map size
const int MAP_WIDTH = 31;
const int MAP_HEIGHT = 31;

//Defining tile sizes
const int TILE_SIZE = 20;
const int WALL_SIZE = 10;

bool path_clear = true;

// Define tile types
enum Tile { WALL = 1, PATH, DOT, GATE, PELLET, TELEPORT };

//Map Design
int map[MAP_WIDTH][MAP_HEIGHT] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
{1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 0, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1},
{1, 5, 1, 0, 0, 1, 3, 1, 0, 0, 0, 0, 1, 3, 1, 0, 1, 3, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 1, 5, 1},
{1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1},
{1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
{1, 3, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 3, 1},
{1, 3, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 3, 1},
{1, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 1, 0, 1, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 1},
{1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 0, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1, 3, 1, 1, 3, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 3, 1, 1, 3, 1, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1},
{6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6},
{1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1},
{1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
{1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 0, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1},
{1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1},
{1, 5, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 5, 1},
{1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1},
{1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1},
{1, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 1, 0, 1, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 1},
{1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 0, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1},
{1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1},
{1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


// Define player position
Vector2 playerPos = { 295, 452 };
int score = 0;
bool power_pellet = false;

// Define movement speed
float playerSpeed = 2.0f;

// Function to draw the map
void DrawMap() {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (map[y][x] == WALL) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, WALL_SIZE, WALL_SIZE, BLUE); // Draw wall in blue
            }
            else if (map[y][x] == PATH) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK); // Draw empty path in black
            }
            else if (map[y][x] == DOT) {
                DrawCircle(x * TILE_SIZE + TILE_SIZE / 2 - 4, y * TILE_SIZE + TILE_SIZE / 2 -4, TILE_SIZE / 6, YELLOW); // Draw dots in yellow
            }
            else if (map[y][x] == GATE) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, WALL_SIZE, WALL_SIZE, WHITE); // Draw Gate in White
            }
            else if (map[y][x] == PELLET) {
                DrawCircle((x * TILE_SIZE) + TILE_SIZE / 2 -4, (y * TILE_SIZE) + TILE_SIZE / 2 -4, TILE_SIZE / 4, WHITE);//DRAW Power pellet
            }
            else if (map[y][x] == GATE) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK); // Draw empty path in black
            }
        }
    }
}

//Function to check for obstructions, pellets and ghosts
class CheckSurroundings {
public:
    //checkingforwalls
    bool WallDetected(int newx, int newy) {
        double division = static_cast<double>(newx) / 20 ; 
        int mapx = round(division);
        double divisiony = static_cast<double>(newy) / 20;
        int mapy = round(divisiony);
        if (map[mapy][mapx] == WALL) { //DOES NOT WORK
            return true;
        };
        if (map[mapy][mapx] == DOT){
            score += 1;
            map[mapy][mapx] = PATH;
        };
        if (map[mapy][mapx] == PELLET) {
            power_pellet = true;
            map[mapy][mapx] = PATH;
        };
        if (map[mapy][mapx] == GATE) {//DOES NOT WORK EITHER
            newx = 20;
        };
        return false;
    }
};

CheckSurroundings checker;

// Function to handle player movement
void UpdatePlayer() {
    if (IsKeyDown(KEY_RIGHT)) {
        int updatex = playerPos.x + playerSpeed;
        int newx = updatex + 17;
        int newy = playerPos.y + 15;
        if (!checker.WallDetected(newx, newy)) {
            playerPos.x = updatex;
        };

        
    }
    if (IsKeyDown(KEY_LEFT)){
        int newx = playerPos.x - playerSpeed;
        int newy = playerPos.y + 10;
        if (!checker.WallDetected(newx, newy)) {
            playerPos.x = newx;
        };
    }
    if (IsKeyDown(KEY_UP)) {
        int newx = playerPos.x + 10;
        int newy = playerPos.y - playerSpeed;
        if (!checker.WallDetected(newx, newy)) {
            playerPos.y = newy;
        };
    }
    if (IsKeyDown(KEY_DOWN)) {
        int newx = playerPos.x + 15;
        int updatey = playerPos.y + playerSpeed + 20;
        int newy = updatey - 20;
        if (!checker.WallDetected(newx, updatey)) {
            playerPos.y = newy;
        };
    }
}

// Main function
int main() {
    // Initialize the window
    InitWindow(620, 620, "Pac-Man Style Map");

    // Set the target FPS
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update the player position based on input
        UpdatePlayer();

        // Start drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the map
        DrawMap();

        // Draw the player (a simple rectangle for now)
        DrawRectangleV(playerPos, { 27, 27 }, YELLOW);

        // End drawing
        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}

//ideas: run separate check function for if anything comes into the radius of the pacman to check fo rwalls, ghosts and orbs