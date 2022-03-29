#include "Core.h"

void Core::Update(){
    for (auto chunk : Buffer){
        chunk.second->Update();
    }
}