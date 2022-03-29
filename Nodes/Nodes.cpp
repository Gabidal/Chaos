#include "Nodes.h"
#include "../Core/Core.h"

extern Core* core;


//The rules that all Handles follow:
//Same size radius Handles get away from eachother.
//Smaller radius Handles try to get inside a bigger radius Handle. 
void Handle_Chunk::Update(){

    for (auto Handle_A : Buffer){

        Vector Average_Velocity(0, 0, 0);

        for (auto Handle_B : Buffer){
            if (Handle_A != Handle_B){
                int Result = Handle_A->State(Handle_B);
                
                if (Result == 0){
                    if (Handle_A->Radius == Handle_B->Radius){
                        //This means that the handles are either overlapping or same radius.
                        //So we need to move them away from eachother.
                        Average_Velocity.X -= Handle_B->Location.X - Handle_A->Location.X;
                        Average_Velocity.Y -= Handle_B->Location.Y - Handle_A->Location.Y;
                        Average_Velocity.Z -= Handle_B->Location.Z - Handle_A->Location.Z;
                    }
                    else if (Handle_A->Radius < Handle_B->Radius){
                        //This means that the Handle_A is smaller than Handle_B.
                        //So we need to move to the Handle_B.
                        Average_Velocity.X += Handle_B->Location.X - Handle_A->Location.X;
                        Average_Velocity.Y += Handle_B->Location.Y - Handle_A->Location.Y;
                        Average_Velocity.Z += Handle_B->Location.Z - Handle_A->Location.Z;
                    }
                }
            }
        }

        //Now we need to normalize the average velocity to the core->Update_Speed.
        float length = sqrt(pow(Average_Velocity.X, 2) + pow(Average_Velocity.Y, 2) + pow(Average_Velocity.Z, 2));
        Average_Velocity.X /= length;
        Average_Velocity.Y /= length;
        Average_Velocity.Z /= length;

        Handle_A->Location.X += Average_Velocity.X * core->Update_Speed;
        Handle_A->Location.Y += Average_Velocity.Y * core->Update_Speed;
        Handle_A->Location.Z += Average_Velocity.Z * core->Update_Speed;
    }

}