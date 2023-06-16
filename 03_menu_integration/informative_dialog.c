#include "informative_dialog.h"
#include "menu_integration.h"

#include <gui/view.h>

void dialog_result_callback(DialogExResult result, void* context) {
    MenuIntegration* instance = context;

    FURI_LOG_D("MENUINT", "Caught signal %i", result);
    if (result == DialogExResultLeft) {
	FURI_LOG_D("MENUINT", "Attempting to switch back to submenu");
	view_dispatcher_switch_to_view(instance->view_dispatcher, MenuIntegrationViewSubmenu);
    }
}

void informative_dialog_init(DialogEx* dialog, void* ctx){
	dialog_ex_set_context(dialog, ctx);

	FURI_LOG_D("MENUINT", "Setting dialog result callback...");
	dialog_ex_set_result_callback(dialog, dialog_result_callback);

	dialog_ex_set_left_button_text(dialog, "Menu");

	dialog_ex_set_header(
	    dialog,
	    "Hello Flipper",
	    16,
	    12,
	    AlignLeft,
	    AlignTop);

}
