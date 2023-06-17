#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/modules/submenu.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/file_browser.h>

// This is the model for the application. 
// It is a store for all of the data relevant to running our app. 
typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    DialogEx* dialog;
    FileBrowser* file_browser;
} MenuIntegration;

// List of views for the ViewDispatcher. 
// This is used to set indices in the init functions. 
typedef enum {
    MenuIntegrationViewSubmenu,
    MenuIntegrationViewDialog,
    MenuIntegrationViewFileBrowser,
    MenuIntegrationViewMAX,
} MenuIntegrationView;
