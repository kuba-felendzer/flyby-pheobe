#include <raylib.h>

typedef struct {
	char * PATH;
	int ID;
	Texture2D TEXTURE;
} Tile;

int tile_counter = 0x64; // used to assigned tiles their ids, incremented whenever load_tile() is called

// loads a tile from a png image
Tile load_tile(char * path) {
	Tile output;

	output.PATH = path;
	
	output.ID   = tile_counter;
	tile_counter++;

	output.TEXTURE = LoadTexture(path);

	return output;
}

int main(void)
{
    const int WIDTH = 800;
    const int HEIGHT = 450;

    // Initialization
    InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	// Texture Loading
	const Tile FLOOR_1 = load_tile("./res/floor-tile-1.png");


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
			
			DrawTexture(FLOOR_1.TEXTURE, WIDTH / 2 - 4, HEIGHT / 2 - 4, WHITE);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
