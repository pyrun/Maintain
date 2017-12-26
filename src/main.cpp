#include <irrlicht.h>

using namespace irr;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main() {

    IrrlichtDevice *device = createDevice( video::EDT_SOFTWARE, irr::core::dimension2d<u32>(640, 480), 16, false, false, false, 0);

    if (!device)
        return 1;

    //
    irr::video::IVideoDriver* driver = device->getVideoDriver();

    // Title
    device->setWindowCaption(L"Maintain");

    while(device->run())
	{
		driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

		driver->endScene();
	}
    return 0;
}
