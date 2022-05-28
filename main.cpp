using namespace std;
/*Basic c library*/
#include <string>
#include <iostream>
#include <vector>
#include <map>

/*Open GL*/
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"

/*My library*/
#include "engine/core.h"
#include "engine/console.h"
#include "engine/ic_strings.h"
#include "ships.h"

// id GLwindow
unsigned short int main_window_id, console_window_id;

unsigned short int console_window_height = 70;

// list of textures
vector<string> textures_list;

// Class for basic functions
ClassScene Scene(textures_list);
// Class for console
ClassConsole Console(console_window_height);

// repainting OpenGL by reshape window
void SceneReshape(GLsizei Width, GLsizei Height){
    Scene.Reshape(Width, Height);
    // reshaping console window
    glutSetWindow(console_window_id);
    glutHideWindow();
    glutReshapeWindow( Width - 20, console_window_height );
    glutShowWindow();
    glutSetWindow(main_window_id);
}

// processing keys in game mode
void GameModeKeys(unsigned char key){
    switch (key){
        // escape - exit
        case 27:
            Scene.ClearTextures();
            glutDestroyWindow(main_window_id);
        break;
        // "`" key - enter console mode
        case 96:
            Console.visible = true;
            Scene.app_mode = 1;
        break;
    }
}

// processing keys
void Keyboard(unsigned char key, int x, int y){
    // select application mode
    switch (Scene.app_mode){
        // game mode
        case 0:
            GameModeKeys(key);
        break;
        // console mode
        case 1:
            Console.ProcessKeys(Scene, key);
        break;
    }
}

int main(int argc, char *argv[]){
    // initializing and create window GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1024, 768);
    main_window_id = glutCreateWindow("ICommander 0.0.1");
    glutFullScreen();

    // defining events of window
    glutDisplayFunc([]() -> void { Scene.Draw(); });
    glutReshapeFunc(SceneReshape);
    glutIdleFunc([]() -> void { Scene.Draw(); Console.Draw(Scene, console_window_id, main_window_id); });
    glutKeyboardFunc(Keyboard);

    // background color
    glClearColor(0, 0, 0, 0.0);
    // smoothing paint of color
    glShadeModel(GL_SMOOTH);
    // modified perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // console subwindow
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    console_window_id = glutCreateSubWindow(main_window_id, 10, 10, glutGet(GLUT_WINDOW_WIDTH) - 20, console_window_height);
    glClearColor(0.0, 1.0, 0.0, 0.0);
    glutDisplayFunc([]() -> void { Console.Draw(Scene, console_window_id, main_window_id); });
    glutReshapeFunc([](GLsizei Width, GLsizei Height) -> void { Console.Reshape(Width, Height); });

    // processing events of window
    glutMainLoop();

    // clear textures
    Scene.ClearTextures();
    glutDestroyWindow(main_window_id);

    return 0;
}
