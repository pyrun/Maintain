#ifndef ENGINE_H
#define ENGINE_H

#include "config.h"
#include "../graphic/graphic.h"

class engine {
    public:
        engine();
        virtual ~engine();

        int run();
    protected:

    private:
        graphic *p_graphic;
        config *p_config;
};

#endif // ENGINE_H
