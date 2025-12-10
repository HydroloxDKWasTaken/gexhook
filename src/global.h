#ifndef GLOBAL_H
#define GLOBAL_H

#define GEX_POS( x ) ( ( x ) << 16 )
#define GEX_POS_SCREEN_INDEX( x ) ( ( x ) >> 0x18 )
#define GEX_POS_SCREEN_ROW_INDEX( x ) ( ( ( x ) >> 0x15 ) & 7 )

inline bool free_camera_mode = false;
inline int free_camera_x = -1;
inline int free_camera_y = -1;
inline int free_camera_restore_x = -1;
inline int free_camera_restore_y = -1;
inline int ob_debug_draw_flags = 0;
inline int ob_debug_draw_filter_by_type = -1;
inline constexpr int k_ob_debug_draw_types = 1 << 0;
inline constexpr int k_ob_debug_draw_layer = 1 << 1;
inline constexpr int k_ob_debug_draw_cldprio = 1 << 2;
inline constexpr int k_ob_debug_draw_cldtype = 1 << 3;
inline constexpr int k_ob_debug_draw_work0 = 1 << 4;
inline constexpr int k_ob_debug_draw_work1 = 1 << 5;
inline constexpr int k_ob_debug_draw_work2 = 1 << 6;
inline constexpr int k_ob_debug_draw_work3 = 1 << 7;
inline constexpr int k_ob_debug_draw_work4 = 1 << 8;
inline constexpr int k_ob_debug_draw_work5 = 1 << 9;
inline constexpr int k_ob_debug_draw_work6 = 1 << 10;
inline constexpr int k_ob_debug_draw_work7 = 1 << 11;
inline constexpr int k_ob_debug_ignore_common_ob_types = 1 << 30;
inline bool should_draw_debug_data = false;

inline constexpr int k_stats_short = 1 << 0;
inline constexpr int k_stats_long = 1 << 1;
inline int stats_flags = 0;

#endif // GLOBAL_H
