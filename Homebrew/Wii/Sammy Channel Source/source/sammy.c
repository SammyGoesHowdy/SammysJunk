// Original code by emilydaemon, I just got permission to do a funny thing lol.

#include <grrlib.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <wiiuse/wpad.h>

#include "sammy_png.h"

extern void __exception_setreload(int);

GRRLIB_texImg* sammy_img;

int i;
int exitLoop = 0;

void exitsleep(int delay) {
	for (i = 0; i < delay; i++) {
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) {
			exitLoop = 1;
			break;
		}
		usleep(1);
	}
}

int main(int argc, char **argv) {
	__exception_setreload(4);

	GRRLIB_Init();

	WPAD_Init();

	sammy_img = GRRLIB_LoadTexture(sammy_png);

	while(1) {
		WPAD_ScanPads();

		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;

		GRRLIB_DrawImg(0, 0, sammy_img, 0, 1, 1, 0xFFFFFFFF);
		GRRLIB_Render();
	}
	GRRLIB_FreeTexture(sammy_img);
	GRRLIB_Exit();

	exit(0);
}
