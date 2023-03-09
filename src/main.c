#include <stdbool.h>
#include <stdio.h>
#include "EntityManager.h"
#include "kc/array.h"
#include "tests.h"
#include "Scene.h"
#include "Config.h"

#if TARGET == TERMINAL
// Raw Mode
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

struct termios orig_termios;

void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
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

int main(void) {
	//run_tests();
	
#if TARGET == TERMINAL
	enable_raw_mode();
#endif

	kge_scene play = kge_scene_play_create();
	while(RUNNING) {
		kge_scene_update(play);
	}

	kge_scene_free(play);
}

