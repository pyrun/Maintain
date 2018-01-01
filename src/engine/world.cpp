#include "world.h"

#include "physic.h"

using namespace irr;

world::world() {
}

world::~world() {
    //dtor
}

void world::load( graphic *graphic) {
    irr::scene::IMesh *plane = graphic->getSceneManager()->getGeometryCreator()->createPlaneMesh( irr::core::dimension2df(20,20), irr::core::dimension2du(100,100));
    irr::scene::IMeshSceneNode *terrain = graphic->getSceneManager()->addMeshSceneNode(plane, 0, -1);

    terrain->setMaterialType(irr::video::EMT_SOLID);
    terrain->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //terrain->setScale(vector3df(40.0f));
    terrain->setPosition(vector3df(0, 0, 0));
    //terrain->setMaterialFlag(irr::video::EMF_WIREFRAME, true);


    terrain->setMaterialTexture( 0, graphic->getDriver()->getTexture( "ground/grass/diffus.tga") );

    //terrain->setMaterialType(video::EMT_DETAIL_MAP);

    physic_createTrg( terrain, true, 0);

    irr::scene::IMesh *plane2 = graphic->getSceneManager()->getMesh("trg.obj");
    irr::scene::IMeshSceneNode *terrain2 = graphic->getSceneManager()->addMeshSceneNode(plane2, 0, -1);

    terrain2->setMaterialType(irr::video::EMT_SOLID);
    terrain2->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    terrain2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    terrain2->setScale(vector3df(40.0f));
    terrain2->setPosition(vector3df(600, 100, 0));
    //terrain->setMaterialFlag(irr::video::EMF_WIREFRAME, true);


    terrain2->setMaterialTexture( 0, graphic->getDriver()->getTexture( "ground/grass/diffus.tga") );

    //terrain->setMaterialType(video::EMT_DETAIL_MAP);

    physic_createTrg( terrain2, false, 1);

    // create triangle selector for the terrain
    //scene::ITriangleSelector* selector = graphic->getSceneManager()->createTerrainTriangleSelector( l_terrain, 0);
}
