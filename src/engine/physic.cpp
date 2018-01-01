#include "physic.h"

dWorldID physic_world;
dSpaceID physic_space;
dJointGroupID physic_contactGroup;
vector3df physic_rotation;
physic_structObject physic_sObject;
vector<physic_structObject> physic_vObject;
vector<physic_structObject>::iterator physic_vObjectIter;
physic_structPlayer physic_sPlayer;

void physic_init() {
    dInitODE();
    physic_world = dWorldCreate();
    dWorldSetGravity(physic_world, 0, -9.8, 0);

    physic_space = dHashSpaceCreate(0);
    physic_contactGroup = dJointGroupCreate(0);

    //dWorldSetCFM(physic_world, 1e-9);
    //dWorldSetAutoDisableFlag(physic_world, 1);
}

void physic_updateWorld(f32 pTime)
{
    if(pTime > 0)
    {
        for(u32 i = 0;i < physic_vObject.size();i++)
        {
            if (dGeomIsEnabled(physic_vObject[i].geom))
            {
                physic_setPosition(physic_vObject[i].geom);
            }
        }

        dSpaceCollide( physic_space, 0, &physic_callBack);
        dWorldQuickStep( physic_world, pTime * 0.01f);
        dJointGroupEmpty( physic_contactGroup);
    }
}

void physic_deleteWorld()
{
	dWorldDestroy(physic_world);
	dCloseODE();
}

#define MAX_CONTACTS 128
void physic_callBack(void* pNode, dGeomID o1, dGeomID o2) {
    int i;

    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

    if(b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact))
    {
        return;
    }

    dContact contact[MAX_CONTACTS];
    for (i = 0; i < MAX_CONTACTS; i++) {
        contact[i].surface.mode = dContactBounce | dContactSoftCFM;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.mu2 = 0.01f;
        contact[i].surface.bounce = 0.01f;
        contact[i].surface.bounce_vel = 0.0f;
        contact[i].surface.soft_cfm = 0.00000000000000001f;
    }

    if (int numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact)))
    {
        for (i = 0; i < numc; i++)
        {
            dJointID c = dJointCreateContact(physic_world, physic_contactGroup, contact + i);
            dJointAttach(c, b1, b2);
        }
    }
}

void physic_setPosition(dGeomID pGeom)
{
    dReal* physic_pos = (dReal*)dGeomGetPosition(pGeom);
    ISceneNode* node =  (ISceneNode*)dGeomGetData(pGeom);
    vector3df pos((f32)physic_pos[0], physic_pos[1], physic_pos[2]);
    node->setPosition(pos);

    // ODE использует quaternions, конвертируем значение в euler
    dQuaternion result;
    dGeomGetQuaternion(pGeom, result);
    quaternion quat(result[1], result[2], result[3], result[0]);
    quat.toEuler(physic_rotation);
    vector3df degrees(physic_rotation.X * 180 / PI, physic_rotation.Y * 180 / PI, physic_rotation.Z * 180 / PI);
    node->setRotation(degrees);
}

dTriMeshDataID physic_massDataObj( IMesh *mesh, ISceneNode* node) {
    dTriMeshDataID data;

    irr::u32 indexcount = 0;
    irr::u32 vertexcount = 0;

    //Vertex array for trimesh geom.
    dVector4* vertices;

    //Index array for trimesh geom.
    dTriIndex* indices;

    // count vertices and indices
    irr::u32 i;
    for (i = 0; i < mesh->getMeshBufferCount(); i++){
        const irr::scene::IMeshBuffer* mb = mesh->getMeshBuffer(i);

        indexcount += mb->getIndexCount();
        vertexcount += mb->getVertexCount();
    }

    // build structure for ode trimesh geom
    vertices = new dVector4[vertexcount];
    indices = new dTriIndex[indexcount];

    irr::u32 i_off = 0, i_cnt = 0, v_off = 0;

    const irr::core::vector3df& scale = node->getScale();

    for (irr::u32 i = 0; i < mesh->getMeshBufferCount(); ++i)
    {
      const irr::scene::IMeshBuffer* mb = mesh->getMeshBuffer(i);
      const irr::u16* mb_indices = mb->getIndices();

      for (irr::u32 j = 0; j < mb->getIndexCount(); ++j)
         indices[i_off++] = i_cnt + mb_indices[j];

      i_cnt += mb->getIndexCount();


      if (mb->getVertexType() == irr::video::EVT_STANDARD)
      {
         const irr::video::S3DVertex* mb_vertices = (irr::video::S3DVertex*)mb->getVertices();
         irr::u32 j;
         for(j = 0; j < mb->getVertexCount(); ++j)
         {
            vertices[v_off][0] = mb_vertices[j].Pos.X*scale.X;
            vertices[v_off][1] = mb_vertices[j].Pos.Y*scale.Y;
            vertices[v_off][2] = mb_vertices[j].Pos.Z*scale.Z;
            v_off++;
         }
      }
      else if (mb->getVertexType() == irr::video::EVT_2TCOORDS)
      {
         const irr::video::S3DVertex2TCoords* mb_vertices = (irr::video::S3DVertex2TCoords*)mb->getVertices();
         irr::u32 j;
         for (j = 0; j < mb->getVertexCount(); ++j)
         {
            vertices[v_off][0] = mb_vertices[j].Pos.X*scale.X;
            vertices[v_off][1] = mb_vertices[j].Pos.Y*scale.Y;
            vertices[v_off][2] = mb_vertices[j].Pos.Z*scale.Z;
            v_off++;
         }
      }
    }

    data = dGeomTriMeshDataCreate();
    dGeomTriMeshDataBuildSimple( data, (const dReal*)vertices, vertexcount, (const dTriIndex*)indices, indexcount);
    return data;
}

