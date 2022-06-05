using namespace std;
#ifndef AELITA_H_INCLUDED
#define AELITA_H_INCLUDED

class ClassAelita{
    private:
        // available task forces
        map<unsigned short int unit_type, vector<ClassShip*>> taskForces;
    public:
        // constructor
        ClassAelita();
        // add unit to task forces
        void ClassAelita::AddUnit(unsigned short int unit_type, ClassShip &unit);
        // give orders to available task forces
        void ClassAelita::GiveOrders();
        // destructor
        ~ClassAelita();
}

#endif // AELITA_H_INCLUDED
