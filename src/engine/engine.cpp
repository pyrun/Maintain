#include "engine.h"

engine::engine() {
    // init
    p_config = new config();
    p_graphic = new graphic( p_config);
    physic_init();
    p_entity = new entity_handle();
    p_input = new input();
    p_world = new world();

    // start
    p_entity->load( p_config, p_graphic);

    // init the files
    p_entity->init( p_config, p_graphic);

    p_graphic->getDevice()->setEventReceiver( p_input);

    p_world->load( p_graphic);

    physic_createPlayer( p_graphic->getSceneManager(), vector3df(60, 500, 60));
}

engine::~engine() {
    physic_deleteWorld();
    if( p_input)
        delete p_input;
    if( p_entity)
        delete p_entity;
    if( p_graphic)
        delete p_graphic;
    if( p_config)
        delete p_config;
}

#include <windows.h>

int engine::run() {
    //p_entity->createObject( p_graphic, "house", vec3( 100, 100, 100) );

    //p_graphic->getCamera()->setPosition( vec3( 0, 1000, 0));


    int deltaTime = 0;
    int timeStamp = 0;

    u32 FPS_startTime = 0;
    u32 FPS_skipTime = 1000 / 60;

    // main while
    while(p_graphic->getDevice()->run()) {
        // Work out a frame delta time.
        deltaTime = p_graphic->getDevice()->getTimer()->getTime() - timeStamp;
        timeStamp = p_graphic->getDevice()->getTimer()->getTime();

        physic_updateWorld( 0.5f*deltaTime);
        physic_controlPlayer();

        if ( timeStamp - FPS_startTime > FPS_skipTime){
            FPS_startTime = timeStamp;
            p_graphic->begin();

            // draw scene
            p_graphic->getSceneManager()->drawAll();

            p_graphic->end();
        }
	}

	p_graphic->getDevice()->drop();

    return 0;
}
