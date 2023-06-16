#pragma once

#include <gui/modules/submenu.h>

typedef enum {
    MainMenuItemSesim,
    MainMenuItemHello,
} MainMenuItem;

void menu_test_submenu_init(Submenu* submenu, void* ctx);
