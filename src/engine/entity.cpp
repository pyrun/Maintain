#include "entity.h"
#include <dirent.h>

#include "../xml/tinyxml2.h"

using namespace tinyxml2;

entity_type::entity_type() {
    //ctor
}

entity_type::~entity_type() {
    //dtor
}

entity::entity() {
    //ctor
}

entity::~entity() {
    //dtor
}

entity_handle::entity_handle() {
    // set dafult value
    p_id_counter = 0;
}

entity_handle::~entity_handle() {
    //dtor
}

bool entity_handle::init( config *config, graphic *graphic) {
    //load the mesh
    for( int i = 0; i < (int)p_types.size(); i++) {
        entity_type *l_type = &p_types[ i];

        // load mesh
        l_type->setMesh( graphic->getSceneManager()->getMesh( l_type->file.c_str()));
    }
}

bool entity_handle::load( config *config, graphic *graphic) {
    std::string l_path = config->get( "folder", "objects", "objects/");

    loadFolder( l_path, config, graphic);

    return true;
}

bool entity_handle::loadFolder( std::string folder, config *config, graphic *graphic) {
    DIR *l_dir;

    struct dirent *l_entry;

    // open dir
    l_dir = opendir(folder.c_str());
    if ( l_dir == NULL)  // error opening the directory?
        return false;

    // open ech folder
    while ((l_entry = readdir(l_dir)) != NULL) {
        std::string l_file = folder + l_entry->d_name + "/";

        // dont go back folder
        if( l_entry->d_name[0] == '.')
            continue;

        // load type
        if( loadType( config, folder, l_entry->d_name, graphic) == false)
            loadFolder( l_file, config, graphic);
    }
    closedir(l_dir);

    return true;
}

bool entity_handle::loadType( config *config, std::string l_path, std::string l_name, graphic *graphic) {
    XMLDocument l_file;

    l_path = l_path + l_name + "/";

    std::string l_pathfile = l_path + (char*)ENTITY_DEFINITION_FILE;

    // if file dont exist - dont load
    if( file_exist( l_pathfile) == false) {
        return false;
    }

    // load the file
    XMLError l_result = l_file.LoadFile( l_pathfile.c_str());

    // print that one atleast found

    // check the file
    //XMLCheckResult(l_result);

    // read xml element
    XMLElement* l_object = l_file.FirstChildElement( "object" );
    if( !l_object )
        return false;

    // attribute
    std::string l_type_file = l_object->Attribute( "file");

    // create node
    entity_type l_type;
    l_type.name = l_name;
    l_type.file = l_path + l_type_file;
    p_types.push_back( l_type);

    printf( "entity_handle::load_type load type \"%s\" \n", l_name.c_str());

    return true;
}

entity_type *entity_handle::getType( std::string name) {
    for( int i = 0; i < (int)p_types.size(); i++)
        if( p_types[i].name == name)
            return &p_types[i];
    return NULL;
}

int entity_handle::createObject( graphic *graphic, std::string name, vec3 position) {
    entity_type *l_type;

    l_type = getType( name);

    if( l_type == NULL)
        return -1;

    entity l_obj;

    l_obj.id = p_id_counter;
    // incress
    p_id_counter++;

    // create scene mng
    l_obj.setMeshnode( graphic->getSceneManager()->addAnimatedMeshSceneNode( l_type->getMesh()));

    // set matrial flag
    l_obj.getMesh()->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    // position
    l_obj.setPosition( position );

    p_entitys.push_back( l_obj);

    return p_id_counter-1;
}
