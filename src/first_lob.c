
#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <glib-object.h> //g_type_init

#include "gfx/gfx_api.h"
#include "vob/scene.h"
#include "lob/api.h"
#include "lob/lobs.h"
#include "vob/vobs.h"
#include "util/regions.h"
#include "util/sigsegv.h"

/*
static Lob* create_lob(Region *reg)
{
	Lob *l;

	printf("create Lob\n");
	l = lob_vbox(reg);
	printf("create Lob\n");
	lob_vbox_add(reg, (LobBox *)l,
		     lob_rect(reg, lob_color(reg, 1.0, 0.5, 0.2)));
	printf("create Lob\n");
	int i; 
	for (i=30; i<51; i++) {
		UtilArray *fonts = lob_font_list(reg);
		printf("create Lob\n");
		LobBox *text =
			lob_font_text(reg, util_arr_get(fonts, i), 12, "The quick brown fox jumps over the lazy dog"); 
		lob_hbox_add(reg, text, lob_hglue()); 
		lob_vbox_add(reg, (LobBox *)l, (Lob*)text); 
		lob_vbox_add(reg, (LobBox *)l, lob_vglue()); 
	}
	lob_vbox_add(reg, (LobBox *)l,
		     lob_rect(reg, lob_color(reg, 1.0, 0.5, 0.2)));

	return l;
}
*/

static Lob* create_lob(Region *reg)
{
	Lob *l;

	printf("create Lob\n");
	l = lob_vbox(reg);
	lob_vbox_add(reg, (LobBox *)l,
		     lob_rect(reg, vob_color(reg, 1.0, 0.5, 0.2)));
	lob_vbox_add(reg, (LobBox *)l, (Lob*)lob_paper(reg, 2340l));
	//lob_rect(reg, lob_color(reg, 1.0, 1.0, 0.5)));
	lob_vbox_add(reg, (LobBox *)l,
		     lob_rect(reg, vob_color(reg, 1.0, 0.4, 0.2)));
	return l;
}

static void key_pressed()
{
	printf("KEY PRESSED...\n");
}

static void key_released()
{
	printf("KEY RELEASED...\n");
}

int main(int argc, char **argv) 
{
	struct gfx_window *win = gfx_create_window(0, 0, 2*320, 3*240);

	struct gfx_callbacks *cb = gfx_callbacks(win);
	cb->create_lob = &create_lob;
	cb->key_pressed = &key_pressed;
	cb->key_released = &key_released;

	g_type_init();
	setup_sigsegv();

	gfx_main_loop(win);
	return 0;
}
