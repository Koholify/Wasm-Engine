#include <stdbool.h>
#include <stdio.h>
#include "Components.h"
#include "Entities.h"
#include "EntityManager.h"
#include "RenderingSystem.h"
#include "kc/array.h"
#include "klm.h"
#include "tests.h"
#include "Scene.h"
#include "Config.h"
#include "Init.h"

#if KGE_TERMINAL
// Raw Mode
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

struct termios orig_termios;

static void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

static void enable_raw_mode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disable_raw_mode);
	
	struct termios raw = orig_termios;
	raw.c_iflag &= ~(IXON | ICRNL);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	//raw.c_oflag &= ~(OPOST);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
#endif

bool RUNNING = true;
kge_scene ActiveScene;

void kge_init(void) {
	//run_tests();
	
#if KGE_TERMINAL
	enable_raw_mode();
#endif

	kge_scene play = kge_scene_play_create();
	ActiveScene = play;
	entity_archetype arch = entity_archetype_create(cp_type(Velocity), cp_type(Sprite), cp_type(Transform));
	entity_entity entity = entity_manager_add_entity(play.manager, arch);

	Sprite sprite = { client::_get_texture_from_name(), { 1.f, 1.f, 0.f, 1.f } };
	Transform trans = { { }, { 1.f, 1.f }, 0.f };
	Velocity vel = { { 0.002f, 0.001f } };

	entity_manager_set_component(play.manager, entity, cp_type(Sprite), &sprite);
	entity_manager_set_component(play.manager, entity, cp_type(Transform), &trans);
	entity_manager_set_component(play.manager, entity, cp_type(Velocity), &vel);
	entity_archetype_free(arch);
}

bool kge_update() {
	kge_scene_update(ActiveScene);
	return RUNNING;
}

void kge_cleanup() {
	kge_scene_free(ActiveScene);
}
