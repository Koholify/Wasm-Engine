#ifndef _KGE_COMPONENTS_H
#define _KGE_COMPONENTS_H

#include "klm.h"

typedef struct Transform {
	klm_vec3 pos;
	klm_vec2 size;
} Transform;
#define GET_COMPONENT_VALUE_Transform TRANSFORM

typedef struct Sprite {
	int id;
	klm_vec4 color;
} Sprite;
#define GET_COMPONENT_VALUE_Sprite SPRITE

// Master list of components.
enum COMPONENT_ENUM {
	NONE,
	TRANSFORM,
	SPRITE,
};
typedef enum COMPONENT_ENUM COMPONENT_ENUM;

#define cp_type(comp) ((size_t)GET_COMPONENT_VALUE_##comp)

#endif // _KGE_COMPONENTS_H
