#include "debug_menu.h"
#include "menus.h"
#include "game.h"
#include "global.h"
#include <Windows.h>
#include <concepts>
#include <optional>

namespace debug_menu {

// internal helper functions
static inline void set_boolean_var(dm_line::var_t& var, bool value) {
    std::visit([=]<typename T>(T& arg) {
        if constexpr(std::same_as<T, bool*>) {
            if(!arg) return;
            *arg = value;
        } else if constexpr(std::same_as<T, int*>) {
            if(!arg) return;
            *arg = value ? 1 : 0;
        }
    },
        var);
}
static inline std::optional<bool> get_boolean_var(const dm_line::var_t& var) {
    return std::visit([]<typename T>(T&& arg) -> std::optional<bool> {
        if constexpr(std::same_as<T, bool* const&>) {
            if(arg) return *arg;
        } else if constexpr(std::same_as<T, int* const&>)
            if(arg) return *arg != 0;

        return std::nullopt;
    },
        var);
}

void init() {
    current_menu = main_menu.data();
    menu_stack.push(main_menu.data());
}

void draw_menu() {
    constexpr int k_start_y = GEX_POS(50);

    gNoProcess = menu_open;

    if(gCurrentVK == VK_DOWN && current_menu[selected_index + 1].type != line_type::endmenu)
        selected_index++;
    else if(gCurrentVK == VK_UP && selected_index > 0)
        selected_index--;
    else if(gCurrentVK == VK_RIGHT)
        process_menu_right(&current_menu[selected_index]);
    else if(gCurrentVK == VK_LEFT)
        process_menu_left(&current_menu[selected_index]);
    else if(gCurrentVK == VK_RETURN || gCurrentVK == VK_SPACE)
        process_menu_activate(&current_menu[selected_index]);
    if(gCurrentVK == 'p')
        pop_menu();

    constexpr int k_num_lines_to_show = 10;

    int start_line = 0;
    if(selected_index > 6)
        start_line = selected_index - 6;

    for(int i = start_line; current_menu[i].type != line_type::endmenu; i++) {
        const int ypos = k_start_y + k_y_step * (i - start_line);
        ;
        if(i >= k_num_lines_to_show + start_line) {
            DrawARect(0, GEX_POS(55), ypos - k_y_step / 3, GEX_POS(250 - 55), k_y_step, 0, 0x1f801f80);
            TXT_DrawPrintF(GEX_POS(70), ypos, "...");
            break;
        }
        current_menu[i].draw(ypos, i == selected_index);
    }
}

inline void process_menu_left(dm_line* a_line) {
    switch(a_line->type) {
    case line_type::integer:
        a_line->step(-1);
        break;
    case line_type::boolean: {
        set_boolean_var(a_line->var, false);
        break;
    }
    case line_type::flag: {
        if(auto p = std::get_if<int*>(&a_line->var)) {
            int* ip = *p;
            if(ip) (*ip) &= ~a_line->data1;
        }
        break;
    }
    default: break;
    }
}

inline void process_menu_right(dm_line* a_line) {
    switch(a_line->type) {
    case line_type::integer: a_line->step(1); break;
    case line_type::boolean: {
        set_boolean_var(a_line->var, true);
        break;
    }
    case line_type::flag: {
        if(auto p = std::get_if<int*>(&a_line->var)) {
            int* ip = *p;
            if(ip) (*ip) |= a_line->data1;
        }
        break;
    }
    default: break;
    }
}

inline void process_menu_activate(dm_line* a_line) {
    switch(a_line->type) {
    case line_type::action: {
        if(auto p = std::get_if<dm_action_fun>(&a_line->var)) {
            dm_action_fun f = *p;
            if(f) f(a_line);
        }
        break;
    }
    case line_type::menu: {
        if(auto p = std::get_if<dm_line*>(&a_line->var)) {
            dm_line* lp = *p;
            if(lp) {
                push_menu(lp);
            }
        }
        break;
    }
    default: break;
    }
}

inline void push_menu(dm_line* a_menu) {
    current_menu->find_endmenu()->data1 = selected_index;
    menu_stack.push(current_menu);
    current_menu = a_menu;
    selected_index = current_menu->find_endmenu()->data1;
}

inline void pop_menu() {
    if(menu_stack.top() == main_menu.data())
        return;

    current_menu->find_endmenu()->data1 = selected_index;
    menu_stack.pop();
    current_menu = menu_stack.top();
}

int toggle_menu() {
    menu_open = !menu_open;
    return menu_open;
}

bool is_menu_open() {
    return menu_open;
}

void actions::goto_level(dm_line* a_line) {
    level = a_line->data1;
}

void actions::goto_specific_level(dm_line* a_line) {
    level = level_to_goto;
    level_to_goto = 0;
}

void actions::do_cheat(dm_line* a_line) {
    gCurrentCheatCode = a_line->data1;
}

void dm_line::draw(int a_y, bool a_selected) {
    DrawARect(0, GEX_POS(55), a_y - k_y_step / 3, GEX_POS(250 - 55), k_y_step, 0, 0x1f801f80);
    if(a_selected)
        TXT_DrawPrintP(GEX_POS(60), a_y, ">");

    TXT_DrawPrintP(GEX_POS(70), a_y, text.c_str());
    switch(type) {
    case line_type::integer: {
        if(auto p = std::get_if<int*>(&var)) {
            int* ip = *p;
            if(ip)
                TXT_DrawPrintF(GEX_POS(200), a_y, "%d", *ip);
            else
                TXT_DrawPrintP(GEX_POS(200), a_y, "NULL");
        } else {
            TXT_DrawPrintP(GEX_POS(200), a_y, "NULL");
        }
        break;
    }

    case line_type::boolean: {
        auto boolopt = get_boolean_var(var);

        if(boolopt.has_value())
            TXT_DrawPrintF(GEX_POS(200), a_y, "%s", bool_to_c_str(*boolopt));
        else
            TXT_DrawPrintP(GEX_POS(200), a_y, "NULL");

        break;
    }
    case line_type::flag: {
        if(auto p = std::get_if<int*>(&var)) {
            int* ip = *p;
            if(ip)
                TXT_DrawPrintF(GEX_POS(200), a_y, "%s", bool_to_c_str(((*ip) & data1) != 0));
            else
                TXT_DrawPrintP(GEX_POS(200), a_y, "NULL");
        } else {
            TXT_DrawPrintP(GEX_POS(200), a_y, "NULL");
        }
        break;
    }
    default: break;
    }
}

inline void dm_line::step(int a_step) {
    if(type != line_type::integer)
        return;

    if(auto p = std::get_if<int*>(&var)) {
        int* ip = *p;
        if(!ip) return;

        bool ctrl = GetAsyncKeyState(VK_CONTROL) < 0;
        bool shift = GetAsyncKeyState(VK_SHIFT) < 0;
        int step = a_step;

        if(ctrl)
            step *= 10;
        if(shift)
            step *= 10;

        *ip += step;
    }
}

inline dm_line* dm_line::find_endmenu() {
    auto menu = this;
    while(menu->type != line_type::endmenu)
        menu++;
    return menu;
}

} // namespace debug_menu
