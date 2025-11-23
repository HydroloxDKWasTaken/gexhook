#pragma once
#include "debug_menu.h"
#include "game.h"
#include "global.h"

namespace debug_menu {

inline extern std::array<dm_line, 14> level_select_menu;
inline extern std::array<dm_line, 16> main_menu;

inline auto grave_menu =
    menu_builder<9>()
        .add_menu("level select...", level_select_menu)
        .add_action("grave1", actions::goto_level, 0)
        .add_action("grave2", actions::goto_level, 1)
        .add_action("grave3", actions::goto_level, 2)
        .add_action("grave4", actions::goto_level, 3)
        .add_action("grave5 (unused)", actions::goto_level, 4)
        .add_action("grave6 (unused)", actions::goto_level, 5)
        .add_action("grave7 (boss)", actions::goto_level, 6)
        .build();

inline auto cartoon_menu =
    menu_builder<9>()
        .add_menu("level select...", level_select_menu)
        .add_action("cartoon1", actions::goto_level, 7)
        .add_action("cartoon2", actions::goto_level, 8)
        .add_action("cartoon3", actions::goto_level, 9)
        .add_action("cartoon4", actions::goto_level, 10)
        .add_action("cartoon5", actions::goto_level, 11)
        .add_action("cartoon6 (unused)", actions::goto_level, 12)
        .add_action("cartoon7 (boss)", actions::goto_level, 13)
        .build();

inline auto jungle_menu =
    menu_builder<9>()
        .add_menu("level select...", level_select_menu)
        .add_action("jungle1 (unused)", actions::goto_level, 14)
        .add_action("jungle2", actions::goto_level, 15)
        .add_action("jungle3", actions::goto_level, 16)
        .add_action("jungle4 (unused)", actions::goto_level, 17)
        .add_action("jungle5 (unused)", actions::goto_level, 18)
        .add_action("jungle6 (unused)", actions::goto_level, 19)
        .add_action("jungle7 (boss)", actions::goto_level, 20)
        .build();

inline auto rez_menu =
    menu_builder<9>()
        .add_menu("level select...", level_select_menu)
        .add_action("rez1", actions::goto_level, 21)
        .add_action("rez2", actions::goto_level, 22)
        .add_action("rez3", actions::goto_level, 23)
        .add_action("rez4", actions::goto_level, 24)
        .add_action("rez5", actions::goto_level, 25)
        .add_action("rez6", actions::goto_level, 26)
        .add_action("rez7 (boss)", actions::goto_level, 27)
        .build();

inline auto scifi_menu =
    menu_builder<6>()
        .add_menu("level select...", level_select_menu)
        .add_action("scifi1", actions::goto_level, 28)
        .add_action("scifi2", actions::goto_level, 29)
        .add_action("scifi3", actions::goto_level, 30)
        .add_action("scifi4", actions::goto_level, 31)
        .build();

inline auto kungfu_menu =
    menu_builder<6>()
        .add_menu("level select...", level_select_menu)
        .add_action("kungfu1", actions::goto_level, 35)
        .add_action("kungfu2", actions::goto_level, 36)
        .add_action("kungfu3", actions::goto_level, 37)
        .add_action("kungfu4", actions::goto_level, 38)
        .build();

inline auto mainmap_menu =
    menu_builder<9>()
        .add_menu("level select...", level_select_menu)
        .add_action("mainmap1 (grave)", actions::goto_level, 49)
        .add_action("mainmap2 (cartoon)", actions::goto_level, 50)
        .add_action("mainmap3 (jungle)", actions::goto_level, 51)
        .add_action("mainmap4 (rez)", actions::goto_level, 52)
        .add_action("mainmap5 (scifi)", actions::goto_level, 53)
        .add_action("mainmap6 (kungfu)", actions::goto_level, 54)
        .add_action("mainmap7 (main dome)", actions::goto_level, 55)
        .build();

inline auto bonus_menu =
    menu_builder<9>()
        .add_menu("level select...", level_select_menu)
        .add_action("bonus1 (jungle)", actions::goto_level, 56)
        .add_action("bonus2 (grave)", actions::goto_level, 57)
        .add_action("bonus3 (rez)", actions::goto_level, 58)
        .add_action("bonus4 (kungfu)", actions::goto_level, 59)
        .add_action("bonus5 (cartoon, secret)", actions::goto_level, 60)
        // .add_action( "bonus6 (unused)",  actions::goto_level, 61 ) - crashes the game
        .add_action("bonus7", actions::goto_level, 62)
        .build();

inline auto secret_menu =
    menu_builder<5>()
        .add_menu("level select...", level_select_menu)
        .add_action("sl67", actions::goto_level, 136)
        .add_action("sl68", actions::goto_level, 137)
        .add_action("sl69", actions::goto_level, 138)
        .build();

inline auto level_select_menu =
    menu_builder<14>()
        .add_menu("main menu...", main_menu)
        .add_int_ref("level to goto", &level_to_goto)
        .add_action("goto level", actions::goto_specific_level)
        .add_menu("grave menu...", grave_menu)
        .add_menu("cartoon menu...", cartoon_menu)
        .add_menu("jungle menu...", jungle_menu)
        .add_menu("rez menu...", rez_menu)
        .add_menu("scifi menu...", scifi_menu)
        .add_menu("kungfu menu...", kungfu_menu)
        .add_menu("mainmap menu...", mainmap_menu)
        .add_menu("bonus menu...", bonus_menu)
        .add_menu("secret menu...", secret_menu)
        .build();

inline auto cheats_menu =
    menu_builder<5>()
        .add_menu("main menu...", main_menu)
        .add_action("unlock levels on current map", actions::do_cheat, 0x0)
        .add_action("level select", actions::do_cheat, 0x1)
        .add_action("99 lives", actions::do_cheat, 0x2)
        .build();

inline auto sound_menu =
    menu_builder<5>()
        .add_menu("main menu...", main_menu)
        .add_bool_ref("sfx", &gEnableSFX)
        .add_bool_ref("vfx", &gEnableVFX)
        .add_bool_ref("music", &gEnableMUS)
        .build();

inline auto debug_draw_menu =
    menu_builder<16>()
        .add_menu("main menu...", main_menu)
        .add_flag("ob types", &ob_debug_draw_flags, k_ob_debug_draw_types)
        .add_flag("ignore common ob types", &ob_debug_draw_flags, k_ob_debug_ignore_common_ob_types)
        .add_int_ref("ob filter type", &ob_debug_draw_filter_by_type)
        .add_flag("ob layer", &ob_debug_draw_flags, k_ob_debug_draw_layer)
        .add_flag("ob cldprio", &ob_debug_draw_flags, k_ob_debug_draw_cldprio)
        .add_flag("ob cldtype", &ob_debug_draw_flags, k_ob_debug_draw_cldtype)
        .add_flag("ob work0", &ob_debug_draw_flags, k_ob_debug_draw_work0)
        .add_flag("ob work1", &ob_debug_draw_flags, k_ob_debug_draw_work1)
        .add_flag("ob work2", &ob_debug_draw_flags, k_ob_debug_draw_work2)
        .add_flag("ob work3", &ob_debug_draw_flags, k_ob_debug_draw_work3)
        .add_flag("ob work4", &ob_debug_draw_flags, k_ob_debug_draw_work4)
        .add_flag("ob work5", &ob_debug_draw_flags, k_ob_debug_draw_work5)
        .add_flag("ob work6", &ob_debug_draw_flags, k_ob_debug_draw_work6)
        .add_flag("ob work7", &ob_debug_draw_flags, k_ob_debug_draw_work7)
        .build();

inline auto main_menu =
    menu_builder<16>()
        .add_flag("short stats", &stats_flags, k_stats_short)
        .add_flag("long stats", &stats_flags, k_stats_long)
        .add_bool_ref("free camera with ijkl", &free_camera_mode)
        .add_bool_ref("draw debug data", &should_draw_debug_data)
        .add_menu("debug draw menu...", debug_draw_menu)
        .add_menu("level select menu...", level_select_menu)
        .add_menu("cheats menu...", cheats_menu)
        .add_menu("sound menu...", sound_menu)
        .build();

} // namespace debug_menu
