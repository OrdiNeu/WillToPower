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

// Putting this into its own function because it's really non-intuitive
bool XmlLoader::hasTag(std::string text, std::string tag) {
    return text.find(tag) != std::string::npos;
}

int XmlLoader::parseTags(std::string tags) {
    int retVal = 0;

    if (hasTag(tags,"IS_WALKABLE")) {
        retVal |= IS_WALKABLE;
    }
    if (hasTag(tags,"IS_MINABLE")) {
        retVal |= IS_MINABLE;
    }
    if (hasTag(tags,"PATHING_BLOCK")) {
        retVal |= PATHING_BLOCK;
    }

    return retVal;
}

Doodad* XmlLoader::loadWall(boost::property_tree::ptree wall_tree, DoodadManager* doodad_manager, Material* mat_made_of) {
    std::string filename = wall_tree.get<std::string>("filename");
    std::string tags = wall_tree.get<std::string>("tags");
    std::ostringstream stream;
    stream << mat_made_of->name << "_" << mat_made_of->wallIDs.size();
    Doodad* thisWall = new Doodad(stream.str(), filename, 0, 0, parseTags(tags) | DRAW_SPECIAL);

    if (doodad_manager != NULL) {
        doodad_manager->addNewEntType(stream.str(), *thisWall);
    }

    if (mat_made_of != NULL) {
        thisWall->madeOf = mat_made_of;
    }

    return thisWall;
}

Tile* XmlLoader::loadTile(boost::property_tree::ptree tile_tree, Map* map, Material* mat_made_of) {
    std::string filename = tile_tree.get<std::string>("filename");
    std::string tags = tile_tree.get<std::string>("tags");
    Tile* thisTile = new Tile(filename, parseTags(tags));

    if (map != NULL) {
        map->addTile(thisTile);
    }

    if (mat_made_of != NULL) {
        thisTile->madeOf = mat_made_of;
    }

    return thisTile;
}

void XmlLoader::loadMaterials(DoodadManager* doodad_manager, Map* map, std::string filename) {
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(filename, tree);
    boost::property_tree::ptree mats = tree.get_child("materials");

    BOOST_FOREACH( boost::property_tree::ptree::value_type &v, mats ) {
        boost::property_tree::ptree mat_tree = v.second;
        Material* mat = new Material();
        map->addMaterial(mat);
        mat->name = mat_tree.get<std::string>("name");

        // Floor
        try {
            boost::property_tree::ptree floors = mat_tree.get_child("floor");
            /*for ( boost::property_tree::ptree::value_type &v2 : mat_tree.get_child("floor") ) {
                boost::property_tree::ptree floor_tree = v2.second;
                Tile* floorTile = loadTile(floor_tree, map, mat);
                mat->tileIDs.push_back(map->getTileID(floorTile));
            }*/
            Tile* floorTile = loadTile(floors, map, mat);
            mat->tileIDs.push_back(map->getTileID(floorTile));
        } catch (boost::property_tree::ptree_bad_path e) {
            // Do nothing
        }

        // Wall
        try {
            boost::property_tree::ptree walls = mat_tree.get_child("wall");
            /*BOOST_FOREACH( boost::property_tree::ptree::value_type v2, walls ) {
                boost::property_tree::ptree wall_tree = v2.second;
                //Doodad* wall = loadWall(wall_tree, doodad_manager, mat);
                //mat->wallIDs.push_back(wall->uid);
            }*/
            Doodad* wall = loadWall(walls, doodad_manager, mat);
            mat->wallIDs.push_back(wall->uid);
        } catch (boost::property_tree::ptree_bad_path e) {
            // Do nothing
        }
    }
}