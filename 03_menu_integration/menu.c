#include "menu.h"
#include "menu_integration.h"


void select_handler(void* ctx, uint32_t index) {
    UNUSED(ctx);
    if (index == MainMenuItemDialog) {
	FURI_LOG_D("MENUINT", "Handler fired for dialog.");
    }
}

void menu_integration_submenu_init(Submenu* submenu, void* ctx) {
    submenu_add_item(
	submenu,
	"Display Dialog",
	MainMenuItemDialog,
	select_handler,
	ctx
    );		
    submenu_add_item(
	submenu,
	"Display File Browser",
	MainMenuItemFileBrowser,
	select_handler,
	ctx
    );		
}
