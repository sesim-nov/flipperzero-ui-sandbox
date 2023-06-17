#include "my_file_browser.h"
#include "menu_integration.h"

bool my_file_browser_load_callback(
    FuriString* path,
    void* context,
    uint8_t** icon,
    FuriString* item_name) 
{
    UNUSED(context);
    UNUSED(icon);
    UNUSED(item_name);
    FURI_LOG_D("MENUINT", "File Path: %s", furi_string_get_cstr(path));
    return true;
}
void my_file_browser_callback(
    void* context)
{
    MenuIntegration* instance = context;
    FURI_LOG_D("MENUINT", "Second Callback called on path %s", furi_string_get_cstr(instance->file_browser_selected_path));
}

void my_file_browser_configure(
    FileBrowser* browser,
    const char* extension,
    const char* base_path, 
    bool skip_assets,
    bool hide_dot_files,
    const Icon* icon,
    bool hide_ext,
    void* context
    ){
    file_browser_configure(
	browser,
    	extension,
    	base_path, 
    	skip_assets,
    	hide_dot_files,
    	icon,
    	hide_ext);

    file_browser_set_item_callback(browser, my_file_browser_load_callback, context);
    file_browser_set_callback(browser, my_file_browser_callback, context);
}
