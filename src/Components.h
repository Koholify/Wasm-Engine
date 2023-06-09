// This is a generated file, do not edit manually

#ifndef _KGE_COMPONENTS_H
#define _KGE_COMPONENTS_H

#include <stddef.h>
#include "klm.h"

typedef struct Sprite {
	int id;
	vec4 color;
} Sprite;
#define GET_COMPONENT_VALUE_Sprite COMPONENT_SPRITE
#define GET_COMPONENT_SIZE_COMPONENT_COMPONENT_SPRITE sizeof(Sprite)

typedef struct Transform {
	vec3 pos;
	vec2 size;
	float rotation;
} Transform;
#define GET_COMPONENT_VALUE_Transform COMPONENT_TRANSFORM
#define GET_COMPONENT_SIZE_COMPONENT_COMPONENT_TRANSFORM sizeof(Transform)

typedef struct Velocity {
	vec2 value;
} Velocity;
#define GET_COMPONENT_VALUE_Velocity COMPONENT_VELOCITY
#define GET_COMPONENT_SIZE_COMPONENT_COMPONENT_VELOCITY sizeof(Velocity)

// Master list of components.
enum COMPONENT_ENUM {
	COMPONENT_NONE,
	COMPONENT_SPRITE,
	COMPONENT_TRANSFORM,
	COMPONENT_VELOCITY,
};
typedef enum COMPONENT_ENUM COMPONENT_ENUM;

#define GET_COMPONENT_SIZE_COMPONENT_0 0
#define GET_COMPONENT_SIZE_COMPONENT_COMPONENT_NONE 0
#define cp_type(comp) ((COMPONENT_ENUM)GET_COMPONENT_VALUE_##comp)
#define _cp_size(enm) GET_COMPONENT_SIZE_COMPONENT_##enm

size_t cp_size(COMPONENT_ENUM type);

#endif // _KGE_COMPONENTS_H
