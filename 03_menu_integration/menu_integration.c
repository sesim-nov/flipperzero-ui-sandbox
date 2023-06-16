
#include "menu.h"
#include "menu_integration.h"

// List of views for the ViewDispatcher. 
// This is used to set indices in the init functions. 
typedef enum {
    MenuTestViewSubmenu,
    MenuTestViewDialog,
    MenuTestViewMAX,
} MenuTestView;

// "Navigation callbacks" handle back-arrow events.
// Returning false simply exits the program. 
bool view_dispatcher_navigation_event_callback(void* context) {
    UNUSED(context);

    return false;
}

// Allocate all of the fun things in our app. 
MenuTest* menu_integration_alloc() {
    // Allocate the app struct itself
    MenuTest* instance = malloc(sizeof(MenuTest));

    // Open a gui record so we can draw on the display. 
    instance->gui = furi_record_open("gui");

    // Allocate our submenu
    instance->submenu = submenu_alloc();
    // Add menu items to our submenu. 
    menu_integration_submenu_init(instance->submenu, instance);

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

// Deallocate everything we included in our model. 
// The idea here is to follow the one-free-per-alloc rule. 
void menu_integration_free(MenuTest* instance) {
    // Close down our link to the GUI. 
    // Still shaky on exactly what a furi record is. 
    FURI_LOG_D("MENUTEST", "Closing gui record");
    furi_record_close("gui");
    
    // I discovered that if you fail to remove the view prior to
    // deallocating the dispatcher, the program will hang. 
    // One day I'll debug to find out exactly why that happens. 
    view_dispatcher_remove_view(instance->view_dispatcher, MenuTestViewSubmenu);
    FURI_LOG_D("MENUTEST", "Freeing Dispatcher");
    view_dispatcher_free(instance->view_dispatcher);

    FURI_LOG_D("MENUTEST", "Freeing Submenu");
    submenu_free(instance->submenu);
}

int menu_integration_app(void *p) {
    UNUSED(p);

    // Allocate our app
    MenuTest* app = menu_integration_alloc();

    // Actually start the view dispatcher. This is the line that actually 
    // starts the main loop of the program. 
    FURI_LOG_D("MENUTEST", "Entering View Dispatcher");
    view_dispatcher_run(app->view_dispatcher);
    FURI_LOG_D("MENUTEST", "Exiting View Dispatcher");

    // Deallocate our app
    menu_integration_free(app);

    int a = 0;
    return a; 
}
