#ifndef _NODES_H_
#define _NODES_H_

#include <math.h>
#include <vector>

using namespace std;

constexpr int CHUNK_SIZE = 16;

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
};

//The external users will have to use this Chaos handle node as amember to their Entities.
class Chaos_Handle{
public:
    float Radius;
    Vector* Location;

    Chaos_Handle(float radius){
        Radius = radius;
		Location = new Vector(0, 0, 0);
    }

    //This function returns 1 if this Node is inside of the other Node.
    //This function returns -1 if the other Node is inside of this Node.
    //This function returns 0 if the Nodes are not overlapping. Or theyre both have same radius.
    int State(Chaos_Handle* other){
        float distance = sqrt(pow(Location->X - other->Location->X, 2) + pow(Location->Y - other->Location->Y, 2));
        if (distance < Radius + other->Radius){
            //if both are overlapping eachother, but are same size
            if (Radius == other->Radius){
                return 0;
            }
            //if this node is inside of the other node
            else if (distance + Radius < other->Radius){
                return 1;
            }
            //if the other node is inside of this node
            else if (distance + other->Radius < Radius){
                return -1;
            }
        }

        //if the nodes are not overlapping
        return 0;
    }
};

class Handle_Chunk{
public:
    vector<Chaos_Handle*> Buffer;

    Handle_Chunk(){}

    void Update();
};

#endif