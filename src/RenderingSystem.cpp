#include "RenderingSystem.h"
#include "Components.h"
#include "Entities.h"
#include "EntityManager.h"
#include "kc/array.h"
#include <iterator>
#include <stddef.h>
#include <cheerp/clientlib.h>
#include <cheerp/client.h>

void renderer_render_system(struct entity_manager *manager) {
	entity_archetype renderable = entity_archetype_create(cp_type(Sprite), cp_type(Transform));
	entity_entity* entities = entity_manager_query_entities(manager, renderable);
	client::_clear_canvas();
	client::_setup_sprite_draw();

	for (size_t i = 0; i < kc_arr_len(entities); i++) {
		jsrend::renderer_draw_entity(manager, entities[i]);
	}

	entity_archetype_free(renderable);
	kc_arr_free(entities);
}

void renderer_draw_entity(struct entity_manager *manager, entity_entity entity) {
	const Sprite* sprite = entity_manager_read_component(manager, entity, Sprite);
	const Transform* trans = entity_manager_read_component(manager, entity, Transform);

	float color[4] = { 0 };
	float mv[16] = { 0 };
	color[0] = sprite->color.x;
	color[1] = sprite->color.y;
	color[2] = sprite->color.z;
	color[3] = sprite->color.w;

	mv[0] = 1.0f;
	mv[5] = 1.0f;
	mv[10] = 1.0f;
	mv[15] = 1.0f;
	mv[14] = trans->pos.z;
	mv[13] = trans->pos.y;
	mv[12] = trans->pos.x;
	
	client::_draw_entity_to_canvas(sprite->id, (size_t)color, (size_t)mv);
}

#ifndef KGE_WASM
void _draw_entity_to_canvas(int texutureId, float* color, float* transform) {}
void _clear_canvas() {}
void _setup_sprite_draw() {}
#endif
