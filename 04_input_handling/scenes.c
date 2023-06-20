#include <gui/scene_manager.h>

#include "scenes.h"
/*
 * These lists contain the enter, event and exit handlers for each scene, 
 * posted in the order the scenes are defined in the InputHandlingScenes enum.
 */
const AppSceneOnEnterCallback input_handling_scene_enter_handlers[] = {};
const AppSceneOnEventCallback input_handling_scene_event_handlers[] = {};
const AppSceneOnExitCallback input_handling_scene_exit_handlers[] = {};

const SceneManagerHandlers input_handling_scene_manager_handlers = {
    .on_enter_handlers = input_handling_scene_enter_handlers,
    .on_event_handlers = input_handling_scene_event_handlers,
    .on_exit_handlers = input_handling_scene_exit_handlers,
    .scene_num = InputHandlingSceneMAX,
};
