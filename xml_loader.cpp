#include "xml_loader.hpp"

void XmlLoader::loadUnits(UnitManager* unit_manager, std::string filename) {
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(filename, tree);
    boost::property_tree::ptree units = tree.get_child("units");

    BOOST_FOREACH( boost::property_tree::ptree::value_type v, units ) {
    	boost::property_tree::ptree thisTree = v.second;
    	std::string id = thisTree.get<std::string>("id");
    	std::string filename = thisTree.get<std::string>("filename"); 
    	Unit testUnit = Unit(id,filename);
    	unit_manager->addNewEntType(id,testUnit);
    }
}

int XmlLoader::parseTags(std::string tags) {
    int retVal = 0;
    /* Boost::regex is bugging out on me, prolly related to my version of mingw
    boost::regex expression(
       "(IS_WALKABLE)?"
       "(IS_MINABLE)?"
       "(TILE)?"
       "(WALL)?");
    boost::match_results<std::string::const_iterator> what;

    if (regex_search(tags, what, expression)) {
        std::cout << what[0] << std::endl << what[1] << std::endl;
    };*/

    // Temp workaround for boost::regex
    if (tags == "IS_WALKABLE") {
        retVal |= IS_WALKABLE;
    }
    if (tags == "IS_MINABLE|IS_WALL") {
        retVal |= IS_MINABLE | WALL;
    }
    return retVal;
}

Tile* XmlLoader::loadTile(boost::property_tree::ptree tileTree, Map* map, Material* matMadeOf) {
    std::string filename = tileTree.get<std::string>("filename");
    std::string tags = tileTree.get<std::string>("tags");
    Tile* thisTile = new Tile(filename, parseTags(tags));

    if (map != NULL) {
        map->addTile(thisTile);
    }

    if (matMadeOf != NULL) {
        thisTile->madeOf = matMadeOf;
    }

    return thisTile;
}

void XmlLoader::loadMaterials(Map* map, std::string filename) {
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(filename, tree);
    boost::property_tree::ptree mats = tree.get_child("materials");

    BOOST_FOREACH( boost::property_tree::ptree::value_type v, mats ) {
        boost::property_tree::ptree thisTree = v.second;
        Material* mat = new Material();
        map->addMaterial(mat);

        // Floor
        Tile* floorTile = loadTile(thisTree.get_child("floor"), map, mat);
        mat->tileID = map->getTileID(floorTile);

        // Wall
        try {
            Tile* wallTile = loadTile(thisTree.get_child("wall"), map, mat);
            mat->wallID = map->getTileID(wallTile);
        } catch (boost::property_tree::ptree_bad_path e) {
            // Do nothing
        }
    }
}