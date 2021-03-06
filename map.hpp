#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "tile.hpp"
#include "constants.hpp"
#include "room.hpp"
#include "entity.hpp"
#include "bounds_check.hpp"
#include "point.hpp"

class Map {
	friend class WorldGenerator;
	friend class XmlLoader;
private:
	int** tiles;
	int** colorize;	// Flag that tells if the tile is supposed to be colorized prior to rendering
	int** rooms;
	bool** tasked; // Flag that tells if the tile has an associated task
	bool** walkable;
	std::vector<Tile*> tileDict;
	std::vector<sf::Color> colorDict;
	std::vector<Room*> roomDict;
	std::vector<Material*> matDict;
	sf::RenderTexture mapTex;
	sf::Sprite mapSpr;
	bool dirty;
	Entity*** ents; 
protected:
	void addTile(Tile* tileToAdd);
	void addColor(sf::Color colorToAdd);
	void addRoom(Room* roomToAdd);
	void addMaterial(Material* matToAdd);
public:
	int width, height;

	static point TexXYToTileXY(float texX, float texY);
	static point TileXYToTexXY(int x, int y);
	
	Map();
	~Map();
	void init(int width, int height);
	void update(float dt);
	void render(sf::RenderTarget* screen);
	void reRender();
	void setTile(int x, int y, Tile* tileToAdd);
	void setTile(int x, int y, int tileToAdd);
	Tile* getTile(int x, int y);
	void setColor(int x, int y, sf::Color colorToAdd);
	void setColor(int x, int y, int colorToAdd);
	void setRoom(int x, int y, Room* roomToAdd);
	void setRoom(int x, int y, int roomToAdd);
	void setRoom(int x0, int y0, int x1, int y1, int roomToAdd);
	void setRoom(int x0, int y0, int x1, int y1, Room* roomToAdd);
	int getRoomID(Room* room);
	int getTileID(Tile* tile);
	void setTasked(int x, int y, bool tasked);
	bool getTasked(int x, int y);
	bool isWalkable(int x, int y);
	void resetWalkableStatus(int x, int y);
	void setWalkableStatus(int x, int y, bool status);
	//void moveEnt(int oldX, int oldY)
	//Entity* getEnts(int x, int y);
	Tile* getRoom(int x, int y);
	void clearColor(int x, int y);
	bool inBounds(int x, int y);
	std::vector<Tile*> getTileDict(){ return tileDict; };
};

#endif