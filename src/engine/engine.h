#ifndef ENGINE_H
#define ENGINE_H

#include "config.h"
#include "../graphic/graphic.h"
#include "entity.h"
#include "input.h"
#include "world.h"
#include "physic.h"

class engine {
    public:
        engine();
        virtual ~engine();

        int run();
    protected:

    private:
        graphic *p_graphic;
        config *p_config;
        entity_handle *p_entity;
        input *p_input;
        world *p_world;
        physic *p_physic;
};

#endif // ENGINE_H
