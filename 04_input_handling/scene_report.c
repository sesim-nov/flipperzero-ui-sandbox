#include "input_handling.h"
#include "scenes.h"

#include <gui/scene_manager.h>
#include <gui/canvas.h>

/**
 * This is the callback function for the dialog. 
 */
void scene_report_dialog_result_callback(DialogExResult result, void* ctx) {
    InputHandlingData* instance = ctx;
    switch (result) {
        case DialogExResultLeft:
            scene_manager_previous_scene(instance->scene_manager);
            break;
        case DialogExResultRight:
            // Kill the view dispatcher, which ultimately exits the app. 
            view_dispatcher_stop(instance->view_dispatcher);
        default:
            break;
    }
}

/*
 * This code is run when the scene manager switches into this scene
 */
void scene_report_on_enter(void* ctx) {
    
    InputHandlingData* instance = ctx;

    dialog_ex_reset(instance->dialog_ex);

    dialog_ex_set_header(instance->dialog_ex, instance->model->input_text, 10, 10, AlignLeft, AlignTop);

    dialog_ex_set_result_callback(instance->dialog_ex, scene_report_dialog_result_callback);

    dialog_ex_set_left_button_text(instance->dialog_ex, "Go Back");
    dialog_ex_set_right_button_text(instance->dialog_ex, "Exit Application");

    dialog_ex_set_context(instance->dialog_ex, ctx);

    view_dispatcher_switch_to_view(instance->view_dispatcher, InputHandlingViewDialog);
}

bool scene_report_on_event(void* ctx, SceneManagerEvent event) {
    UNUSED(ctx);
    UNUSED(event);
    FURI_LOG_D("INPUTHANDLNG", "Got event!");
    return false;
}

void scene_report_on_exit(void* ctx) {
    FURI_LOG_D("InputHandling", "Entered Scene Report on Exit");
    InputHandlingData* instance = ctx;

    dialog_ex_reset(instance->dialog_ex);
}
