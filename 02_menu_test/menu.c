#include "menu.h"


void dummy_handler(void* ctx, uint32_t index) {
    UNUSED(ctx);
    UNUSED(index);
}

void menu_test_submenu_init(Submenu* submenu, void* ctx) {
    submenu_add_item(
	submenu,
	"Sesim wuz here",
	MainMenuItemSesim,
	dummy_handler,
	ctx
    );		
    submenu_add_item(
	submenu,
	"Hello Flipper",
	MainMenuItemHello,
	dummy_handler,
	ctx
    );		
}
