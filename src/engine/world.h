#ifndef WORLD_H
#define WORLD_H

#include "../graphic/graphic.h"

class world {
    public:
        world();
        virtual ~world();

        void load( graphic *graphic );
    protected:

    private:
//        scene::ISceneNode* l_terrain;
};

#endif // WORLD_H
