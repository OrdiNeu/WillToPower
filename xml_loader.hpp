#ifndef XML_LOADER_HPP
#define XML_LOADER_HPP

#include <cstring>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
//#include <boost/regex.hpp>
#include "map.hpp"
#include "entity_manager.hpp"
#include "unit_manager.hpp"
#include "unit.hpp"

class XmlLoader {
private:
	static Tile* loadTile(boost::property_tree::ptree tile_tree, Map* map = NULL, Material* mat_made_of = NULL);
	static Doodad* loadWall(boost::property_tree::ptree wall_tree, DoodadManager* doodad_manager, Material* mat_made_of = NULL);
	static bool hasTag(std::string text, std::string tag);
	static int parseTags(std::string tags);
public:
	static void loadUnits(UnitManager* unit_manager, std::string filename);
	static void loadMaterials(DoodadManager* doodad_manager, Map* map, std::string filename);
};

#endif 