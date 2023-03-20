#include <iostream>
#include "Config.h"
#include "KGE.hpp"

#if TARGET == WASM
#include <emscripten.h>
#endif

int EMSCRIPTEN_KEEPALIVE main(void) {
	std::cout << "Starting up hehe\n";
	kge_init();
}
