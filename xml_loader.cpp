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