#ifndef ENTITY_H
#define ENTITY_H

#include "../graphic/graphic.h"
#include "config.h"
#include "helper.h"
#include "physic.h"

#define ENTITY_DEFINITION_FILE "definition.xml" // search for this file in folders

class entity_type {
    public:
        entity_type();
        ~entity_type();

        std::string name;
        std::string file;
        void setMesh( irr::scene::IAnimatedMesh *mesh) { p_mesh = mesh; }
        irr::scene::IAnimatedMesh *getMesh() { return p_mesh; }
    private:
        irr::scene::IAnimatedMesh *p_mesh;
};

class entity {
    public:
        entity();
        virtual ~entity();

        int id;

        void init( graphic *graphic, physic *physic, irr::scene::IAnimatedMesh *mesh);

        // physic collision
        q3Body* getBody() { return p_body; }

        // mesh node
        void setMeshNode( irr::scene::IAnimatedMeshSceneNode *node) { p_node = node; }
        irr::scene::IAnimatedMeshSceneNode *getMeshNode() { return p_node; }

        // position
        void setPosition( irr::core::vector3df position) { p_node->setPosition( position); }
        irr::core::vector3df getPosition() { return p_node->getPosition(); }
    protected:

    private:
        irr::scene::IAnimatedMeshSceneNode *p_node;
        q3Body* p_body;
};

class entity_handle {
    public:
        entity_handle();
        ~entity_handle();

        bool init( config *config, graphic *graphic);

        void process();

        bool load( config *config, graphic *graphic);
        bool loadFolder( std::string folder, config *config, graphic *graphic);
        bool loadType( config *config, std::string l_path, std::string l_name, graphic *graphic);

        entity_type *getType( std::string name);

        int createObject( graphic *graphic, physic *physic, std::string name, vec3 position);
    private:
        std::vector<entity_type*> p_types;
        std::vector<entity*> p_entitys;

        int p_id_counter;
};

#endif // ENTITY_H
