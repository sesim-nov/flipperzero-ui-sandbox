#pragma once

/**
 *  This lists all of the available scenes. 
 *  It also defines the ORDER in which they are referenced and how the 
 *  callbacks are listed in the callback structure. 
 */
typedef enum {
    InputHandlingSceneWelcome,
//    InputHandlingSceneEntry,
//    InputHandlingSceneReport,
    InputHandlingSceneMAX,
} InputHandlingScenes;

/**
 * This is the callback structure used to initialize the scene manager. 
 * It holds references to all of the callbacks for all of the scenes 
 * that comprise our application. 
 */
extern const SceneManagerHandlers input_handling_scene_manager_handlers;

/**
 * These two functions help us hook the event system from the view dispatcher into the scene manager.
 * They adapt the signature of the event callbacks from ViewDispatcher to that of the required 
 * SceneManager event handlers. 
 */
bool input_handling_scene_manager_navigation_event_callback(void* context);
bool input_handling_scene_manager_custom_event_callback(void* context, uint32_t event);
