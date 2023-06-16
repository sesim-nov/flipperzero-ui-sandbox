#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/modules/submenu.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>


// This is the model for the application. 
// It is a store for all of the data relevant to running our app. 
typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    SceneManager* scene_manager;
} MenuTest;
