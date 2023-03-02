// This is a generated file, do not edit manually

#ifndef _KGE_COMPONENTS_H
#define _KGE_COMPONENTS_H

#include "klm.h"

typedef struct Sprite {
	int id;
	vec4 color;
} Sprite;
#define GET_COMPONENT_VALUE_Sprite COMPONENT_SPRITE

typedef struct Transform {
	vec3 pos;
	vec2 size;
	float rotation;
} Transform;
#define GET_COMPONENT_VALUE_Transform COMPONENT_TRANSFORM

typedef struct Velocity {
	vec2 value;
} Velocity;
#define GET_COMPONENT_VALUE_Velocity COMPONENT_VELOCITY

// Master list of components.
enum COMPONENT_ENUM {
	COMPONENT_NONE,
	COMPONENT_SPRITE,
	COMPONENT_TRANSFORM,
	COMPONENT_VELOCITY,
};
typedef enum COMPONENT_ENUM COMPONENT_ENUM;

#define cp_type(comp) ((size_t)GET_COMPONENT_VALUE_##comp)

#endif // _KGE_COMPONENTS_H
