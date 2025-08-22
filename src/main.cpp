#include "GEX.H"
#include "hook.h"
#include <bit>
#include <cstdarg>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>

#define GEX_POS(x) ((x) << 16)
#define GX_FUN(addr, ret, name, ...) \
    inline ret (*name)(__VA_ARGS__) = (ret (*)(__VA_ARGS__))addr;

GX_FUN( 0x0043fa70, void, TXT_DrawPrintP, int x, int y, const char* text );
GX_FUN( 0x0043faa0, void, TXT_DrawPrintF, int x, int y, const char* text, ... );
GX_FUN( 0x0043fae0, int, TXT_PixelLength, const char* text );

GX_FUN( 0x00444800, void, DrawRectMaybe, int ignored, int x1, int y1, int x2, int y2, std::uint32_t color, std::uint32_t pixc );

inline auto& gCurrentVK = *(int*) 0x00487fd4;
inline auto& gNoProcess = *(int*) 0x00455c4c;
inline auto& gTimer = *(int*) 0x004a2ac8;
inline auto& level = *(int*) 0x004a2964;
inline auto& CAMERA_XPos = *(int*) 0x004a2a38;
inline auto& CAMERA_YPos = *(int*) 0x004a2a1c;
inline auto& gObjectLists = *(ListType (*)[10]) 0x004a28a0;
inline auto& gCurrentCheatCode = *(int*) 0x00455b38;
inline auto& gEnableSFX = *(int*) 0x00455c08;
inline auto& gEnableVFX = *(int*) 0x00455c0c;
inline auto& gEnableMUS = *(int*) 0x00455c10;
inline auto& gNumFreeBlocks = *(int*) 0x004a2924;
inline auto& M1_004a2a80 = *(int*) 0x004a2a80;

enum class debug_menu_type
{
    dmt_action,
    dmt_menu,
    dmt_int,
    dmt_bool,
    dmt_flag,
    dmt_endmenu
};

struct debug_menu_line;
using on_activate_func = void (*)( debug_menu_line* );

struct debug_menu_line
{
    debug_menu_type type;
    const char* text;
    int* var;
    int data1;
};
#define DMT_ACTION(text, func, arg) debug_menu_line{debug_menu_type::dmt_action, text, (int*)func, arg}
#define DMT_MENU(text, menu) debug_menu_line{debug_menu_type::dmt_menu, text, (int*)menu, 0}
#define DMT_INT(text, var) debug_menu_line{debug_menu_type::dmt_int, text, var, 0}
#define DMT_BOOL(text, var) debug_menu_line{debug_menu_type::dmt_bool, text, (int*)var, 0}
#define DMT_FLAG(text, var, flag) debug_menu_line{debug_menu_type::dmt_flag, text, (int*)var, flag}
#define DMT_ENDMENU debug_menu_line{debug_menu_type::dmt_endmenu, nullptr, nullptr, 0}

void goto_level( debug_menu_line* a_line )
{
    level = a_line->data1;
}
int level_to_goto = 0;
void goto_specific_level( debug_menu_line* a_line )
{
    level = level_to_goto;
    level_to_goto = 0;
}

