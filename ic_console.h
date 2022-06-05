using namespace std;
#ifndef IC_CONSOLE_H_INCLUDED
#define IC_CONSOLE_H_INCLUDED

#include <engine/console.h>

class ClassICConsole : public ClassConsole{
    public:
        // constructor
        ClassICConsole(unsigned short int window_height);
        // add new scene object by type
        void AddSceneObject(ClassScene &active_scene, vector<string> parsed_command);
        // view list of objects or object info
        void GetObjectInfo(ClassScene &active_scene, vector<string> parsed_command);
};

#endif // IC_CONSOLE_H_INCLUDED
