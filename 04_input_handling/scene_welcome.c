#include "input_handling.h"
#include "scenes.h"

#include <gui/scene_manager.h>
#include <gui/canvas.h>

void scene_welcome_dialog_result_callback(DialogExResult result, void* ctx) {
    UNUSED(result);
    InputHandlingData* instance = ctx;
    FURI_LOG_D("INPUTHANDLING", "Callback hit");
    scene_manager_next_scene(instance->scene_manager, InputHandlingSceneInput);
}

/*
 * This code is rn when the scene manager switches into this scene
 */
void scene_welcome_on_enter(void* ctx) {
    
    InputHandlingData* instance = ctx;

    dialog_ex_reset(instance->dialog_ex);

    dialog_ex_set_header(instance->dialog_ex, "Hello there.", 10, 10, AlignLeft, AlignTop);

    dialog_ex_set_result_callback(instance->dialog_ex, scene_welcome_dialog_result_callback);

    dialog_ex_set_right_button_text(instance->dialog_ex, "Go");

    dialog_ex_set_context(instance->dialog_ex, ctx);

    view_dispatcher_switch_to_view(instance->view_dispatcher, InputHandlingViewDialog);
}

bool scene_welcome_on_event(void* ctx, SceneManagerEvent event) {
    UNUSED(ctx);
    UNUSED(event);
    FURI_LOG_D("INPUTHANDLNG", "Got event!");
    return false;
}

void scene_welcome_on_exit(void* ctx) {
    FURI_LOG_D("InputHandling", "Entered Scene Welcome on Exit");
    InputHandlingData* instance = ctx;

    dialog_ex_reset(instance->dialog_ex);
}
