#include "Entities.h"
#include "kc/set.h"
#include <stdarg.h>

bool _entity_archetype_has(entity_archetype arch, size_t comp) {
	return kc_set_has(arch.components, comp);
}

entity_archetype entity_archetype_create(size_t comp, ...) {
	entity_archetype arch;
	arch.components = kc_set_init(16);
	va_list args;
	va_start(args, comp);
}