void physic_createPlayer(ISceneManager* smgr, vector3df pPosition)
{
    dBodyID &body = physic_sPlayer.playerBody; // Тело
    dGeomID &geom = physic_sPlayer.playerGeom; // Геометрия
    ISceneNode *&node = physic_sPlayer.node; // Узел
    ICameraSceneNode *&playerCamera = physic_sPlayer.playerCamera; // Камера

    // Создаем камеру
    playerCamera = smgr->addCameraSceneNodeFPS();
    playerCamera->setPosition(pPosition);

    // Создаем узел
    node = smgr->addCubeSceneNode();
    node->setPosition(pPosition);
    //node->setScale(vector3df(3, 10, 3));
    node->setName("adasdasd");
    // Создаем геометрию игрока, капсулу
    geom = dCreateCapsule(physic_space, 10.0f, 10.0f);
    dGeomSetPosition(geom, pPosition.X, pPosition.Y, pPosition.Z);
    dGeomSetData(geom, node);

    // Создаем тело игрока
    body = dBodyCreate(physic_world);
    dMass mass;
    dMassSetCapsule(&mass, 1.0f, 2, 5.0f, 10.0f);
    dBodySetMass(body, &mass);
    dGeomSetBody(geom, body);
    dBodySetPosition(body, pPosition.X, pPosition.Y, pPosition.Z);
    dBodySetData(body, node);

    physic_sObject.body = body;
    physic_sObject.geom = geom;
    physic_vObject.push_back(physic_sObject);
}

void physic_controlPlayer()
{
    ISceneNode *&node = physic_sPlayer.node;


    //ICameraSceneNode *&playerCamera = physic_sPlayer.playerCamera;

    //playerCamera->setPosition(node->getPosition());
}

void physic_deleteObj(IMeshSceneNode* pNode)
{
    for(u32 i = 0;i < physic_vObject.size();i++)
    {
        if(pNode == physic_vObject[i].node)
        {
            if(physic_vObject[i].body)
            {
                dBodyDestroy(physic_vObject[i].body);
            }
            if(physic_vObject[i].geom)
            {
                dGeomDestroy(physic_vObject[i].geom);
            }
            physic_vObject[i].node->grab();
            physic_vObject[i].node->remove();
            physic_vObject.erase(physic_vObject.begin() + i);
            break;
        }
    }
}

void physic_createBox(IMeshSceneNode* pNode, bool pStatic, f32 pMass)
{
    physic_sObject.node = pNode;
    dBodyID &body = physic_sObject.body;
    dGeomID &geom = physic_sObject.geom;

    vector3df nodeExtend = (pNode->getBoundingBox()).getExtent();
    vector3df nodePosition = pNode->getPosition();

    f32 lengthX = nodeExtend.X * pNode->getScale().X;
    f32 lengthY = nodeExtend.Y * pNode->getScale().Y;
    f32 lengthZ = nodeExtend.Z * pNode->getScale().Z;

    geom = dCreateBox(physic_space, lengthX, lengthY, lengthZ);
    dGeomSetPosition(geom, nodePosition.X, nodePosition.Y, nodePosition.Z);
    dGeomSetData(geom, pNode);

    if(pStatic == false)
    {
        body = dBodyCreate(physic_world);
        dMass mass;
        dMassSetBox(&mass, pMass, nodeExtend.X, nodeExtend.Y, nodeExtend.Z);
        dBodySetMass(body, &mass);
        dGeomSetBody(geom, body);
        dBodySetPosition(body, nodePosition.X, nodePosition.Y, nodePosition.Z);
        dBodySetData(body, pNode);
    }

    physic_vObject.push_back(physic_sObject);
}

