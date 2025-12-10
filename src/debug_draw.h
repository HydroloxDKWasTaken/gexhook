#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

namespace debug_draw
{

void draw_obs( );
void draw_info( );
void draw_debug_data( );

void debug_data_add_str( const char* a_str );

void debug_print( const char* a_format, ... );

} // namespace debug_draw

#endif // DEBUG_DRAW_H
