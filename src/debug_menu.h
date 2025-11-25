#pragma once
#include <variant>
#include <string>
#include <string_view>
#include <array>
#include "global.h"
#include <stack>

namespace debug_menu {

struct dm_line;
using dm_action_fun = void (*)(dm_line*);

enum class line_type {
    action,
    menu,
    integer,
    boolean,
    flag,
    endmenu
};

struct dm_line {
    using var_t = std::variant<std::monostate, dm_line*, dm_action_fun, int*, bool*>;

    line_type type;
    std::string text;
    var_t var;
    int data1{};

    void draw(int a_y, bool a_selected);
    void step(int a_step);
    dm_line* find_endmenu();
};

/// \brief Helps build dm_line-based menus.
/// \tparam n_lines
///     Size of the returned array.
///     Must be at least: number of menu entries + 1.
template <size_t n_lines>
class menu_builder {
  public:
    static_assert(n_lines > 0);
    menu_builder() = default;

    menu_builder& add_menu(std::string_view menu_name, dm_line* menu);

    template <class T>
    menu_builder& add_menu(std::string_view menu_name, T& menu);

    menu_builder& add_action(std::string_view text, dm_action_fun func, int arg = 0);

    menu_builder& add_int_ref(std::string_view text, int* val);

    menu_builder& add_bool_ref(std::string_view text, int* val);

    menu_builder& add_bool_ref(std::string_view text, bool* val);

    menu_builder& add_flag(std::string_view text, int* flags, int val);

    std::array<dm_line, n_lines> build();

  private:
    size_t m_counter = 0;
    std::array<dm_line, n_lines> m_lines{};
};

// declarations
void init();
void draw_menu();

void process_menu_left(dm_line* a_line);
void process_menu_right(dm_line* a_line);
void process_menu_activate(dm_line* a_line);
void push_menu(dm_line* a_menu);
void pop_menu();

/// \return menu_open state after the operation
int toggle_menu();
bool is_menu_open();

inline int level_to_goto = 0;

namespace actions {
void goto_level(dm_line* a_line);
void goto_specific_level(dm_line* a_line);
void do_cheat(dm_line* a_line);
} // namespace actions

// internal state (inline to keep header-only initialization semantics)
static constexpr int k_y_step = GEX_POS(15);
inline dm_line* current_menu = nullptr;
inline std::stack<dm_line*> menu_stack;
inline int selected_index = 0;
inline bool menu_open = false;

// --- method definitions ---

template <size_t n_lines>
inline menu_builder<n_lines>&
menu_builder<n_lines>::add_menu(std::string_view menu_name, debug_menu::dm_line* menu) {
    m_lines.at(m_counter++) = { line_type::menu, std::string(menu_name), menu };
    return *this;
}

template <size_t n_lines>
template <class T>
inline menu_builder<n_lines>&
menu_builder<n_lines>::add_menu(std::string_view menu_name, T& menu) {
    add_menu(menu_name, menu.data());
    return *this;
}

template <size_t n_lines>
inline menu_builder<n_lines>&
menu_builder<n_lines>::add_action(std::string_view text, dm_action_fun func, int arg) {
    m_lines.at(m_counter++) = { line_type::action, std::string(text), func, arg };
    return *this;
}

template <size_t n_lines>
inline menu_builder<n_lines>&
menu_builder<n_lines>::add_int_ref(std::string_view text, int* val) {
    m_lines.at(m_counter++) = { line_type::integer, std::string(text), val };
    return *this;
}

template <size_t n_lines>
inline menu_builder<n_lines>&
menu_builder<n_lines>::add_bool_ref(std::string_view text, int* val) {
    m_lines.at(m_counter++) = { line_type::boolean, std::string(text), val };
    return *this;
}

template <size_t n_lines>
inline menu_builder<n_lines>&
menu_builder<n_lines>::add_bool_ref(std::string_view text, bool* val) {
    m_lines.at(m_counter++) = { line_type::boolean, std::string(text), val };
    return *this;
}

template <size_t n_lines>
inline menu_builder<n_lines>&
menu_builder<n_lines>::add_flag(std::string_view text, int* flags, int val) {
    m_lines.at(m_counter++) = { line_type::flag, std::string(text), flags, val };
    return *this;
}

template <size_t n_lines>
inline std::array<dm_line, n_lines> menu_builder<n_lines>::build() {
    m_lines.at(m_counter) = { line_type::endmenu };
    m_counter = 0;
    return m_lines;
}

} // namespace debug_menu
