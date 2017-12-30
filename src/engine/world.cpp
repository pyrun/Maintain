#include "world.h"

using namespace irr;

world::world() {
}

world::~world() {
    //dtor
}

void world::load( graphic *graphic) {

    float l_width = 40.f;
    float l_length = 40.f;
    float l_height = 10.f;

    // add terrain scene node
    scene::ITerrainSceneNode* l_terrain = graphic->getSceneManager()->addTerrainSceneNode(
        "heightmap.jpg",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(0.f, 0.f, 0.f),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df( l_width, l_height, l_length),  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,     // patchSize
        4                   // smoothFactor
        );

    l_terrain->setMaterialFlag(video::EMF_LIGHTING, false);

    l_terrain->setMaterialTexture(0, graphic->getDriver()->getTexture("ground/grass/diffus.tga"));
    l_terrain->setMaterialTexture(1, graphic->getDriver()->getTexture("ground/earth/diffus.tga"));

    l_terrain->setMaterialType(video::EMT_DETAIL_MAP);

    l_terrain->scaleTexture( l_width, l_length);

    // create triangle selector for the terrain
    scene::ITriangleSelector* selector = graphic->getSceneManager()->createTerrainTriangleSelector( l_terrain, 0);
    l_terrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera
    scene::ISceneNodeAnimator* anim = graphic->getSceneManager()->createCollisionResponseAnimator(
        selector, graphic->getCamera(), core::vector3df(60,100,60),
        core::vector3df(0,0,0),
        core::vector3df(0,50,0));

    graphic->getCamera()->addAnimator( anim);

    selector->drop();
}