extern debug_menu_line level_select_menu[];
debug_menu_line grave_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "grave1", goto_level, 0 ),
    DMT_ACTION( "grave2", goto_level, 1 ),
    DMT_ACTION( "grave3", goto_level, 2 ),
    DMT_ACTION( "grave4", goto_level, 3 ),
    DMT_ACTION( "grave5 (unused)", goto_level, 4 ),
    DMT_ACTION( "grave6 (unused)", goto_level, 5 ),
    DMT_ACTION( "grave7 (boss)", goto_level, 6 ),
    DMT_ENDMENU
};
debug_menu_line cartoon_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "cartoon1", goto_level, 7 ),
    DMT_ACTION( "cartoon2", goto_level, 8 ),
    DMT_ACTION( "cartoon3", goto_level, 9 ),
    DMT_ACTION( "cartoon4", goto_level, 10 ),
    DMT_ACTION( "cartoon5", goto_level, 11 ),
    DMT_ACTION( "cartoon6 (unused)", goto_level, 12 ),
    DMT_ACTION( "cartoon7 (boss)", goto_level, 13 ),
    DMT_ENDMENU
};
debug_menu_line jungle_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "jungle1 (unused)", goto_level, 14 ),
    DMT_ACTION( "jungle2", goto_level, 15 ),
    DMT_ACTION( "jungle3", goto_level, 16 ),
    DMT_ACTION( "jungle4 (unused)", goto_level, 17 ),
    DMT_ACTION( "jungle5 (unused)", goto_level, 18 ),
    DMT_ACTION( "jungle6 (unused)", goto_level, 19 ),
    DMT_ACTION( "jungle7 (boss)", goto_level, 20 ),
    DMT_ENDMENU
};
debug_menu_line rez_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "rez1", goto_level, 21 ),
    DMT_ACTION( "rez2", goto_level, 22 ),
    DMT_ACTION( "rez3", goto_level, 23 ),
    DMT_ACTION( "rez4", goto_level, 24 ),
    DMT_ACTION( "rez5", goto_level, 25 ),
    DMT_ACTION( "rez6", goto_level, 26 ),
    DMT_ACTION( "rez7 (boss)", goto_level, 27 ),
    DMT_ENDMENU
};
debug_menu_line scifi_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "scifi1", goto_level, 28 ),
    DMT_ACTION( "scifi2", goto_level, 29 ),
    DMT_ACTION( "scifi3", goto_level, 30 ),
    DMT_ACTION( "scifi4", goto_level, 31 ),
    DMT_ENDMENU
};
debug_menu_line kungfu_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "kungfu1", goto_level, 35 ),
    DMT_ACTION( "kungfu2", goto_level, 36 ),
    DMT_ACTION( "kungfu3", goto_level, 37 ),
    DMT_ACTION( "kungfu4", goto_level, 38 ),
    DMT_ENDMENU
};
debug_menu_line mainmap_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "mainmap1 (grave)", goto_level, 49 ),
    DMT_ACTION( "mainmap2 (cartoon)", goto_level, 50 ),
    DMT_ACTION( "mainmap3 (jungle)", goto_level, 51 ),
    DMT_ACTION( "mainmap4 (rez)", goto_level, 52 ),
    DMT_ACTION( "mainmap5 (scifi)", goto_level, 53 ),
    DMT_ACTION( "mainmap6 (kungfu)", goto_level, 54 ),
    DMT_ACTION( "mainmap7 (main dome)", goto_level, 55 ),
    DMT_ENDMENU
};
debug_menu_line bonus_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "bonus1 (jungle)", goto_level, 56 ),
    DMT_ACTION( "bonus2 (grave)", goto_level, 57 ),
    DMT_ACTION( "bonus3 (rez)", goto_level, 58 ),
    DMT_ACTION( "bonus4 (kungfu)", goto_level, 59 ),
    DMT_ACTION( "bonus5 (cartoon, secret)", goto_level, 60 ),
    // DMT_ACTION( "bonus6 (unused)", goto_level, 61 ), - crashes the game
    DMT_ACTION( "bonus7", goto_level, 62 ),
    DMT_ENDMENU
};
debug_menu_line secret_menu[] =
{
    DMT_MENU( "level select...", level_select_menu ),
    DMT_ACTION( "sl67", goto_level, 136 ),
    DMT_ACTION( "sl68", goto_level, 137 ),
    DMT_ACTION( "sl69", goto_level, 138 ),
    DMT_ENDMENU
};

