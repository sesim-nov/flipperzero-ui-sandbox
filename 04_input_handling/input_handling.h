#pragma once

#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/text_input.h>

typedef struct {
    char* input_text;
    size_t input_text_size;
} InputHandlingModel;


/**
 * This structure tracks the main relevant information about the application.
 */
typedef struct {
    InputHandlingModel* model;

    ViewDispatcher* view_dispatcher;
    
    //View Dispatcher Views
    TextInput* text_input;
    DialogEx* dialog_ex;

    SceneManager* scene_manager;
} InputHandlingData;

/**
 * This lists all available views allocated to our view dispatcher. 
 */
typedef enum {
    InputHandlingViewDialog,
    InputHandlingViewTextInput,
    InputHandlingViewMAX
} InputHandlingViews;
