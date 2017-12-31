#include "engine.h"

engine::engine() {
    // init
    p_config = new config();
    p_graphic = new graphic( p_config);
    p_entity = new entity_handle();
    p_input = new input();
    p_world = new world();


    // start
    p_entity->load( p_config, p_graphic);

    // init the files
    p_entity->init( p_config, p_graphic);

    p_graphic->getDevice()->setEventReceiver( p_input);

    p_world->load( p_graphic);
}

engine::~engine() {
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

    p_graphic->getCamera()->setPosition( vec3( 0, 1000, 0));

    const f32 MOVEMENT_SPEED = 5.f;

    u32 then = p_graphic->getDevice()->getTimer()->getTime();
    // main while
    while(p_graphic->getDevice()->run()) {
        // Work out a frame delta time.
        const u32 now = p_graphic->getDevice()->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        /*core::vector3df nodePosition = node->getPosition();

        if( p_input->isKeyDown(irr::KEY_KEY_W))
            nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
        else if( p_input->isKeyDown(irr::KEY_KEY_S))
            nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

        if( p_input->isKeyDown(irr::KEY_KEY_A))
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
        else if( p_input->isKeyDown(irr::KEY_KEY_D))
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

        node->setPosition(nodePosition);*/

        p_graphic->begin();

        // draw scene
        p_graphic->getSceneManager()->drawAll();

		p_graphic->end();
	}

	p_graphic->getDevice()->drop();

    return 0;
}
