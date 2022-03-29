#ifndef _CORE_H_
#define _CORE_H_

#include "../Nodes/Nodes.h"

#include <map>
#include <string>

using namespace std;

class Core{
public:
    map<string, Handle_Chunk*> Buffer;

    //This determines how much of the result of the Chaos handles move each update frame. 
    float Update_Speed;

    Core(float update_speed = 0.1f){
        Update_Speed = update_speed;
    }

    //Returns the chunk that is at the rigth locatino, so that the handle can be placed inside of it.
    Handle_Chunk* Get_Chunk(Vector location){
        int chunk_x = (int)location.X / CHUNK_SIZE;
        int chunk_y = (int)location.Y / CHUNK_SIZE;

        string key = to_string(chunk_x) + "," + to_string(chunk_y);

        if (Buffer.find(key) == Buffer.end()){
            Buffer[key] = new Handle_Chunk();
        }

        return Buffer[key];
    }

    //The user needs to call this functino for every Entity they have, and save them to theyr Entity objects as a member.
    Chaos_Handle Get_New_Handle(Vector location, float radius){
        Chaos_Handle* handle = new Chaos_Handle(radius);
        handle->Location = location;
        
        //This is for multithreading.
        Get_Chunk(location)->Buffer.push_back(handle);

        return *handle;
    }

    //This function will update the location of the Chaos handles.
    void Update();
};

#endif