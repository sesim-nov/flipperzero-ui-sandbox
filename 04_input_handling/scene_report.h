#pragma once
/*
 * Pretty self explanatory, this header defines the scene manager 
 * interface for the "report" scene. 
 */

void scene_report_on_enter(void* ctx) ;

bool scene_report_on_event(void* ctx, SceneManagerEvent event) ;

void scene_report_on_exit(void* ctx) ;
