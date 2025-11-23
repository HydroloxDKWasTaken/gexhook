#include "hook.h"
#include "game.h"
#include "menus.h"
#include "debug_draw.h"
#include <string>
#include <windows.h>

void freecam_disable_hook_1();
quick_hook freecam_disable_hook{ 0x00431300, (void*)&freecam_disable_hook_1 };
void freecam_disable_hook_1() {
    if(free_camera_mode) return;
    freecam_disable_hook.remove();
    ((void (*)())0x00431300)();
    freecam_disable_hook.install();
}

void freecam_disable_hook_2(int a, int b, int c);
quick_hook freecam_disable_hook_2_hook{ 0x0040fe80, (void*)&freecam_disable_hook_2 };
void freecam_disable_hook_2(int a, int b, int c) {
    if(free_camera_mode) return;
    freecam_disable_hook_2_hook.remove();
    ((void (*)(int, int, int))0x0040fe80)(a, b, c);
    freecam_disable_hook_2_hook.install();
}

void freecam_disable_hook3();
quick_hook freecam_disable_hook3_hook{ 0x00410250, (void*)&freecam_disable_hook3 };
void freecam_disable_hook3() {
    if(free_camera_mode) return;
    freecam_disable_hook3_hook.remove();
    ((void (*)())0x00410250)();
    freecam_disable_hook3_hook.install();
}

void process_freecam() {
    const int speed = std::isupper(gCurrentVK) ? GEX_POS(20) : GEX_POS(5);
    TXT_DrawPrintF(GEX_POS(10), GEX_POS(210), "i = UP, k = DOWN, j = LEFT, l = RIGHT");
    TXT_DrawPrintF(GEX_POS(10), GEX_POS(220), "X = %d, Y = %d", CAMERA_XPos, CAMERA_YPos);
    if(std::tolower(gCurrentVK) == 'i')
        free_camera_y -= speed;
    if(std::tolower(gCurrentVK) == 'k')
        free_camera_y += speed;
    if(std::tolower(gCurrentVK) == 'j')
        free_camera_x -= speed;
    if(std::tolower(gCurrentVK) == 'l')
        free_camera_x += speed;
    CAMERA_XPos = free_camera_x;
    CAMERA_YPos = free_camera_y;
}

void draw_debug_text();
quick_hook ddt_hook{ 0x00410250, (void*)&draw_debug_text };
void draw_debug_text() {
    if(stats_flags)
        debug_draw::draw_info();
    if(should_draw_debug_data)
        debug_draw::draw_debug_data();
    if(ob_debug_draw_flags)
        debug_draw::draw_obs();

    if(gCurrentVK == 'o') // 'O'
    {
        gNoProcess = debug_menu::toggle_menu();
    }
    if(debug_menu::is_menu_open())
        debug_menu::draw_menu();

    static bool was_freecam = false;
    if(was_freecam != free_camera_mode) {
        if(free_camera_mode) {
            free_camera_x = CAMERA_XPos;
            free_camera_y = CAMERA_YPos;
            free_camera_restore_x = free_camera_x;
            free_camera_restore_y = free_camera_y;
        } else {
            CAMERA_XPos = free_camera_restore_x;
            CAMERA_YPos = free_camera_restore_y;
        }
        gEnableScrolling = !free_camera_mode;
        was_freecam = free_camera_mode;
    }
    if(free_camera_mode) {
        gEnableScrolling = false;
        process_freecam();
    }

    ddt_hook.remove();
    ((void (*)())0x00410250)();
    ddt_hook.install();
}

bool videos = false;

void disable_video_error_box(int error);
quick_hook disable_video_error_box_hook{ 0x004046b0, (void*)&disable_video_error_box };
void disable_video_error_box(int error) {}

class init_type {
  public:
    init_type() {
        OutputDebugStringA("gexhook.asi loaded!\n");
        const auto pid = std::to_string(GetCurrentProcessId());
        OutputDebugStringA(("pid: " + pid + "\n").c_str());
        debug_menu::init();
    }
} static i;
