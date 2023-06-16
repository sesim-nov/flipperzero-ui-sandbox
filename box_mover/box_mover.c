#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} BoxMoverModel; 

typedef struct {
    BoxMoverModel* model;
    FuriMutex* model_mutex;
    
    FuriMessageQueue* event_queue;

    ViewPort* view_port;
    Gui* gui;
} BoxMover;

void draw_callback(Canvas* canvas, void* ctx) {
    BoxMover* box_mover = ctx;
    furi_check(furi_mutex_acquire(box_mover->model_mutex, FuriWaitForever) == FuriStatusOk);

    canvas_draw_box(canvas, box_mover->model->x, box_mover->model->y, 4, 4);

    furi_mutex_release(box_mover->model_mutex);
}

void input_callback(InputEvent* input, void* ctx) {
    BoxMover* box_mover = ctx;

    furi_message_queue_put(box_mover->event_queue, input, FuriWaitForever);
}

// Allocate the Struct

BoxMover* box_mover_alloc() {
    BoxMover* instance = malloc(sizeof(BoxMover));

    instance->model = malloc(sizeof(BoxMoverModel));
    instance->model->x = 10;
    instance->model->y = 10;

    instance->model_mutex = furi_mutex_alloc(FuriMutexTypeNormal);

    instance->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    instance->view_port = view_port_alloc();
    view_port_draw_callback_set(instance->view_port, draw_callback, instance);
    view_port_input_callback_set(instance->view_port, input_callback, instance);

    instance->gui = furi_record_open("gui");
    gui_add_view_port(instance->gui, instance->view_port, GuiLayerFullscreen);

    return instance;
}

void box_mover_free(BoxMover* instance) {
    view_port_enabled_set(instance->view_port, false);
    gui_remove_view_port(instance->gui, instance->view_port);
    furi_record_close("gui");
    view_port_free(instance->view_port);

    furi_message_queue_free(instance->event_queue);

    furi_mutex_free(instance->model_mutex);

    free(instance->model);
    free(instance);
}

int32_t box_mover_app(void* p) {
    UNUSED(p);
    BoxMover* box_mover = box_mover_alloc();

    InputEvent event;
    
    bool processing = true;
    while(processing) {
        FuriStatus status = furi_message_queue_get(box_mover->event_queue, &event, 100);
        furi_check(furi_mutex_acquire(box_mover->model_mutex, FuriWaitForever) == FuriStatusOk);
        if (status == FuriStatusOk) {
            if (event.type == InputTypePress) {
                switch(event.key) {
                    case InputKeyUp:
                        box_mover->model->y -= 2;
                        break;
                    case InputKeyDown:
                        box_mover->model->y += 2;
                        break;
                    case InputKeyLeft:
                        box_mover->model->x -= 2;
                        break;
                    case InputKeyRight:
                        box_mover->model->x += 2;
                        break;
                    case InputKeyBack:
                        processing = false;
		    case InputKeyOk:
			break;
		    case InputKeyMAX:
			break;
                }
            }
        }
        furi_mutex_release(box_mover->model_mutex);
        view_port_update(box_mover->view_port);
    }
    
    box_mover_free(box_mover);
    return 0;
}
