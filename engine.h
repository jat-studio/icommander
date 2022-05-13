using namespace std;
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

// scale of scene
const float scale = 0.07;

/*#######################   structures   #######################*/
struct sector_coordinates{
  int x;
  int y;
};

/*#######################   classes   #######################*/
class ClassScene{
  private:
  public:
    unsigned short int textures_count;
    // index texture of tiles
    GLuint *texture_tiles;
    // array for loading textures
    map <string, unsigned short int> TextureManager;
    // coordinates of tiles
    int xpos;
    int ypos;

    float camera_xpos = 0.0;
    float camera_ypos = 0.0;

    // initialization count of textures
    void InitTextures(unsigned short int textures_count);
    // loading texture by filename
    void LoadTextureImage(const char *texture_name, GLuint texture);
    // enter to ortho mode
    void setOrthoProjection(GLsizei Width, GLsizei Height);
    // exit of ortho mode
    void setPerspectiveProjection();
    // output string
    void DrawStaticString(float x, float y, float z, void *font, string input);
    // repainting OpenGL by reshape window
    void Reshape(GLsizei Width, GLsizei Height);
    // loading textures
    void LoadTextures(vector<string> textures_list);
    // deleting textures
    void ClearTextures();
    // painting Scene
    void Draw();
    /*processing move camera
      variable direction:
      0 - left
      1 - right
      2 - up
      3 - down*/
    void ProcessMoving(unsigned short int direction);
    // destructor
    ~ClassScene();

    // friendly classes
    friend class ClassConsole;
};

class ClassConsole{
  public:
    // array of functions
    map <string, void (ClassConsole::*)(int, int)> dualcommands;
    map <string, void (ClassConsole::*)(int)> singlecommands;
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
    void Enter();
    // goto x y coordinates
    void Goto_x_y(int x, int y);
    // destructor
    ~ClassConsole();
};

#endif
