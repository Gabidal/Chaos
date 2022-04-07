#include "Nodes.h"
#include "../Core/Core.h"

extern Core* Chaos_core;

int Accuracity = 1;

int Chaos_Handle::State(Chaos_Handle* other) {
    float distance = sqrt(pow(Location->X - other->Location->X, 2) + pow(Location->Y - other->Location->Y, 2));

    int Result = 0;

    if (distance < Radius + other->Radius) {
        //if both have the same radius
        if (abs(Radius - other->Radius) <= Accuracity) {
            Result |= STATE::SAME_RADIUS;
        }
        //if this node is inside of the other node
        if (Radius < other->Radius) {
            if (abs(Radius + distance - other->Radius) <= 1) {
                Result |= STATE::A_INSIDE_OF_B;
            }
        }
        //if the other node is inside of this node
        else if (other->Radius < Radius) {
            Result |= STATE::B_INSIDE_OF_A;

            //If the smaller handle is not already inside of the bigger one, then add it to it.
            if (Childs.find(other) == Childs.end()) {

                //If the new child has been a neighbour then remove it.
                if (Neighbours.find(other) != Neighbours.end()) {
                    Neighbours.erase(other);

                    Result |= STATE::REMOVED_NEIGHBOUR;
                }

                Childs.emplace(other, other);

                Result |= STATE::NEW_CHILD;
            }
        }

    }
    //if both Nodes are neck to neck
    else if (abs(distance - (Radius + other->Radius)) <= Accuracity) {
        Result |= STATE::NECK_TO_NECK;

        //If the smaller handle is not already inside of the bigger one, then add it to it.
        if (Neighbours.find(other) == Neighbours.end()) {

            //If the new child has been a neighbour then remove it.
            if (Childs.find(other) != Childs.end()) {
                Childs.erase(other);

                Result |= STATE::REMOVED_CHILD;
            }

            Neighbours.emplace(other, other);

            Result |= STATE::NEW_NEIGHBOUR;
        }
    }
    //if the nodes are not overlapping
    else {
        if (distance > Radius + other->Radius) {
            Result |= STATE::FAR;
        }
        else {
            Result |= STATE::CLOSE;
        }

        Result |= STATE::NOT_OVERLAPPING;

        if (Neighbours.find(other) != Neighbours.end()) {
            Neighbours.erase(other);

            Result |= STATE::REMOVED_NEIGHBOUR;
        }
        else if (Childs.find(other) != Childs.end()) {
            Childs.erase(other);

            Result |= STATE::REMOVED_CHILD;
        }
    }

    return Result;
}

bool Chaos_Handle::is(int value, int bit_mask) {
    return (bit_mask & value) == bit_mask;
}

//The rules that all Handles follow:
//Same size radius Handles get away from eachother.
//Smaller radius Handles try to get inside a bigger radius Handle. 
void Handle_Chunk::Update(){

    for (auto Handle_A : Buffer){

        Vector* Average_Velocity = new Vector(0, 0, 0);

        for (auto Handle_B : Buffer){
            if (Handle_A != Handle_B){
                int state = Handle_A->State(Handle_B);

                if (Chaos_core->Handlers.find(state) != Chaos_core->Handlers.end()) {
                    Vector* Result = Chaos_core->Handlers[state](Handle_A, Handle_B);

                    if (Result)
                        *Average_Velocity += *Result;
                }
                else {
                    for (auto i : Chaos_core->Handlers) {
                        if (Chaos_Handle::is(state, i.first)) {
                            Vector* Result = i.second(Handle_A, Handle_B);

                            if (Result)
                                *Average_Velocity += *Result;

                            break;
                        }
                    }
                }
            }
        }

        //Update the Handle_A's position with the new normalized data
        Average_Velocity = Vector::Normalize(*Average_Velocity);

        if (Average_Velocity == nullptr) {
            continue;
        }

        *Handle_A->Location += *Average_Velocity;
    }
}

Vector* Vector::Normalize(Vector other) {
    //Now we need to normalize the average velocity to the core->Update_Speed.
    float length = sqrt(pow(other.X, 2) + pow(other.Y, 2) + pow(other.Z, 2));

    if (length == 0)
        return nullptr;

    other.X /= length;
    other.Y /= length;
    other.Z /= length;

    other.X *= Chaos_core->Update_Speed;
    other.Y *= Chaos_core->Update_Speed;
    other.Z *= Chaos_core->Update_Speed;

    return new Vector(other);
}
