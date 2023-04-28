#ifndef _KGE_RENDERING_SYSTEM_H
#define _KGE_RENDERING_SYSTEM_H

#include "Config.h"
#include "Entities.h"
#include "EntityManager.h"

#if KGE_WASM
extern void _setup_sprite_draw();
extern void _draw_entity_to_canvas(int texutureId, float* color, float* transform);
extern void _clear_canvas();
extern int _get_texture_from_name(const char* name);
#else
void _setup_sprite_draw();
void _draw_entity_to_canvas(int texutureId, float* color, float* transform);
void _clear_canvas();
int _get_texture_from_name(const char* name);
#endif

void renderer_draw_entity(struct entity_manager* manager, entity_entity entity);
void renderer_render_system(struct entity_manager* manager);
int renderer_get_texture(const char* name);

#endif
