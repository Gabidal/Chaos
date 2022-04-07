#include "Core/Core.h"

Core* Chaos_core;

#ifndef LIB
int main() {

}
#endif

void Chaos_Init(map<int, Chaos_Function_Handle> handlers, float speed) {
	Chaos_core = new Core(handlers, speed);
}

void Chaos_Update() {
	Chaos_core->Update();
}