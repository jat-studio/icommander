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

// list of textures
vector<string> textures_list;

// Class for basic functions
ClassScene Scene(textures_list);
// Class for console
ClassConsole Console(200);

int main(int argc, char *argv[]){
    Scene.MainWindowInit(argc, argv, "ICommander 0.0.1", {0, 0}, {1024, 768}, true );

    // defining events of window
    glutDisplayFunc([]() -> void { Scene.Draw(); });
    glutReshapeFunc([](GLsizei Width, GLsizei Height) -> void { Scene.Reshape(Width, Height); });
    glutIdleFunc([]() -> void { Scene.Draw(); Console.Draw(); });
    glutKeyboardFunc([](unsigned char key, int x, int y) -> void { Scene.ProcessKeys(key, x, y); });

    // console subwindow
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    Console.window_id = glutCreateSubWindow(Scene.main_window_id, 10, 10, glutGet(GLUT_WINDOW_WIDTH) - 20, Console.window_height);
    Scene.subwindows.insert({Console.window_id, &Console});
    glClearColor(0.0, 1.0, 0.0, 0.0);
    glutDisplayFunc([]() -> void { Console.Draw(); });
    glutReshapeFunc([](GLsizei Width, GLsizei Height) -> void { Console.Reshape(Width, Height); });

    // processing events of window
    glutMainLoop();

    // clear textures
    Scene.ClearTextures();
    glutDestroyWindow(Scene.main_window_id);

    return 0;
}
