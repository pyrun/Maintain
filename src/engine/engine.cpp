#include "engine.h"

engine::engine() {

    p_config = new config();

    p_graphic = new graphic( p_config);
}

engine::~engine() {
    if( p_graphic)
        delete p_graphic;
    if( p_config)
        delete p_config;
}

int engine::run() {

    // main while
    while(p_graphic->getDevice()->run()) {
        p_graphic->begin();



		p_graphic->end();
	}

    return 0;
}