void physic_createSphere(IMeshSceneNode* pNode, bool pStatic, f32 pMass)
{
    physic_sObject.node = pNode;
    dBodyID &body = physic_sObject.body;
    dGeomID &geom = physic_sObject.geom;

    vector3df nodePosition = pNode->getPosition();
    f32 radius = pNode->getMesh()->getBoundingBox().getExtent().X * pNode->getScale().X / 2;

    geom = dCreateSphere(physic_space, radius);
    dGeomSetPosition(geom, nodePosition.X, nodePosition.Y, nodePosition.Z);
    dGeomSetData(geom, pNode);

    if(pStatic == false)
    {
        body = dBodyCreate(physic_world);
        dMass mass;
        dMassSetSphere(&mass, pMass, radius);
        dBodySetMass(body, &mass);
        dGeomSetBody(geom, body);
        dBodySetPosition(body, nodePosition.X, nodePosition.Y, nodePosition.Z);
        dBodySetData(body, pNode);
    }

    physic_vObject.push_back(physic_sObject);
}

void physic_createTrg(IMeshSceneNode* pNode, bool pStatic, f32 pMass)
{
    physic_sObject.node = pNode;
    dGeomID &geom = physic_sObject.geom;
    dBodyID &body = physic_sObject.body;
    vector3df nodePosition = pNode->getPosition();
    IMesh* mesh = pNode->getMesh();

    int indexCount = 0; // Количество индексов
    int vertexCount = 0; // Количество вершин

    for(u32 i = 0;i < mesh->getMeshBufferCount();i++)
    {
        IMeshBuffer* meshBuffer = mesh->getMeshBuffer(i);
        indexCount += meshBuffer->getIndexCount();
        vertexCount += meshBuffer->getVertexCount();
    }

    // Выделяем память для массива с координатами вершин и индексов
    dVector3* arrayPosVertex = new dVector3[vertexCount];
    int* arrayIndexVertex = new int[indexCount];

    int numNowInd = 0; // Номер текущего индекса при переборе
    int numNowVertex = 0; // Номер текущей вершины при переборе

    // Перебираем и заполняем данные
    for(u32 b = 0;b < mesh->getMeshBufferCount();b++)
    {
        // Получаем мешбуффер
        IMeshBuffer* meshBuffer = mesh->getMeshBuffer(b);
        // Получаем доступ к его индексам
        u16* meshBufferGetIndex = meshBuffer->getIndices();
        // Перебираем индексы текущего мешбуффера и добавляем в массив
        for(u32 i = 0;i < meshBuffer->getIndexCount();i++)
        {
            arrayIndexVertex[numNowInd] = meshBufferGetIndex[i];
            numNowInd++;
        }
        // Перебираем вершины текущего мешбуффера и добавляем в массив
        if(meshBuffer->getVertexType() == EVT_STANDARD)
        {
            // Получаем доступ к вершинам
            S3DVertex* meshBufferGetVertices = (S3DVertex*)meshBuffer->getVertices();
            // Перебираем вершины
            for(u32 j = 0;j < meshBuffer->getVertexCount();j++)
            {
                arrayPosVertex[numNowVertex][0] = meshBufferGetVertices[j].Pos.X * pNode->getScale().X;
                arrayPosVertex[numNowVertex][1] = meshBufferGetVertices[j].Pos.Y * pNode->getScale().Y;
                arrayPosVertex[numNowVertex][2] = meshBufferGetVertices[j].Pos.Z * pNode->getScale().Z;
                numNowVertex++;
            }

        }
    }

    // Передаем данные о сетке
    dTriMeshDataID data = dGeomTriMeshDataCreate();
    dGeomTriMeshDataBuildSimple(data, (dReal*)arrayPosVertex, vertexCount, (dTriIndex*)arrayIndexVertex, indexCount);
    // Создаем геометрию
    geom = dCreateTriMesh(physic_space, data, 0, 0, 0);
    // Устанавливаем позицию
    dGeomSetPosition(geom, nodePosition.X, nodePosition.Y, nodePosition.Z);
    dGeomSetData(geom, pNode);
    dGeomSetBody(geom, 0);

    if(pStatic == false)
    {
        body = dBodyCreate( physic_world);
        dMass mass;
        dMassSetTrimesh( &mass, pMass, geom);
        dMassTranslate(&mass, -mass.c[0], -mass.c[1], -mass.c[2]);
        //dMassAdjust(&mass, 0.1);
        dBodySetMass(body, &mass);
        dGeomSetBody(geom, body);
        dBodySetPosition(body, nodePosition.X, nodePosition.Y, nodePosition.Z);
        dBodySetData(body, pNode);
    }

    physic_vObject.push_back(physic_sObject);
}
