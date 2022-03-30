
#include "../Nodes/Nodes.h"

#include "../Core/Core.h"

extern Core* Chaos_core;

Chaos_Handle* Get_New_Handle(Vector* location, float radius) {
	return Chaos_core->Get_New_Handle(location, radius);
}