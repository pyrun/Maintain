#ifndef ENGINE_H
#define ENGINE_H

#include "config.h"
#include "../graphic/graphic.h"
#include "entity.h"

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
};

#endif // ENGINE_H
