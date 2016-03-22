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

    if (tags.find("IS_WALKABLE") != std::string::npos) {
        retVal |= IS_WALKABLE;
    }
    if (tags.find("IS_MINABLE") != std::string::npos) {
        retVal |= IS_MINABLE;
    }
    if (tags.find("IS_WALL") != std::string::npos) {
        retVal |= WALL;
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