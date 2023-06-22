#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <unordered_set>
#include "Components.h"
#include "Entities.h"
#include "kc/set.h"

bool _entity_archetype_has(entity_archetype arch, size_t comp) {
	COMPONENT_ENUM cp = static_cast<COMPONENT_ENUM>(comp);
	return arch.components.find(cp) != arch.components.end();
}

entity_archetype _entity_archetype_create(COMPONENT_ENUM comp, ...) {
	entity_archetype arch;
	arch.components = std::unordered_set<COMPONENT_ENUM>();
	arch.components.reserve(16);
	va_list args;
	va_start(args, comp);
	while(comp) {
		arch.components.insert(comp);
		comp = va_arg(args, COMPONENT_ENUM);
	}

	va_end(args);
	return arch;
}

entity_archetype _entity_archetype_create(size_t comp, ...) {
	entity_archetype arch;
	arch.components = std::unordered_set<COMPONENT_ENUM>();
	arch.components.reserve(16);
	va_list args;
	va_start(args, comp);
	while(comp) {
		arch.components.insert(static_cast<COMPONENT_ENUM>(comp));
		comp = va_arg(args, COMPONENT_ENUM);
	}

	va_end(args);
	return arch;
}

void entity_archetype_add_type(entity_archetype* arch, COMPONENT_ENUM cp) {
	arch->components.insert(cp);
}

void entity_archetype_remove_type(entity_archetype* arch, COMPONENT_ENUM cp) {
	arch->components.erase(cp);
}

void entity_archetype_free(entity_archetype arch) {
	(void)arch;
}

bool entity_archetype_equals(entity_archetype a, entity_archetype b) {
	return a.components == b.components;
}

bool entity_archetype_sub(entity_archetype a, entity_archetype b) {
	if ( a.components.size() <= b.components.size()) {
		for (auto c : a.components) {
			if (b.components.find(c) == b.components.end()) {
				return false;
			}
		}
		return true;
	}
	return false;
}

entity_archetype entity_archetype_copy(entity_archetype a){
	entity_archetype arch = entity_archetype_create(0);
	for(auto c : a.components) {
		arch.components.insert(c);
	}
	return arch;
}

void print_entity_archetype(entity_archetype arch) {
	for(auto c : arch.components) {
			printf("%lu, ", (unsigned long)c);
	}
	printf("\n");
}
