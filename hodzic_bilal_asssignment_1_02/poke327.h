typedef struct tile{
	int type;
	int xCoord;
	int yCoord;
}tile_t;
typedef struct map{
	int xCoord;
	int yCoord;
	tile_t* tiles[21][80];
}map_t;
typedef struct world{
	map_t* m[400][400];
}world_t;

tile_t* tile_init(int type, int xCoord, int yCoord);
map_t* mapInit(int x, int y);
void printMap(map_t m);
void createPath(map_t* m);
void placeMart(map_t* m);
void placeCenter(map_t* m);

