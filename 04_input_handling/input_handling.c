#include <furi.h>

#include "input_handling.h"

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

    instance->dialog_ex = dialog_ex_alloc();
    instance->text_input = text_input_alloc();
    
    instance->view_dispatcher = view_dispatcher_alloc();
    // Add views to dispatcher
    view_dispatcher_add_view(
            instance->view_dispatcher, 
            InputHandlingViewDialog, 
            dialog_ex_get_view(instance->dialog_ex));
    view_dispatcher_add_view(
            instance->view_dispatcher, 
            InputHandlingViewTextInput, 
            text_input_get_view(instance->text_input));


    //instance->scene_manager = scene_manager_alloc();

    return instance;
}

/**
 * Frees all data associated with this app. 
 */
void input_handling_data_free(InputHandlingData* instance) {
    view_dispatcher_remove_view(instance->view_dispatcher, InputHandlingViewTextInput);
    view_dispatcher_remove_view(instance->view_dispatcher, InputHandlingViewDialog);

    view_dispatcher_free(instance->view_dispatcher);

    dialog_ex_free(instance->dialog_ex);
    text_input_free(instance->text_input);

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
