#include "item_manager.hpp"

Item* ItemManager::getItemWithTags(int tag) {
	for (typename std::vector<Item*>::iterator it = ents.begin() ; it != ents.end(); ++it) {
		Item* item = *it;
		if (item->tasked == false && item->hasTags(tag) ) {
			return item;
		}
	}
	return NULL;
}