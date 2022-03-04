#include <raylib.h>

#include <stdlib.h>

#define SCALE 4


typedef struct {
	char * PATH;
	int ID;
	Texture2D TEXTURE;
} Tile;

int tile_counter = 0; // used to assigned tiles their ids, incremented whenever load_tile() is called

Tile tiles[128]; // total map of all tiles

// loads a tile from a png image
Tile load_tile(char * path) {
	Tile output;

	output.PATH = path;
	
	output.ID  = tile_counter;

	output.TEXTURE = LoadTexture(path);
	
	tiles[tile_counter] = output;

	// output
	tile_counter++;
	
	return output;
}

typedef struct {
	unsigned int w, h; // dimensions
	size_t size; // w * h * sizeof(Tile)
	Tile data[]; // data
} TileMap;

// creates an empty tilemap that can then have data loaded into it by load_tilemap()
TileMap mk_tilemap(unsigned int dim_x, unsigned int dim_y) {
	TileMap output;

	output.w = dim_x;
	output.h = dim_y;

	output.size = dim_x * dim_y * sizeof(Tile);

	// ?? errors for some reason idk output.data = { 0 };

	return output;
}


// loads an array of ints of size dim_x * dim_y into a tilemap
void load_tilemap(TileMap * map, unsigned int data[], unsigned int dim_x, unsigned int dim_y) {
	for(int lc = 0; lc < (dim_x * dim_y); lc++) {
		map->data[lc] = tiles[data[lc]];
	}
}

void DrawTileMap(TileMap map, const int scale, Color color, int x, int y) {
	for(int h = 0; h < map.h; h++) {
		for(int w = 0; w < map.w; w++) {
			DrawTexture(map.data[h * map.w + w].TEXTURE, x + (SCALE * w), y + (SCALE * h), color);
		}
	}
}

int main(void)
{
    const int WIDTH = 800;
    const int HEIGHT = 440;

	// used for sprite maps
	const int SCALED_WIDTH = WIDTH / SCALE;
	const int SCALED_HEIGHT = HEIGHT / SCALE;
    
	// Initialization
    InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	// Texture Loading
	const Tile FLOOR_1 = load_tile("./res/floor-tile-1.png");
	const Tile WALL_1  = load_tile("./res/wall-tile-1.png");
	
	const int DIMX = 4;
	const int DIMY = 4;

	unsigned int test_data[16] = { 1, 1, 1, 1,
				   0, 0, 0, 0,
				   0, 0, 0, 0,
				   1, 1, 1, 1  };

	TileMap map = mk_tilemap(DIMX, DIMY);
	load_tilemap(&map, test_data, DIMX, DIMY);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
			
			DrawTileMap(map, SCALE, WHITE, 0, 0);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
