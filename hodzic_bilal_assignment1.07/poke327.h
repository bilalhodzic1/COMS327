typedef struct map_tile{
	int tileType;
	int speed;
}map_tile_t;
typedef struct map{
	map_tile_t tiles[21][80];
	int up_exit;
	int down_exit;
	int left_exit;
	int right_exit;
	int xCoord;
	int yCoord;
}map_t;
typedef struct world{
	map maps[400][400];
}world_t;
void initialize_map(map_t *ma);
void initialize_world(world_t *w);
void tile_init(map_tile_t *t, int type);
void print_map(map_t *ma);

