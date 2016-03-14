#ifndef XML_LOADER_HPP
#define XML_LOADER_HPP

#include <cstring>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "map.hpp"
#include "entity_manager.hpp"
#include "unit_manager.hpp"
#include "unit.hpp"

class XmlLoader {
public:
	static void loadUnits(UnitManager* unit_manager, std::string filename);
};

#endif 