using namespace std;
#ifndef SHIPS_H_INCLUDED
#define SHIPS_H_INCLUDED

/*#######################   structures   #######################*/

/*#######################   classes   #######################*/
class ClassShip : public ClassSceneObject{
    private:
    public:
        // constructor
        ClassShip(floatPoint3d position) : ClassSceneObject(position){};
        // painting object
        virtual void Draw();
        // destructor
        ~ClassShip();
};

class ClassTriangleShip : public ClassShip{
    private:
    public:
        // constructor
        ClassTriangleShip(floatPoint3d position) : ClassShip(position){};
        // painting object
        virtual void Draw();
        // destructor
        ~ClassTriangleShip();
};

class ClassQuadShip : public ClassShip{
    private:
    public:
        // constructor
        ClassQuadShip(floatPoint3d position) : ClassShip(position){};
        // painting object
        virtual void Draw();
        // destructor
        ~ClassQuadShip();
};

#endif // SHIPS_H_INCLUDED
