#include "graphic.h"

#include "..\engine\helper.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

graphic::graphic( config *config) {
    irr::SIrrlichtCreationParameters l_params;

    // set diver type
    l_params.DriverType = irr::video::EDT_OPENGL;
    l_params.WindowSize = irr::core::dimension2d<irr::u32>( atoi(config->get( "width", "graphic", "640").c_str()), atoi( config->get( "heigh", "graphic", "400").c_str()));
    l_params.Fullscreen = string_bool( config->get( "fullscreen", "graphic", "false") );
    l_params.Vsync = string_bool( config->get( "vsync", "graphic", "true") );
    l_params.ZBufferBits = 16;
    l_params.Bits = false;
    l_params.WithAlphaChannel = string_bool( config->get( "withalphachannel", "graphic", "false") );

    // create device ex
    p_device = irr::createDeviceEx( l_params);
    if (!p_device) {
        printf( "failed to launch the IrrlichtDevice\n");
    }

    // set device
    // L for wide character ( very long CHAR*)
    p_device->setWindowCaption( L"Maintain"); // Title

    // get scene
    p_scene = p_device->getSceneManager();

    p_driver = p_device->getVideoDriver();

    p_collisionManager = p_scene->getSceneCollisionManager();

    //p_camera = p_scene->addCameraSceneNodeFPS( 0, 100.0f, 0.5f, -1, 0, 0, true, 30.f, false, true);
    //p_camera->setFarValue( atoi(config->get( "view", "graphic", "9000").c_str()));
}

graphic::~graphic() {
    p_device->drop();
}

void graphic::begin() {
    p_driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
}

void graphic::end() {
    p_driver->endScene();
}