extern debug_menu_line main_menu[];
debug_menu_line level_select_menu[] =
{
    DMT_MENU( "main menu...", main_menu ),
    DMT_INT( "level to goto", &level_to_goto ),
    DMT_ACTION( "goto level", goto_specific_level, 0 ),
    DMT_MENU( "grave menu...", grave_menu ),
    DMT_MENU( "cartoon menu...", cartoon_menu ),
    DMT_MENU( "jungle menu...", jungle_menu ),
    DMT_MENU( "rez menu...", rez_menu ),
    DMT_MENU( "scifi menu...", scifi_menu ),
    DMT_MENU( "kungfu menu...", kungfu_menu ),
    DMT_MENU( "mainmap menu...", mainmap_menu ),
    DMT_MENU( "bonus menu...", bonus_menu ),
    DMT_MENU( "secret menu...", secret_menu ),
    DMT_ENDMENU
};

void do_cheat( debug_menu_line* a_line )
{
    gCurrentCheatCode = a_line->data1;
}

debug_menu_line cheats_menu[] =
{
    DMT_MENU( "main menu...", main_menu ),
    DMT_ACTION( "unlock levels on current map", do_cheat, 0x0 ),
    DMT_ACTION( "level select", do_cheat, 0x1 ),
    DMT_ACTION( "99 lives", do_cheat, 0x2 ),
    DMT_ENDMENU
};

debug_menu_line sound_menu[] =
{
    DMT_MENU( "main menu...", main_menu ),
    DMT_BOOL( "sfx", &gEnableSFX ),
    DMT_BOOL( "vfx", &gEnableVFX ),
    DMT_BOOL( "music", &gEnableMUS ),
    DMT_ENDMENU
};

int ob_debug_draw_flags = 0;
constexpr int k_ob_debug_draw_types = 1 << 0;
constexpr int k_ob_debug_draw_layer = 1 << 1;
constexpr int k_ob_debug_draw_cldprio = 1 << 2;
constexpr int k_ob_debug_draw_cldtype = 1 << 3;
constexpr int k_ob_debug_draw_work0 = 1 << 4;
constexpr int k_ob_debug_draw_work1 = 1 << 5;
constexpr int k_ob_debug_draw_work2 = 1 << 6;
constexpr int k_ob_debug_draw_work3 = 1 << 7;
constexpr int k_ob_debug_draw_work4 = 1 << 8;
constexpr int k_ob_debug_draw_work5 = 1 << 9;
constexpr int k_ob_debug_draw_work6 = 1 << 10;
constexpr int k_ob_debug_draw_work7 = 1 << 11;
constexpr int k_ob_debug_ignore_common_ob_types = 1 << 30;
bool should_draw_info = false;
bool should_draw_debug_data = false;

debug_menu_line debug_draw_menu[] =
{
    DMT_MENU( "main menu...", main_menu ),
    DMT_FLAG( "ob types", &ob_debug_draw_flags, k_ob_debug_draw_types ),
    DMT_FLAG( "ignore common ob types", &ob_debug_draw_flags, k_ob_debug_ignore_common_ob_types ),
    DMT_FLAG( "ob layer", &ob_debug_draw_flags, k_ob_debug_draw_layer ),
    DMT_FLAG( "ob cldprio", &ob_debug_draw_flags, k_ob_debug_draw_cldprio ),
    DMT_FLAG( "ob cldtype", &ob_debug_draw_flags, k_ob_debug_draw_cldtype ),
    DMT_FLAG( "ob work0", &ob_debug_draw_flags, k_ob_debug_draw_work0 ),
    DMT_FLAG( "ob work1", &ob_debug_draw_flags, k_ob_debug_draw_work1 ),
    DMT_FLAG( "ob work2", &ob_debug_draw_flags, k_ob_debug_draw_work2 ),
    DMT_FLAG( "ob work3", &ob_debug_draw_flags, k_ob_debug_draw_work3 ),
    DMT_FLAG( "ob work4", &ob_debug_draw_flags, k_ob_debug_draw_work4 ),
    DMT_FLAG( "ob work5", &ob_debug_draw_flags, k_ob_debug_draw_work5 ),
    DMT_FLAG( "ob work6", &ob_debug_draw_flags, k_ob_debug_draw_work6 ),
    DMT_FLAG( "ob work7", &ob_debug_draw_flags, k_ob_debug_draw_work7 ),
    DMT_ENDMENU
};

