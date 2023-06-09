#include <stdbool.h>
#include <stdio.h>
#include "Components.h"
#include "Entities.h"
#include "EntityManager.h"
#include "kc/array.h"
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
	entity_archetype arch = entity_archetype_create(cp_type(Sprite), cp_type(Transform));
	entity_manager_add_entity(play.manager, arch);
	entity_archetype_free(arch);
}

bool kge_update() {
	kge_scene_update(ActiveScene);
	return RUNNING;
}

void kge_cleanup() {
	kge_scene_free(ActiveScene);
}