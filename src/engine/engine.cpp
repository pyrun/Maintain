#include "engine.h"

engine::engine() {
    // init
    p_config = new config();

    p_graphic = new graphic( p_config);

    p_entity = new entity_handle();

    // start
    p_entity->load( p_config, p_graphic);

    // init the files
    p_entity->init( p_config, p_graphic);
}

engine::~engine() {
    if( p_entity)
        delete p_entity;
    if( p_graphic)
        delete p_graphic;
    if( p_config)
        delete p_config;
}

int engine::run() {

    p_graphic->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(200,-200,-1000), irr::core::vector3df(0,5,0));

    printf("%d\n", p_entity->createObject( p_graphic, "house"));

    // main while
    while(p_graphic->getDevice()->run()) {
        p_graphic->begin();

        // draw scene
        p_graphic->getSceneManager()->drawAll();

		p_graphic->end();
	}

    return 0;
}
