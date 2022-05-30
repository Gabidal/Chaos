#include "Core.h"

#include <thread>

void Core::Update(){
    //First check what handles intersect with what chunk areas.
	//If a handle's own radius reaches this chunk then add it to the chunk
	for (int Point_Index = 0; Point_Index < Buffer.size(); Point_Index++) {

		Point* point = Buffer[Point_Index];

		for (int i = 0; i < point->Handles.size(); i++) {
			//check if this handle collides with this point.
			//if does not then remove it
			if (point->Location.Distance(*point->Handles[i]->Location) < point->Handles[i]->Radius) {

				Chaos_Handle* Orphan_Handle = point->Handles[i];

				Buffer.push_back(new Point{ *Orphan_Handle->Location, vector<Chaos_Handle*>{Orphan_Handle}, Orphan_Handle->Radius * 10 });

				point->Handles.erase(point->Handles.begin() + i--);
			}
        }

		//Combine points with each other
		for (int Other_Point_Index = 0; Other_Point_Index < Buffer.size(); Other_Point_Index++) {
			
			if (Point_Index == Other_Point_Index) {
				continue;
			}

			Point* Other_Point = Buffer[Other_Point_Index];

			//check if this point collides with the other point
			if (point->Location.Distance(Other_Point->Location) < point->Max_Radius + Other_Point->Max_Radius) {
				//if it does then add the other point's handles to this point's handles
				if (Other_Point->Max_Radius > point->Max_Radius) {
					Other_Point->Handles.insert(Other_Point->Handles.end(), point->Handles.begin(), point->Handles.end());
					
					//remove this point from the buffer
					Buffer.erase(Buffer.begin() + Point_Index);

					if (Point_Index <= Other_Point_Index) {
						Other_Point_Index--;
					}
					if (Point_Index != 0) {
					Point_Index--;
					}
				}
				else {
					point->Handles.insert(point->Handles.end(), Other_Point->Handles.begin(), Other_Point->Handles.end());

					//remove the other point from the buffer
					Buffer.erase(Buffer.begin() + Other_Point_Index);

					if (Other_Point_Index <= Point_Index) {
						Point_Index--;
					}
					Other_Point_Index--;
				}
			}

		}
    }

	vector<thread> Threads;

	//Update the handles inside the points
	for (auto& p : Buffer) {

		//Muti thread all updates simultaneously.
		
		//thread t1(&Point::Update, &p);

		//Threads.push_back(move(t1));
		Threads.emplace_back(&Point::Update, p);

	}

	for (auto& t : Threads) {
		t.detach();
	}

}