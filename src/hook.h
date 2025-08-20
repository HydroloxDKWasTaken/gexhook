#ifndef HOOK_H
#define HOOK_H
#include <cstdint>
#include <subhook.h>

class quick_hook
{
public:
    quick_hook( std::uintptr_t a_src, void* a_dst, subhook::HookFlags a_flags = subhook::HookNoFlags ) :
        hook{reinterpret_cast< void* >( a_src ), a_dst, a_flags}
    {
        hook.Install();
    }
    quick_hook() = delete;
    ~quick_hook() = default;

    void install() { hook.Install(); }
    void remove() { hook.Remove(); }

    void* get_trampoline() const { return hook.GetTrampoline(); }
private:
    subhook::Hook hook;
};

#endif
