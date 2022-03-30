#include "Core/Core.h"

Core* Chaos_core;

#ifndef LIB
int main() {

}
#endif

void Chaos_Init(float speed) {
	Chaos_core = new Core(speed);
}

void Chaos_Update() {
	Chaos_core->Update();
}