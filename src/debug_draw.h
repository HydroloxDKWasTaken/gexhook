#pragma once

namespace debug_draw {

void draw_obs();
void draw_info();
void draw_debug_data();

void debug_data_add_str(const char* a_str);

void debug_print(const char* a_format, ...);

} 
