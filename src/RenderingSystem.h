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
}
#else
void _setup_sprite_draw();
void _draw_entity_to_canvas(int texutureId, size_t color, size_t transform);
void _clear_canvas();
#endif

namespace [[cheerp::genericjs]] jsrend {
	[[cheerp::genericjs]] void renderer_draw_entity(struct entity_manager* manager, entity_entity entity);
}
void renderer_render_system(struct entity_manager* manager);

#endif
