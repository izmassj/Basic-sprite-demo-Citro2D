#include <citro2d.h>
#include <3ds.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

C2D_Sprite spr;
static C2D_SpriteSheet spriteSheet;

int main(int argc, char **argv) {
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    consoleInit(GFX_BOTTOM, NULL);

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
    if (!spriteSheet) svcBreak(USERBREAK_PANIC);

    C2D_SpriteFromSheet(&spr, spriteSheet, 0);
    C2D_SpriteSetPos(&spr, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    C2D_SpriteSetCenter(&spr, 0.5f, 0.5f);

    while(aptMainLoop()) {
        hidScanInput();

        if(hidKeysDown() & KEY_START) break;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32f(1.0f, 1.0f, 1.0f, 0.0f));
		C2D_SceneBegin(top);
        C2D_DrawSprite(&spr);
        C3D_FrameEnd(0);
    }

    C2D_SpriteSheetFree(spriteSheet);

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
}
