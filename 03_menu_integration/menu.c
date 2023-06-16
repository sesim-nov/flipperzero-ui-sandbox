#include "menu.h"


void dummy_handler(void* ctx, uint32_t index) {
    UNUSED(ctx);
    UNUSED(index);
}

void menu_integration_submenu_init(Submenu* submenu, void* ctx) {
    submenu_add_item(
	submenu,
	"Display Dialog",
	MainMenuItemDialog,
	dummy_handler,
	ctx
    );		
    submenu_add_item(
	submenu,
	"Display File Browser",
	MainMenuItemFileBrowser,
	dummy_handler,
	ctx
    );		
}
