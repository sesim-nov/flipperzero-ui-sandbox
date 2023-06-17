#pragma once

#include <gui/modules/submenu.h>

typedef enum {
    MainMenuItemDialog,
    MainMenuItemFileBrowser,
} MainMenuItem;

void menu_integration_submenu_init(Submenu* submenu, void* ctx);
