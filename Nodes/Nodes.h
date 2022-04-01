#ifndef _NODES_H_
#define _NODES_H_

#include <math.h>
#include <vector>
#include <map>

using namespace std;

constexpr int CHUNK_SIZE = 16;

class banana {
	
};

class Vector{
public:
    float X;
    float Y;
    float Z;

    Vector(float x, float y, float z = 0){
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
		return {X - other.X, Y - other.Y, Z - other.Z};
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
    constexpr int DEAD_ZONE             = 1 << 5;
    constexpr int FAR                   = 1 << 6;
}

//The external users will have to use this Chaos handle node as amember to their Entities.
class Chaos_Handle{
public:
    float Radius;
    Vector* Location;

    Vector* Objective;

    Vector* Previus_Location;

    //Use themselfs addresses as keys
    map<Chaos_Handle*, Chaos_Handle*> Childs;

    Chaos_Handle(float radius){
        Radius = radius;
		Location = new Vector(0, 0, 0);
        Previus_Location = new Vector(0, 0, 0);
        Objective = nullptr;
    }
	
    //This function checks if the value has the bitmask inside of it
    static bool is(int value, int bit_mask);

    //This function returns STATE::A_INSIDE_OF_B if this Node is inside of the other Node.
    //This function returns STATE::B_INSIDE_OF_A if the other Node is inside of this Node.
    //This function returns STATE::NOT_OVERLAPPING if the Nodes are not overlapping. 
    //This function returns STATE::SAME_RADIUS if the Nodes both have the same radius.
    //This function returns STATE::NECK_TO_NECK if the Nodes are neck to neck.
    //This function returns STATE::DEAD_ZONE if the Node A is inside of Node B and is closer than its own radius.
    //Thus function returns STATE::FAR if the two nodes are farther than their combined radius from each other.
    int State(Chaos_Handle* other);
};

class Handle_Chunk{
public:
    vector<Chaos_Handle*> Buffer;

    Handle_Chunk(){}

    void Update();
};

#endif