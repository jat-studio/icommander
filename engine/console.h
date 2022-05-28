using namespace std;
#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

class ClassConsole{
    public:
        // map of console commands
        map <string, void (ClassConsole::*)(ClassScene&, vector<string>)> commands;
        // string placing parameters
        float str_height = 0.13;
        float str_start_pos = 0.90;
        float str_current_pos = 0.90;
        // fps calculating parameters
        int fps;
        long t, dt;
        // console strings
        array<string, 14> console_str;
        // entering string
        string command_str = "Command~:";
        string current_key = "";
        // console visible state
        bool visible = false;

        // constructor
        ClassConsole();
        // painting Console
        void Draw(ClassScene &object, unsigned short int console, unsigned short int wnd);
        // set 2d mode
        void Reshape(GLsizei Width, GLsizei Height);
        // pressing Enter
        void Enter(ClassScene &active_scene);
        // add new scene object by type
        void AddSceneObject(ClassScene &active_scene, vector<string> parsed_command);
        // destructor
        ~ClassConsole();
};

#endif // CONSOLE_H_INCLUDED