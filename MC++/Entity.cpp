#include "Entity.h"
#include <vector>

using namespace std;

static vector<Entity*> entities;

Entity::Entity() {

	entities.push_back(this);

}

Entity* Entity::getEntity(int index) {

	if (index < 0 || index >= getEntityCount()) {
		return nullptr;
	}

	return entities.at(index);

}

int Entity::getEntityCount() {

	return entities.size();

}

void Entity::clearEntities() {

	for (unsigned int i = 0; i < entities.size(); i++) {
		delete entities.at(i);
	}

	entities.clear();

}

void Entity::destroy() {

	for (unsigned int i = 0; i < entities.size(); i++) {
		if (entities.at(i) == this) {
			entities.erase(entities.begin() + i);
			break;
		}
	}

	delete this;

}