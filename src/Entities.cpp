#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include "Components.h"
#include "Entities.h"
#include "kc/set.h"

bool _entity_archetype_has(entity_archetype arch, size_t comp) {
	return kc_set_has(arch.components, comp);
}

entity_archetype _entity_archetype_create(COMPONENT_ENUM comp, ...) {
	entity_archetype arch;
	arch.components = kc_set_init(16);
	va_list args;
	va_start(args, comp);
	while(comp) {
		kc_set_set(&arch.components, comp);
		comp = va_arg(args, COMPONENT_ENUM);
	}

	va_end(args);
	return arch;
}

entity_archetype _entity_archetype_create(size_t comp, ...) {
	entity_archetype arch;
	arch.components = kc_set_init(16);
	va_list args;
	va_start(args, comp);
	while(comp) {
		kc_set_set(&arch.components, comp);
		comp = va_arg(args, COMPONENT_ENUM);
	}

	va_end(args);
	return arch;
}

void entity_archetype_add_type(entity_archetype* arch, COMPONENT_ENUM cp) {
	kc_set_set(&arch->components, cp);
}

void entity_archetype_remove_type(entity_archetype* arch, COMPONENT_ENUM cp) {
	kc_set_remove(arch->components, cp);
}

void entity_archetype_free(entity_archetype arch) {
	kc_set_free(arch.components);
}

bool entity_archetype_equals(entity_archetype a, entity_archetype b) {
	return kc_set_equals(a.components, b.components);
}

bool entity_archetype_sub(entity_archetype a, entity_archetype b) {
	return kc_set_sub(a.components, b.components);
}

entity_archetype entity_archetype_copy(entity_archetype a){
	entity_archetype arch;
	arch.components = kc_set_copy(a.components);
	return arch;
}

void print_entity_archetype(entity_archetype arch) {
	kc_set_iterator it = kc_set_iter(arch.components);
	size_t val;
	while (kc_set_next(&it, &val))
			printf("%lu, ", val);
	printf("\n");
}
