#ifndef _KGE_PLAY_SCENE_H
#define _KGE_PLAY_SCENE_H

#include "EntityManager.h"

extern bool RUNNING;

typedef void (*scene_update)(struct entity_manager*);

typedef struct kge_scene {
	scene_update loop;
	struct entity_manager* manager;
} kge_scene;

kge_scene kge_scene_create(scene_update update);
void kge_scene_update(kge_scene scene);
void kge_scene_free(kge_scene scene);

kge_scene kge_scene_play_create();
#endif
