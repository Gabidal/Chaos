#ifndef _CHAOS_INCLUDE_H_
#define _CHAOS_INCLUDE_H_

class Vector {
public:
    float X;
    float Y;
    float Z;

    Vector(float x, float y, float z = 0) {
        X = x;
        Y = y;
        Z = z;
    }
};

//The external users will have to use this Chaos handle node as amember to their Entities.
class Chaos_Handle {
public:
    float Radius;
    Vector* Location;

    Chaos_Handle(float radius) {
        Radius = radius;
		Location = new Vector(0, 0, 0);
    }
};

[[nodiscard]]
extern Chaos_Handle* Get_New_Handle(Vector* location, float radius);

extern void Chaos_Init(float speed);

extern void Chaos_Update();

#endif