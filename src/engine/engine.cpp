#include "engine.h"

engine::engine() {
    // init
    p_config = new config();
    p_graphic = new graphic( p_config);
    p_entity = new entity_handle();
    p_input = new input();
    p_world = new world();
    p_physic = new physic( p_graphic);

    // start
    p_entity->load( p_config, p_graphic);

    // init the files
    p_entity->init( p_config, p_graphic);

    p_graphic->getDevice()->setEventReceiver( p_input);

    p_world->load( p_graphic, p_physic);
}

engine::~engine() {
    if( p_physic)
        delete p_physic;
    if( p_input)
        delete p_input;
    if( p_entity)
        delete p_entity;
    if( p_graphic)
        delete p_graphic;
    if( p_config)
        delete p_config;
}

int engine::run() {
    p_entity->createObject( p_graphic, p_physic, "house", vec3( 300, -800, 100) );
    //p_entity->createObject( p_graphic, p_physic, "house", vec3( 300, -800, 100) );

    //p_graphic->getCamera()->setPosition( vec3( 0, 1000, 0));

    float timeStamp = 0;

    u32 FPS_startTime = 0;
    float FPS_skipTime = 1000.0f / 120.0f;

    // main while
    while(p_graphic->getDevice()->run()) {

        timeStamp = p_graphic->getDevice()->getTimer()->getTime();

        p_physic->process( p_graphic);

        p_entity->process( );

        if ( timeStamp - FPS_startTime > FPS_skipTime){
            FPS_startTime = timeStamp;

            int fps = p_graphic->getDriver()->getFPS();
            core::stringw str = L"Irrlicht Engine - Quake 3 Map example [";
                str += p_graphic->getDriver()->getName();
                str += "] FPS:";
                str += fps;

                p_graphic->getDevice()->setWindowCaption(str.c_str());

            p_graphic->begin();

            // draw scene
            p_graphic->getSceneManager()->drawAll();

            p_graphic->end();
        }

        p_graphic->getDevice()->sleep( 1);
	}

    return 0;
}