debug_menu_line main_menu[] =
{
    DMT_BOOL( "draw info", &should_draw_info ),
    DMT_BOOL( "draw debug data", &should_draw_debug_data ),
    DMT_MENU( "debug draw menu...", debug_draw_menu ),
    DMT_MENU( "level select menu...", level_select_menu ),
    DMT_MENU( "cheats menu...", cheats_menu ),
    DMT_MENU( "sound menu...", sound_menu ),
    DMT_ENDMENU
};

bool menu_open = false;
debug_menu_line* current_menu = main_menu;
std::stack< debug_menu_line* > menu_stack;
int selected_index = 0;

void draw_obs()
{
    static const std::set< int > k_types_to_ignore
    {
        242, // gravemap cloud
        247 // kungfumap cloud
    }; 
    for( const auto& list : gObjectLists )
    {
        for( auto ob = (GXObject*) list.lst_head; ob; ob = (GXObject*) ob->gob_node.nd_next )
        {
            if( (ob_debug_draw_flags & k_ob_debug_ignore_common_ob_types) && k_types_to_ignore.contains( ob->gob_type ) )
                continue;
            int xpos = ob->gob_xpos - CAMERA_XPos;
            const int ypos = ob->gob_ypos - CAMERA_YPos;
            const auto drawf = [&]( const char* fmt, ... )
            {
                static char buf[1024];
                va_list args;
                va_start( args, fmt );
                vsnprintf( buf, sizeof(buf), fmt, args );
                TXT_DrawPrintP( xpos, ypos, buf );
                xpos += TXT_PixelLength( buf ) + GEX_POS(3);
                va_end( args );
            };

            const auto draw_work = [&]( int work_flag )
            {
                int index = std::countr_zero( static_cast< unsigned >( work_flag ) ) - std::countr_zero( static_cast< unsigned >( k_ob_debug_draw_work0 ) );
                if( ob_debug_draw_flags & work_flag )
                    drawf( "%d:%x", index, (&ob->gob_work0)[index] );
            };

            if( ob_debug_draw_flags & k_ob_debug_draw_types )
                drawf( "%d", ob->gob_type );
            if( ob_debug_draw_flags & k_ob_debug_draw_layer )
                drawf( "l%x", ob->gob_flags & OB_LAYER_MASK );
            if( ob_debug_draw_flags & k_ob_debug_draw_cldprio )
                drawf( "p%x", ob->gob_flags & OB_CLDPRIO_MASK >> 4 );
            if( ob_debug_draw_flags & k_ob_debug_draw_cldtype )
                drawf( "t%x", ob->gob_flags & OB_CLDTYPE_MASK >> 8 );
            draw_work( k_ob_debug_draw_work0 );
            draw_work( k_ob_debug_draw_work1 );
            draw_work( k_ob_debug_draw_work2 );
            draw_work( k_ob_debug_draw_work3 );
            draw_work( k_ob_debug_draw_work4 );
            draw_work( k_ob_debug_draw_work5 );
            draw_work( k_ob_debug_draw_work6 );
            draw_work( k_ob_debug_draw_work7 );
        }
    }
}

void draw_info()
{
    int frames = gTimer % 30;
    int seconds = (gTimer / 30) % 60;
    int minutes = gTimer / (30*60);
    TXT_DrawPrintF( GEX_POS(10), GEX_POS(10), "time %02d:%02d:%02d", minutes, seconds, frames );
    TXT_DrawPrintF( GEX_POS(10), GEX_POS(20), "level %d fmem %d", level, gNumFreeBlocks );
}

