#include <furi.h>

#include "input_handling.h"
#include "scenes.h"

InputHandlingModel* input_handling_model_alloc() {
    InputHandlingModel* instance = malloc(sizeof(InputHandlingModel));

    instance->input_text_size = 30 * sizeof(char);
    instance->input_text = malloc(instance->input_text_size);
    return instance;
}

void input_handling_model_free(InputHandlingModel* instance) {
    free(instance->input_text);
    free(instance);
}

/**
 * Allocates the memory for an InputHandlingData
 */
InputHandlingData* input_handling_data_alloc() {
    InputHandlingData* instance = malloc(sizeof(InputHandlingData));

    instance->model = input_handling_model_alloc();

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

    // Configure View Manager for use with a scene manager. 
    view_dispatcher_enable_queue(instance->view_dispatcher); // Enable the view dispatcher I/O queue. 
    view_dispatcher_set_event_callback_context(instance->view_dispatcher, instance); // Set the context all callbacks will use. 
    view_dispatcher_set_custom_event_callback(instance->view_dispatcher,
            input_handling_scene_manager_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(instance->view_dispatcher,
            input_handling_scene_manager_navigation_event_callback);


    instance->scene_manager = scene_manager_alloc(&input_handling_scene_manager_handlers, instance);

    return instance;
}

/**
 * Frees all data associated with this app. 
 */
void input_handling_data_free(InputHandlingData* instance) {
    input_handling_model_free(instance->model);
    view_dispatcher_remove_view(instance->view_dispatcher, InputHandlingViewTextInput);
    view_dispatcher_remove_view(instance->view_dispatcher, InputHandlingViewDialog);

    view_dispatcher_free(instance->view_dispatcher);

    dialog_ex_free(instance->dialog_ex);
    text_input_free(instance->text_input);

    scene_manager_free(instance->scene_manager);

    free(instance);
}

/**
 * Entry point for our program. 
 */
int input_handling_app() {
    InputHandlingData* app = input_handling_data_alloc();

    // Attach to gui. Could do this in alloc function too...
    Gui* gui = furi_record_open("gui");
    view_dispatcher_attach_to_gui(app->view_dispatcher, gui, ViewDispatcherTypeFullscreen);

    //Start scene manager
    scene_manager_next_scene(app->scene_manager, InputHandlingSceneWelcome);

    //Start view dispatcher
    view_dispatcher_run(app->view_dispatcher);

    furi_record_close("gui");
    input_handling_data_free(app);
    return 0;
}
