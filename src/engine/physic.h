#ifndef PHYSIC_H
#define PHYSIC_H

//#define dSINGLE
#define dDOUBLE

#include <ode/ode.h>
#include <irrlicht.h>
#include <iostream>
#include <vector>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

// Мир содержащий все тела
extern dWorldID physic_world;

// Указатель на геометрию пространства
extern dSpaceID physic_space;

// Указатель на контактные соединения группы
extern dJointGroupID physic_contactGroup;

// Переменная для поворота
extern vector3df physic_rotation;

// Структура для динамических объектов
struct physic_structObject
{
    ISceneNode* node;
    dBodyID body;
    dGeomID geom;
} extern physic_sObject;

// Список динамических объектов
extern vector< physic_structObject> physic_vObject;
extern vector< physic_structObject>::iterator physic_vObjectIter;

// Структура для игрока
struct physic_structPlayer
{
    ICameraSceneNode* playerCamera;
    ISceneNode* node;
    dBodyID playerBody;
    dGeomID playerGeom;
} extern physic_sPlayer;

// Создать мир
void physic_init();

// Обновить мир
void physic_updateWorld(f32 pTime);

// Удалить мир
void physic_deleteWorld();

// Функция вызывается когда два объекта могут столкнуться
void physic_callBack(void* pNode, dGeomID o1, dGeomID o2);

// Позиционирование тела
void physic_setPosition(dGeomID pGeom);

// Удалить объект
void physic_deleteObj(IMeshSceneNode* pNode);

// Создать квадратное тело
void physic_createBox(IMeshSceneNode* pNode, bool pStatic, f32 pMass);

// Создать круглое тело
void physic_createSphere(IMeshSceneNode* pNode, bool pStatic, f32 pMass);

// Создать произвольное тело
void physic_createTrg(IMeshSceneNode* pNode, bool pStatic, f32 pMass);

// Создать игрока
void physic_createPlayer(ISceneManager* smgr, vector3df pPosition);

// Обрабатывать игрока
void physic_controlPlayer();

#endif // PHYSIC_H
