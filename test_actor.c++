#include "shared/Actor.h++"
#include <iostream>
using namespace std;

int main()
{
    ClassLibrary::instance().push_back(ActorClass(0,0.1,0.1));
    Actor act(0,0,Vector(0.5,0.5));
    Vector velocity(0.01,0.01);
    
    cout << "Original position:" << act.position() << endl;
    act.updateVelocity(10,velocity);
    
    act.updatePosition(100);
    cout << "New position after 100 msec:" << act.position() << endl;
    
    act.translocate(100,Vector(0.0,0.0));
    cout << "Translocate test:" << act.position() << endl;
    
    cout << "WxH: "<< act.classDef().width() << "x" << act.classDef().height() << endl;
    return 0;
}
