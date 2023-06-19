#include <furi.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>


typedef struct {
    ViewDispatcher* view_dispatcher;
    //SceneManager* scene_manager;
} InputHandling;

InputHandling* input_handling_alloc() {
    InputHandling* instance = malloc(sizeof(InputHandling));
    
    instance->view_dispatcher = view_dispatcher_alloc();

    //instance->scene_manager = scene_manager_alloc();

    return instance;
}

void input_handling_free(InputHandling* instance) {
    view_dispatcher_free(instance->view_dispatcher);

    free(instance);
}

int input_handling_app() {
    InputHandling* app = input_handling_alloc();

    input_handling_free(app);
    return 0;
}
