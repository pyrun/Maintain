#ifndef WORLD_H
#define WORLD_H

#include "../graphic/graphic.h"
#include "physic.h"

class world {
    public:
        world();
        virtual ~world();

        void load( graphic *graphic , physic *physic);
    protected:

    private:
//        scene::ISceneNode* l_terrain;
};

#endif // WORLD_H
