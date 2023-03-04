// This is a generated file, do not edit manually
#include "Components.h"
#include <stddef.h>

size_t cp_size(COMPONENT_ENUM type) {
	switch (type) {
		case COMPONENT_SPRITE: return sizeof(Sprite);
		case COMPONENT_TRANSFORM: return sizeof(Transform);
		case COMPONENT_VELOCITY: return sizeof(Velocity);
		default: return 0;
	}
}
