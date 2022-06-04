using namespace std;
#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

class ClassConsole : public ClassSceneSubWindow{
    private:
        const static unsigned short int CONSOLE_FONT_PIXELS_LINE_SPACING = 4;
        const static unsigned short int CONSOLE_FONT_PIXELS_HEIGHT = 13;
        // from -1 to +1, where 0 is center of window
        const static unsigned short int CONSOLE_WINDOW_SIZE = 2;

        struct consoleCommand{
            void (ClassConsole::*function_ptr)(ClassScene&, vector<string>);
            string description;
        };

        // register new command in console
        void RegisterCommand(string name, void (ClassConsole::*function_ptr)(ClassScene&, vector<string>), string description);
    public:
        unsigned short int window_id;
        unsigned short int window_height;
        // map of console commands
        map <string, consoleCommand> commands;
        // string placing parameters
        unsigned short int lines_count;
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

        // constructor
        ClassConsole(unsigned short int window_height);
        // painting Console
        virtual void Draw();
        // set 2d mode
        virtual void Reshape(GLsizei Width, GLsizei Height);
        // processing keyboard keys in console mode
        virtual void ProcessKeys(ClassScene &active_scene, unsigned char key, int x, int y);
        // add some string to end of console
        void AddStr(string new_string);
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
