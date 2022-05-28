using namespace std;
#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

class ClassConsole{
    private:
        const static unsigned short int CONSOLE_FONT_PIXELS_LINE_SPACING = 4;
        const static unsigned short int CONSOLE_FONT_PIXELS_HEIGHT = 13;
        // from -1 to +1, where 0 is center of window
        const static unsigned short int CONSOLE_WINDOW_SIZE = 2;
    public:
        unsigned short int window_height;
        unsigned short int lines_count;
        // map of console commands
        map <string, void (ClassConsole::*)(ClassScene&, vector<string>)> commands;
        // string placing parameters
        float str_height;
        float font_line_spacing;
        float str_current_pos;
        // fps calculating parameters
        int fps;
        long t, dt;
        // console strings
        vector<string> console_str;
        // entering string
        string command_str = "Command~:";
        string current_key = "";
        // console visible state
        bool visible = false;

        // constructor
        ClassConsole(unsigned short int window_height);
        // painting Console
        void Draw(ClassScene &active_scene, unsigned short int console, unsigned short int wnd);
        // set 2d mode
        void Reshape(GLsizei Width, GLsizei Height);
        // processing keyboard keys in console mode
        void ProcessKeys(ClassScene &active_scene, unsigned char key);
        // pressing Enter
        void Enter(ClassScene &active_scene);
        // add new scene object by type
        void AddSceneObject(ClassScene &active_scene, vector<string> parsed_command);
        // view console commands
        void ViewHelp(ClassScene &active_scene, vector<string> parsed_command);
        // destructor
        ~ClassConsole();
};

#endif // CONSOLE_H_INCLUDED
