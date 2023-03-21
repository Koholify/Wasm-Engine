#include <iostream>
#include "KGE.hpp"

int main(void) {
	std::cout << "Starting up hehe\n";
	kge_init();

#if KGE_TERMINAL
	while (kge_update()) {
	}
	kge_cleanup();
#endif
}

