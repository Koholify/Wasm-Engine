#ifndef _KGE_RENDERING_SYSTEM_H
#define _KGE_RENDERING_SYSTEM_H

#include "Config.h"
#include "Entities.h"
#include "EntityManager.h"
#include <cheerp/clientlib.h>

#if KGE_WASM
namespace [[cheerp::genericjs]] client {
void _setup_sprite_draw();
void _draw_entity_to_canvas(int texutureId, size_t color, size_t transform);
void _clear_canvas();
void _launch();
int _get_texture_from_name();
}
#else
void _setup_sprite_draw();
void _draw_entity_to_canvas(int texutureId, size_t color, size_t transform);
void _clear_canvas();
int _get_texture_from_name(const char* name);
#endif

namespace [[cheerp::genericjs]] jsrend {
	void renderer_draw_entity(struct entity_manager* manager, entity_entity entity);
}
void renderer_render_system(struct entity_manager* manager);

#endif
