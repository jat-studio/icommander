#ifndef SHIPS_H_INCLUDED
#define SHIPS_H_INCLUDED

/*#######################   structures   #######################*/

/*#######################   classes   #######################*/
class ClassShip : public ClassSceneObject{
    private:
    public:
        // constructor
        ClassShip(intPoint2d position) : ClassSceneObject(position){};
        // painting object
        virtual void Draw();
        // moving object
        virtual void ProcessMoving(unsigned short int direction, float speed);
        // destructor
        ~ClassShip();
};

class ClassTriangleShip : public ClassShip{
    private:
    public:
        // constructor
        ClassTriangleShip(intPoint2d position) : ClassShip(position){};
        // painting object
        virtual void Draw();
        // moving object
        virtual void ProcessMoving(unsigned short int direction, float speed);
        // destructor
        ~ClassTriangleShip();
};

class ClassQuadShip : public ClassShip{
    private:
    public:
        // constructor
        ClassQuadShip(intPoint2d position) : ClassShip(position){};
        // painting object
        virtual void Draw();
        // moving object
        virtual void ProcessMoving(unsigned short int direction, float speed);
        // destructor
        ~ClassQuadShip();
};

#endif // SHIPS_H_INCLUDED
