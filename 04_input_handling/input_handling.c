#include <furi.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>

/**
 * This structure tracks the main relevant information about the application.
 */
typedef struct {
    ViewDispatcher* view_dispatcher;
    //SceneManager* scene_manager;
} InputHandlingData;

/**
 * This lists all available views allocated to our view dispatcher. 
 */
typedef enum {
    InputHandlingViewDialog,
    InputHandlingViewTextInput,
    InputHandlingViewMAX
} InputHandlingViews;

/**
 * Allocates the memory for an InputHandlingData
 */
InputHandlingData* input_handling_data_alloc() {
    InputHandlingData* instance = malloc(sizeof(InputHandlingData));
    
    instance->view_dispatcher = view_dispatcher_alloc();

    //instance->scene_manager = scene_manager_alloc();

    return instance;
}

/**
 * Frees all data associated with this app. 
 */
void input_handling_data_free(InputHandlingData* instance) {
    view_dispatcher_free(instance->view_dispatcher);

    free(instance);
}

/**
 * Entry point for our program. 
 */
int input_handling_app() {
    InputHandlingData* app = input_handling_data_alloc();

    input_handling_data_free(app);
    return 0;
}
