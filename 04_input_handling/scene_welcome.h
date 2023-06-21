#pragma once
/*
 * Pretty self explanatory, this header defines the scene manager 
 * interface for the "welcome" scene. 
 */

void scene_welcome_on_enter(void* ctx) ;

bool scene_welcome_on_event(void* ctx, SceneManagerEvent event) ;

void scene_welcome_on_exit(void* ctx) ;
