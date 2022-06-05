using namespace std;

/*Basic c library*/
#include <map>
#include <string>
#include <typeinfo>
#include <vector>

/*Open GL*/
#include "GL/glut.h"

/*My library*/
#include "engine/core.h"
#include "engine/console.h"
#include "engine/utils.h"
#include "ic_console.h"
#include "ships.h"

// constructor
ClassICConsole::ClassICConsole(unsigned short int window_height) : ClassConsole(window_height){
    //this->commands["addobj"] = {
    //    &ClassICConsole::AddSceneObject,
    //    "[addobj <obj_type> <float_speed>] add new object into scene, obj_types: 0 - triangle, 1 - quad"
    //};
    //this->commands["objects"] = {
    //    &ClassICConsole::GetObjectInfo,
    //    "[objects <object_id>] list objects or object info with object_id defined"
    //);
}

// add new scene object by type
void ClassICConsole::AddSceneObject(ClassScene &active_scene, vector<string> parsed_command){
    unsigned short int object_type = Str_To_Int( parsed_command[1] );
    float speed = 0.0;
    if (parsed_command.size() > 2){
        speed = stof( parsed_command[2] );
    }

    floatPoint3d position;
    position.x = float( rand() % 130 - 65 );
    position.y = float( rand() % 70 - 35 );
    position.z = 0.0;

    ClassSceneObject* new_scene_object;
    switch (object_type){
        case 0:
            new_scene_object = new ClassTriangleShip(position);
        break;
        case 1:
            new_scene_object = new ClassQuadShip(position);
        break;
    }

    new_scene_object->speed = speed;
    active_scene.scene_objects.push_back(new_scene_object);
}

// view list of objects or object info
void ClassICConsole::GetObjectInfo(ClassScene &active_scene, vector<string> parsed_command){
    if (parsed_command.size() > 1){
        unsigned short int object_id = Str_To_Int( parsed_command[1] );

        this->AddStr( to_string( active_scene.scene_objects[ object_id ]->speed ) );
    }
    else {
        unsigned short int i = 0;
        for ( ClassSceneObject* scene_object : active_scene.scene_objects ){
            this->AddStr( "[" + to_string(i) + "] " + typeid(scene_object).name() );
            i++;
        }
    }
}
