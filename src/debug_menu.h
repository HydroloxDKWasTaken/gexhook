#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

#include <variant>
#include <string>
#include <string_view>
#include <array>
#include <stack>

namespace debug_menu
{

struct dm_line;

using dm_action_fun = void ( * )( dm_line* );

enum class line_type
{
    action,
    menu,
    integer,
    boolean,
    flag,
    endmenu
};

struct dm_line
{
    using var_t = std::variant< std::monostate, dm_line*, dm_action_fun, int*, bool* >;

    line_type type;
    std::string text;
    var_t var;
    int data1{ };

    void draw( int a_y, bool a_selected );
    void step( int a_step );
    dm_line* seek_endmenu( );
};

class menu_builder
{
    inline static constexpr size_t k_max_dm_lines = 2048; // max number of lines in all menus

  public:
    menu_builder( ): m_start_ptr{ &s_line_pool.at( s_total_lines ) } {}

    menu_builder& add_menu( std::string_view menu_name, dm_line* menu );

    menu_builder& add_action( std::string_view text, dm_action_fun func, int arg = 0 );

    menu_builder& add_int_ref( std::string_view text, int* val );

    menu_builder& add_bool_ref( std::string_view text, int* val );

    menu_builder& add_bool_ref( std::string_view text, bool* val );

    menu_builder& add_flag( std::string_view text, int* flags, int val );

    dm_line* build( );

  private:
    dm_line* m_start_ptr = nullptr;
    inline static size_t s_total_lines = 0;
    inline static std::array< dm_line, k_max_dm_lines > s_line_pool{ };
};

// declarations
void init( );
void draw_menu( );

void process_menu_left( dm_line* a_line );
void process_menu_right( dm_line* a_line );
void process_menu_activate( dm_line* a_line );
void push_menu( dm_line* a_menu );
void pop_menu( );

/// \return menu_open state after the operation
bool toggle_menu( );
bool is_menu_open( );

inline int level_to_goto = 0;

namespace actions
{
void goto_level( dm_line* a_line );
void goto_specific_level( dm_line* a_line );
void do_cheat( dm_line* a_line );
} // namespace actions

inline dm_line* current_menu = nullptr;
inline std::stack< dm_line* > menu_stack;
inline int selected_index = 0;
inline bool menu_open = false;

} // namespace debug_menu

#endif // DEBUG_MENU_H
