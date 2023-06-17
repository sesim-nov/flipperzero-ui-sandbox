#pragma once

#include <gui/modules/file_browser.h>


void my_file_browser_configure(
    FileBrowser* browser,
    const char* extension,
    const char* base_path, 
    bool skip_assets,
    bool hide_dot_files,
    const Icon* icon,
    bool hide_ext,
    void* context
    );
