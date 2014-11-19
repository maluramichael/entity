#include "entity.hpp"
#include "world.hpp"

namespace entity {

    Entity::Id EntityManager::id_counter = 0;

    Entity::Entity(Id id, World &world) : id(id), world(world) {}

    EntityManager& Entity::get_entity_manager() {
        return world.get_entity_manager();
    }

    void Entity::refresh() {
        world.refresh_entity(*this);
    }

    void Entity::remove() {
        world.remove_entity(*this);
    }

    EntityManager::EntityManager(World &world) : world(world) {}

    Entity::Id EntityManager::create_entity() {
        Entity::Id id;

        if (reusable_ids.empty()) {
            id = id_counter++;
        }
        else {
            id = reusable_ids.back();
            reusable_ids.pop_back();
        }

        if (id >= components_per_entity.size()) {
            components_per_entity.resize(id + 1);
        }

        return id;
    }

    void EntityManager::refresh_entity(Entity::Id id) {
        Entity entity(id, world);
        //world.get_system_manager().refresh_systems(entity); // TODO: call this something else?
    }

    void EntityManager::remove_entity(Entity::Id id) {
        assert(id < components_per_entity.size());
        components_per_entity[id].reset();
        // TODO: what about systems? have we forgotten something?
        reusable_ids.push_back(id);
    }

}