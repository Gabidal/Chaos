#ifndef _CORE_H_
#define _CORE_H_

#include "../Nodes/Nodes.h"

#include <map>
#include <string>

using namespace std;

class Core{
public:
    vector<Point*> Buffer;

    map<int, Chaos_Function_Handle> Handlers;

    //This determines how much of the result of the Chaos handles move each update frame. 
    float Update_Speed;
    
    Core(map<int, Chaos_Function_Handle> handlers, float update_speed = 0.1f){
        Update_Speed = update_speed;

		//This is mainly for testing
        //Buffer.insert({ "0,0", new Point() });

        Handlers = handlers;
    }

    //Returns the chunk that is at the rigth locatino, so that the handle can be placed inside of it.
    Point* Get_Point(Vector location, float radius){
        
        for (auto& p : Buffer) {
        
            //check is the point is in the radius of the point
			if (p->Location.Distance(location) < radius) {
				return p;
			}

        }

		//If the point is not in the buffer, create a new one.
		Point* New_Point = new Point(location);
        New_Point->Max_Radius = radius;
		
        Buffer.push_back(New_Point);

		return Buffer.back();
    }

    //The user needs to call this functino for every Entity they have, and save them to theyr Entity objects as a member.
    Chaos_Handle* Get_New_Handle(Vector* location, float radius){
        Chaos_Handle* handle = new Chaos_Handle(radius);
        handle->Location = location;
        
        //This is for multithreading.
        Point* p = Get_Point(*location, radius);

        if (p->Max_Radius < handle->Radius) {
            p->Max_Radius = handle->Radius;
        }

		p->Handles.push_back(handle);
        //Buffer["0,0"]->Buffer.push_back(handle);

        return handle;
    }

    //This function will update the location of the Chaos handles.
    void Update();
};

#endif