#include "menu.h"
#include "menu_integration.h"


void select_handler(void* ctx, uint32_t index) {
    FURI_LOG_D("MENUINT", "Entered menu handler");

    MenuIntegration* instance = ctx;

    if (index == MainMenuItemDialog) {
	view_dispatcher_switch_to_view(
            instance->view_dispatcher,
            MenuIntegrationViewDialog);	
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
