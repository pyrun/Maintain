#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <irrlicht.h>

#include "../engine/config.h"

class graphic {
    public:
        graphic( config *config);
        virtual ~graphic();

        irr::video::IVideoDriver *getDriver() { return p_driver; }
        irr::IrrlichtDevice *getDevice() { return p_device; }

        void begin();
        void end();
    protected:

    private:
        irr::video::IVideoDriver *p_driver;
        irr::IrrlichtDevice *p_device;

};

#endif // GRAPHIC_H