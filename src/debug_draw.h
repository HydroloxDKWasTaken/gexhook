#pragma once
#include <cstdio>

namespace debug_draw {

void draw_obs();
void draw_info();
void draw_debug_data();

void debug_data_add_str(const char* a_str);

template <typename... Args>
inline void debug_print(const char* a_format, Args... args) {
    char buf[256];
    std::snprintf(buf, sizeof buf, a_format, args);
    debug_data_add_str(buf);
}

} 
