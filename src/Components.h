#ifdef _KGE_COMPONENTS_H
#define _KGE_COMPONENTS_H

#include "klm.h"

typedef struct Transform {
	klm_vec3 pos;
	klm_vec2 size;
} Transform;

#define GET_COMPONENT_VALUE_Transform TRANSFORM

// Master list of components.
enum COMPONENT_ENUM {
	NONE,
	TRANSFORM,
};

#endif // _KGE_COMPONENTS_H
