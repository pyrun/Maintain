#include "physic.h"

physic::physic( graphic *graphic, float skiptime) {
    p_world = new q3Scene( skiptime );
    p_timer.start( graphic);

    p_last_time = 0;

    p_fps_skipTime = skiptime;

    //p_world->SetGravity( q3Vec3( 0, -9.8, 0) );
}

physic::~physic() {
}


void physic::process( graphic *graphic) {
    float l_current = p_timer.getTicks( graphic);

    if ( l_current - p_last_time > p_fps_skipTime) {
        p_last_time = l_current;

        float l_delta_time = l_current - p_last_time;

        p_world->Step();
    }
}
