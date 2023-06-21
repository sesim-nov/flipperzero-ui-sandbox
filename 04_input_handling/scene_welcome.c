#include "input_handling.h"

#include <gui/scene_manager.h>
#include <gui/canvas.h>

/*
 * This code is rn when the scene manager switches into this scene
 */
void scene_welcome_on_enter(void* ctx) {
    
    InputHandlingData* instance = ctx;

    dialog_ex_reset(instance->dialog_ex);

    dialog_ex_set_header(instance->dialog_ex, "Hello there.", 10, 10, AlignLeft, AlignTop);

    view_dispatcher_switch_to_view(instance->view_dispatcher, InputHandlingViewDialog);
}

bool scene_welcome_on_event(void* ctx, SceneManagerEvent event) {
    UNUSED(ctx);
    UNUSED(event);
    return false;
}

void scene_welcome_on_exit(void* ctx) {
    InputHandlingData* instance = ctx;

    dialog_ex_reset(instance->dialog_ex);
}
