#include <iostream>
#include "KGE.hpp"

int main(void) {
#ifdef __cplusplus
	std::cout << "is cpp\n";
#endif
	kge_init();
}
