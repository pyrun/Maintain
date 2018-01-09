#ifndef PHYSIC_H
#define PHYSIC_H

#include "q3.h"
#include "../graphic/graphic.h"
#include "timer.h"

class physic
{
    public:
        physic( graphic *graphic, float skiptime = 1.f / 60.f);
        virtual ~physic();

        void process( graphic *graphic);
        q3Scene *getWorld() { return p_world; }
    protected:

    private:
        q3Scene *p_world;
        timer p_timer;
        float p_fps_skipTime;
        float p_last_time;

        q3Body* body;
};

#endif // PHYSIC_H
