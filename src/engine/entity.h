#ifndef ENTITY_H
#define ENTITY_H

#include "../graphic/graphic.h"
#include "config.h"

#define ENTITY_DEFINITION_FILE "definition.xml" // search for this file in folders

class entity_type {
    public:
        entity_type();
        ~entity_type();

        std::string name;
        std::string file;
        void set_mesh( irr::scene::IAnimatedMesh *mesh) {
            p_mesh = mesh;
        }
        irr::scene::IAnimatedMesh *get_mesh() {
            return p_mesh;
        }
    private:
        irr::scene::IAnimatedMesh *p_mesh;
};

class entity {
    public:
        entity();
        virtual ~entity();

        int id;

        void set_mesh_node( irr::scene::IAnimatedMeshSceneNode *node) {
            p_node = node;
        }
        irr::scene::IAnimatedMeshSceneNode *get_mesh() {
            return p_node;
        }
    protected:

    private:
        irr::scene::IAnimatedMeshSceneNode *p_node;
};

class entity_handle {
    public:
        entity_handle();
        ~entity_handle();

        bool init( config *config, graphic *graphic);

        bool load( config *config, graphic *graphic);
        bool load_folder( std::string folder, config *config, graphic *graphic);
        bool load_type( config *config, std::string l_path, std::string l_name, graphic *graphic);

        entity_type *getType( std::string name);

        int createObject( graphic *graphic, std::string name);
    private:
        std::vector<entity_type> p_types;
        std::vector<entity> p_entitys;

        int p_id_counter;
};

#endif // ENTITY_H
