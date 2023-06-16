#include <furi.h>
#include <gui/gui.h>
#include <gui/modules/submenu.h>
#include <gui/modules/submenu.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>

#include "menu.h"

// This is the model for the application. 
// It is a store for all of the data relevant to running our app. 
typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    SceneManager* scene_manager;
} MenuTest;

// List of views for the ViewDispatcher. 
// This is used to set indices in the init functions. 
typedef enum {
    MenuTestViewSubmenu,
} MenuTestView;

// "Navigation callbacks" handle back-arrow events.
// Returning false simply exits the program. 
bool view_dispatcher_navigation_event_callback(void* context) {
    UNUSED(context);

    return false;
}

// Allocate all of the fun things in our app. 
MenuTest* menu_test_alloc() {
    // Allocate the app struct itself
    MenuTest* instance = malloc(sizeof(MenuTest));

    // Open a gui record so we can draw on the display. 
    instance->gui = furi_record_open("gui");

    // Allocate our submenu
    instance->submenu = submenu_alloc();
    // Add menu items to our submenu. 
    menu_test_submenu_init(instance->submenu, instance);

    // Allocate our view dispatcher
    instance->view_dispatcher = view_dispatcher_alloc();
    // Add the submenu
    view_dispatcher_add_view(instance->view_dispatcher, 
	    MenuTestViewSubmenu, 
	    submenu_get_view(instance->submenu));
    // Enable the input messsage queue, which allows the view dispatcher to directly handle input events. 
    view_dispatcher_enable_queue(instance->view_dispatcher);
    view_dispatcher_attach_to_gui(instance->view_dispatcher, instance->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_switch_to_view(instance->view_dispatcher, MenuTestViewSubmenu);
    // Set view dispatcher's behavior when the back button is pressed. 
    view_dispatcher_set_navigation_event_callback(
	    instance->view_dispatcher, view_dispatcher_navigation_event_callback);

    return instance;
}

void menu_test_free(MenuTest* instance) {
    FURI_LOG_D("MENUTEST", "Closing gui record");
    furi_record_close("gui");
    
    view_dispatcher_remove_view(instance->view_dispatcher, MenuTestViewSubmenu);
    FURI_LOG_D("MENUTEST", "Freeing Dispatcher");
    view_dispatcher_free(instance->view_dispatcher);

    FURI_LOG_D("MENUTEST", "Freeing Submenu");
    submenu_free(instance->submenu);
}

int menu_test_app(void *p) {
    UNUSED(p);

    MenuTest* app = menu_test_alloc();

    FURI_LOG_D("MENUTEST", "Entering View Dispatcher");
    view_dispatcher_run(app->view_dispatcher);
    FURI_LOG_D("MENUTEST", "Exiting View Dispatcher");

    menu_test_free(app);

    int a = 0;
    return a; 
}