std::vector< std::string > debug_log_datas{};
constexpr int k_max_debug_lines = 10;

void debug_data_add_str( const char* a_str )
{
    static std::vector< std::string > k_to_filter =
    {
        // from M1_PlayLevel
        "Intro Objects\n",
        "ProcessBlockAnims\n",
        "ProcessTileAnims\n",
        "Process Objects\n",
        "Process Collisions\n",
        "Set Scroll Position\n",
        "Draw Tiles\n",
        "Draw Objects Mid\n",
        "Draw Objects Hi\n",
    };
    std::string str{a_str};
    if( std::find( k_to_filter.begin(), k_to_filter.end(), str ) != k_to_filter.end() )
        return;

    if( debug_log_datas.size() > k_max_debug_lines )
        debug_log_datas.erase( debug_log_datas.begin() );
    debug_log_datas.emplace_back( a_str );
}

void debug_print( const char* a_format, ... )
{
    std::va_list args;
    va_start( args, a_format );
    char buf[256];
    std::vsnprintf( buf, sizeof buf, a_format, args );
    debug_data_add_str( buf );
    va_end( args );
}
quick_hook dp_hook{0x00405350, (void*)&debug_print};
quick_hook dp2_hook{0x00405390, (void*)&debug_print};

void draw_debug_data()
{
    int y = GEX_POS(10);
    for( const auto& data : debug_log_datas )
    {
        y += GEX_POS(10);
        TXT_DrawPrintP( GEX_POS(10), y, data.c_str() );
    }
}

constexpr int k_y_step = GEX_POS(15);

void draw_menu_line( int a_y, debug_menu_line* a_line, bool a_selected )
{
    DrawRectMaybe( 0, GEX_POS( 55 ), a_y - k_y_step/3, GEX_POS( 250-55 ), k_y_step, 0, 0x1f801f80 );
    if( a_selected )
        TXT_DrawPrintP( GEX_POS(60), a_y, ">" );

    TXT_DrawPrintP( GEX_POS(70), a_y, a_line->text );
    switch( a_line->type )
    {
        case debug_menu_type::dmt_int:
        {
            if( a_line->var )
                TXT_DrawPrintF( GEX_POS(200), a_y, "%d", *(int*)a_line->var );
            else
                TXT_DrawPrintP( GEX_POS(200), a_y, "NULL" );
            break;
        }

        case debug_menu_type::dmt_bool:
        {
            if( a_line->var )
                TXT_DrawPrintF( GEX_POS(200), a_y, "%s", *(bool*)a_line->var ? "true" : "false" );
            else
                TXT_DrawPrintP( GEX_POS(200), a_y, "NULL" );
            break;
        }
        case debug_menu_type::dmt_flag:
        {
            if( a_line->var )
                TXT_DrawPrintF( GEX_POS(200), a_y, "%s", *(int*)a_line->var & a_line->data1 ? "true" : "false" );
            else
                TXT_DrawPrintP( GEX_POS(200), a_y, "NULL" );
            break;
        }
        default: break;
    }
}

void step_line( debug_menu_line* a_line, int a_step )
{
    if( !a_line->var || a_line->type != debug_menu_type::dmt_int )
        return;

    bool ctrl = GetAsyncKeyState( VK_CONTROL ) < 0;
    bool shift = GetAsyncKeyState( VK_SHIFT ) < 0;
    int step = a_step;

    if( ctrl )
        step *= 10;
    if( shift )
        step *= 10;

    *a_line->var += step;
}

void process_menu_left( debug_menu_line* a_line )
{
    switch( a_line->type )
    {
        case debug_menu_type::dmt_int: step_line( a_line, -1 ); break;
        case debug_menu_type::dmt_bool: if( a_line->var ) (*(bool*)a_line->var) = false; break;
        case debug_menu_type::dmt_flag: if( a_line->var ) (*(int*)a_line->var) &= ~a_line->data1; break;
        default: break;
    }
}

