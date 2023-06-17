# Modules in Flipper Zero Graphics

This document will contain notes and other usiful information about the graphics API modules as I use them. 

## Modules in General

Most modules have a set of tasks associated with them. They follow a naming convention that helps standardise the interface between different modules. The naming convention is simply: 

```
$MODULE_NAME_$ACTIVITY
```

Some common ones shared by most modules are shown below: 

### Allocating a module instance

To allocate most modules, call: 

```
$MODULE_NAME_alloc();
```

### Freeing a module instance

To free most modules, call: 

```
$MODULE_NAME_free(module_instance);
```

This will free everything constructed by the alloc function. 

### Getting the view

To retrieve the view associated with a given module, call:

```
$MODULE_NAME_get_view(module_instance);
```

This will get the associated view for the module, which can be added to a View Dispatcher and made available to the gui to draw. 

## Life Cycle of a module:

The overall lifecycle of a module is listed below. This tracks the module from creation to destruction. 

1. Allocation: The module is allocated using its associated helper function
2. Initialization: The modules various parameters are set to represent a fully populated interface to display to the user. 
3. Registration: The module instance is added to a view dispatcher, which makes it available for use by calling `view_dispatcher_switch_to_view`, likely inside of some input handling callback or another. 
4. Scene Management: The module is used as part of a Scene Manager (I haven't done any scene manager work yet so this is a placeholder). 
5. Deregistration: The module instance is disconnected from the view dispatcher. 
6. Deallocation: The memory containing the module is freed. 


## Dialog

The dialog is as its name implies. It is a full-screen notification with the ability to add interactions on the left, right and center buttons. 

### Contained in: 

```
$FIRMWARE_ROOT/applications/services/gui/modules/dialog_ex.h
```

### To allocate

```
DialogEx* dialog = dialog_ex_alloc()
```

### Draw-related functions

To set the header text, use: 

```
dialog_ex_set_header
```

The positioning functions and alignement arguments i sitll need to work out how to use. When I used 0,0 for my position and center for both alignments, the header didn't draw. 

To set the button labels, use: 

```
dialog_ex_set_center_button_text
```

There are similar functions for left and right buttons also. 
It is worth noting that if a label for a given direction isn't defined, the associated input event is ignored and your callbacks won't be called. In order to use a given button in the dialog, you have to define a label for it. 
