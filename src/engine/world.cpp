#include "world.h"

#include "helper.h"

using namespace irr;

world::world() {
}

world::~world() {
    //dtor
}

void world::load( graphic *graphic, physic *physic) {

    // load model
    // create scene node with model
    // create triagle selector of this scene node with the method described above
    // add collision response animator to your camera

    /// load model
    /// create scene node with model
    irr::scene::IMesh *l_mesh = graphic->getSceneManager()->getGeometryCreator()->createPlaneMesh( irr::core::dimension2df(20,20), irr::core::dimension2du(100,100));
    irr::scene::IMeshSceneNode *l_nodeMesh = graphic->getSceneManager()->addMeshSceneNode( l_mesh, 0, -1);

    l_nodeMesh->setMaterialType(irr::video::EMT_SOLID);
    l_nodeMesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    l_nodeMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //l_nodeMesh->setScale(vector3df(40.0f));
    l_nodeMesh->setPosition(vec3(0, -1000, 0));
    //l_nodeMesh->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    l_nodeMesh->setMaterialTexture( 0, graphic->getDriver()->getTexture( "ground/grass/diffus.tga") );


    // Create the floor
		q3BodyDef bodyDef;
		//bodyDef.axis.Set( q3RandomFloat( -1.0f, 1.0f ), q3RandomFloat( -1.0f, 1.0f ), q3RandomFloat( -1.0f, 1.0f ) );
		//bodyDef.angle = q3PI * q3RandomFloat( -1.0f, 1.0f );
		bodyDef.position.Set( 0.0f, -1000, 0.0f );
		q3Body* body = physic->getWorld()->CreateBody( bodyDef );

		q3BoxDef boxDef;
		boxDef.SetRestitution( 0 );
		q3Transform tx;
		q3Identity( tx );
		boxDef.Set( tx, q3Vec3( 1000.0f, 10.0f, 1000.0f ) );
		body->AddBox( boxDef );
}
