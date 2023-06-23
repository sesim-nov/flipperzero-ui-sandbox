#pragma once
/*
 * Pretty self explanatory, this header defines the scene manager 
 * interface for the "input" scene. 
 */

void scene_input_on_enter(void* ctx) ;

bool scene_input_on_event(void* ctx, SceneManagerEvent event) ;

void scene_input_on_exit(void* ctx) ;
