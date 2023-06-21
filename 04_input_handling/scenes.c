#include <gui/scene_manager.h>

#include "input_handling.h"
#include "scenes.h"
#include "scene_welcome.h"
/*
 * These lists contain the enter, event and exit handlers for each scene, 
 * posted in the order the scenes are defined in the InputHandlingScenes enum.
 */
const AppSceneOnEnterCallback input_handling_scene_enter_handlers[] = {scene_welcome_on_enter};
const AppSceneOnEventCallback input_handling_scene_event_handlers[] = {scene_welcome_on_event};
const AppSceneOnExitCallback input_handling_scene_exit_handlers[] = {scene_welcome_on_exit};

const SceneManagerHandlers input_handling_scene_manager_handlers = {
    .on_enter_handlers = input_handling_scene_enter_handlers,
    .on_event_handlers = input_handling_scene_event_handlers,
    .on_exit_handlers = input_handling_scene_exit_handlers,
    .scene_num = InputHandlingSceneMAX,
};

bool input_handling_scene_manager_custom_event_callback(void* context, uint32_t event) {
    InputHandlingData* app = context;

    return scene_manager_handle_custom_event(app->scene_manager, event);
}

bool input_handling_scene_manager_navigation_event_callback(void* context) {
    InputHandlingData* app = context;

    return scene_manager_handle_back_event(app->scene_manager);
}
