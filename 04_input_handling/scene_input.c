#include "input_handling.h"
#include "scenes.h"
void scene_input_result_callback(void* ctx) {
    InputHandlingData* instance = ctx;

    scene_manager_next_scene(instance->scene_manager, InputHandlingSceneReport);
}

void scene_input_on_enter(void* ctx) {
    FURI_LOG_D("InputHandling", "Entered Scene Input On Enter");
    InputHandlingData* instance = ctx; 

    text_input_reset(instance->text_input);

    text_input_set_result_callback(instance->text_input, 
            scene_input_result_callback, 
            instance, 
            instance->model->input_text, 
            instance->model->input_text_size,
            true);

    text_input_set_header_text(instance->text_input, "Gimme some text.");

    view_dispatcher_switch_to_view(instance->view_dispatcher, InputHandlingViewTextInput);
}

bool scene_input_on_event(void* ctx, SceneManagerEvent event) {
    UNUSED(ctx);
    UNUSED(event);
    return false;
}

void scene_input_on_exit(void* ctx) {
    InputHandlingData* instance = ctx;

    text_input_reset(instance->text_input);
}