void process_menu_right( debug_menu_line* a_line )
{
    switch( a_line->type )
    {
        case debug_menu_type::dmt_int: step_line( a_line, 1 ); break;
        case debug_menu_type::dmt_bool: if( a_line->var ) (*(bool*)a_line->var) = true; break;
        case debug_menu_type::dmt_flag: if( a_line->var ) (*(int*)a_line->var) |= a_line->data1; break;
        default: break;
    }
}

debug_menu_line* find_endmenu_line( debug_menu_line* a_menu )
{
    while( a_menu->type != debug_menu_type::dmt_endmenu )
        a_menu++;
    return a_menu;
}

void push_menu( debug_menu_line* a_menu )
{
    find_endmenu_line( current_menu )->data1 = selected_index;
    menu_stack.push( current_menu );
    current_menu = a_menu;
    selected_index = find_endmenu_line( current_menu )->data1;
}

void pop_menu()
{
    if( menu_stack.top() == main_menu )
        return;

    find_endmenu_line( current_menu )->data1 = selected_index;
    menu_stack.pop();
    current_menu = menu_stack.top();
}

void process_menu_activate( debug_menu_line* a_line )
{
    switch( a_line->type )
    {
        case debug_menu_type::dmt_action: if( a_line->var ) ((on_activate_func)a_line->var)( a_line ); break;
        case debug_menu_type::dmt_menu:
            if( a_line->var )
            {
                push_menu( (debug_menu_line*)a_line->var );
            }
            break;
        default: break;
    }
}

void draw_menu()
{
    constexpr int k_start_y = GEX_POS(50);

    gNoProcess = menu_open;

    if( gCurrentVK == VK_DOWN && current_menu[selected_index + 1].type != debug_menu_type::dmt_endmenu )
        selected_index++;
    else if( gCurrentVK == VK_UP && selected_index > 0 )
        selected_index--;
    else if( gCurrentVK == VK_RIGHT )
        process_menu_right( &current_menu[selected_index] );
    else if( gCurrentVK == VK_LEFT )
        process_menu_left( &current_menu[selected_index] );
    else if( gCurrentVK == VK_RETURN || gCurrentVK == VK_SPACE )
        process_menu_activate( &current_menu[selected_index] );
    if( gCurrentVK == 'p' )
        pop_menu();


    for( int i = 0; current_menu[i].type != debug_menu_type::dmt_endmenu; i++ )
        draw_menu_line( k_start_y + k_y_step * i, &current_menu[i], i == selected_index );
}

void draw_debug_text();
quick_hook ddt_hook{0x00410250, (void*)&draw_debug_text};
void draw_debug_text()
{
    if( should_draw_info )
        draw_info();
    if( should_draw_debug_data )
        draw_debug_data();
    if( ob_debug_draw_flags )
        draw_obs();

    if( gCurrentVK == 'o' ) // 'O'
    {
        menu_open = !menu_open;
        gNoProcess = menu_open;
    }
    if( menu_open )
        draw_menu();
    ddt_hook.remove();
    ((void(*)())0x00410250)();
    ddt_hook.install();
}

bool videos = false;

void disable_video_hook( const char* a_video_name );
quick_hook disable_video_hook_hook{00404410, (void*)&disable_video_hook};
void disable_video_hook( const char* a_video_name )
{
    if( videos )
        return;

    disable_video_hook_hook.remove();
    ((void(*)())0x0043f3d0)();
    disable_video_hook_hook.install();
}

class init_type
{
public:
    init_type()
    {
        OutputDebugStringA( "gexhook.asi loaded!\n" );
        const auto pid = std::to_string( GetCurrentProcessId() );
        OutputDebugStringA( ("pid: " + pid + "\n").c_str() );
        menu_stack.push( main_menu );
    }
};

static init_type i;

