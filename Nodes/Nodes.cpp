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
            Result |= STATE::A_INSIDE_OF_B;
			
            //The node A is closer to the node B center than the A own radius.
            if (distance < Radius)
                Result |= STATE::DEAD_ZONE;
        }
        //if the other node is inside of this node
        else if (other->Radius < Radius) {
            Result |= STATE::B_INSIDE_OF_A;
			
            //The node B is closer to the node A center than the B own radius.
            if (distance < other->Radius)
                Result |= STATE::DEAD_ZONE;
        }

    }
    //if both Nodes are neck to neck
    else if (abs(distance - (Radius + other->Radius)) <= Accuracity) {
        Result |= STATE::NECK_TO_NECK;
    }
    //if the nodes are not overlapping
    else {
        Result |= STATE::NOT_OVERLAPPING;
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
                int Result = Handle_A->State(Handle_B);

				//if the Handle A is not inside of B
                if (Chaos_Handle::is(Result, STATE::NOT_OVERLAPPING)) {
                    //if Handle A is smaller than B
                    if (Handle_A->Radius < Handle_B->Radius) {
                        //A goes towards B
                        *Average_Velocity += *Handle_B->Location - *Handle_A->Location;
					}
                }
                else if (Chaos_Handle::is(Result, STATE::NECK_TO_NECK)) {
					//Get away from the 
                    *Average_Velocity -= *Handle_B->Location - *Handle_A->Location;
                }

                //If B is inside of A, then insert B into A's children, for later on to calculate the Lagrient points.
                if (Chaos_Handle::is(Result, STATE::B_INSIDE_OF_A)) {
                    if (Handle_A->Childs.find(Handle_B) != Handle_A->Childs.end()) {
                        //We use same address for keys also as the values
                        Handle_A->Childs.insert({ Handle_B, Handle_B });
                    }
                }
                else if (Chaos_Handle::is(Result, STATE::A_INSIDE_OF_B)) {
                    if (Chaos_Handle::is(Result, STATE::DEAD_ZONE)) {
                        *Average_Velocity -= *Handle_A->Location - *Handle_B->Location;
                    }
                    else{
                        *Average_Velocity += *Handle_A->Location - *Handle_B->Location;
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

        //If the handle has an objective
        if (Handle_A->Objective)
            //go a little towards the objective
            *Handle_A->Location += *Vector::Normalize(*Handle_A->Objective);
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
