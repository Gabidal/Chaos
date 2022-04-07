#ifndef _CHAOS_INCLUDE_H_
#define _CHAOS_INCLUDE_H_

#include <random>
#include <map>

using namespace std;

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

    void operator+=(Vector other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
    }

    void operator-=(Vector other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
    }

    void operator*=(float other) {
        X *= other;
        Y *= other;
        Z *= other;
    }

    Vector operator-(Vector other) {
        return { X - other.X, Y - other.Y, Z - other.Z };
    }

    bool operator<=(Vector other) {
        return X <= other.X && Y <= other.Y && Z <= other.Z;
    }

    static Vector* Normalize(Vector other);

    static Vector* Abs(Vector other) {
        Vector* Result = new Vector(other);

        Result->X = abs(Result->X);
        Result->Y = abs(Result->Y);
        Result->Z = abs(Result->Z);

        return Result;
    }
};

namespace CHAOS_UTILS {
    static float Rand() {
        return (float)rand() / RAND_MAX;
    }

    static float Rand(float Min, float Max) {
        return Min + Rand() * (Max - Min);
    }
}

namespace STATE {
    constexpr int A_INSIDE_OF_B         = 1 << 0;
    constexpr int B_INSIDE_OF_A         = 1 << 1;
    constexpr int NOT_OVERLAPPING       = 1 << 2;
    constexpr int SAME_RADIUS           = 1 << 3;
    constexpr int NECK_TO_NECK          = 1 << 4;
    constexpr int FAR                   = 1 << 5;

    constexpr int NEW_CHILD             = 1 << 6;
    constexpr int REMOVED_CHILD         = 1 << 7;

    constexpr int NEW_NEIGHBOUR         = 1 << 8;
    constexpr int REMOVED_NEIGHBOUR     = 1 << 9;
    constexpr int CLOSE                 = 1 << 10;
}

//The external users will have to use this Chaos handle node as amember to their Entities.
class Chaos_Handle {
public:
    float Radius;
    Vector* Location;

    //Use themselfs addresses as keys
    map<Chaos_Handle*, Chaos_Handle*> Childs;
    map<Chaos_Handle*, Chaos_Handle*> Neighbours;

    Chaos_Handle(float radius) {
        Radius = radius;
        Location = new Vector(0, 0, 0);
    }

    //This function checks if the value has the bitmask inside of it
    //static bool is(int value, int bit_mask);
};

typedef Vector* (*Chaos_Function_Handle)(Chaos_Handle* A, Chaos_Handle* B);

[[nodiscard]]
extern Chaos_Handle* Get_New_Handle(Vector* location, float radius);

extern void Chaos_Init(map<int, Chaos_Function_Handle> handlers, float speed);

extern void Chaos_Update();

#endif