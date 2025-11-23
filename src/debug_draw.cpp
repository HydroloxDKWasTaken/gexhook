#include "debug_draw.h"
#include "game.h"
#include "global.h"
#include <bit>
#include <cstdarg>
#include <set>
#include <unordered_set>
#include <string>
#include <deque>

namespace debug_draw {

void draw_obs() {
    static const std::set<int> k_types_to_ignore{
        (int)ob_type::gravemap_cloud,
        (int)ob_type::kungfumap_cloud
    };
    for(const auto& list : gObjectLists) {
        for(auto ob = (GXObject*)list.lst_head; ob; ob = (GXObject*)ob->gob_node.nd_next) {
            const auto filter_pass = [&] {
                bool pass = true;
                if(ob_debug_draw_flags & k_ob_debug_ignore_common_ob_types)
                    pass = pass && !k_types_to_ignore.contains(ob->gob_type);
                if(ob_debug_draw_filter_by_type != -1)
                    pass = pass && ob->gob_type == ob_debug_draw_filter_by_type;
                return pass;
            };
            if(!filter_pass())
                continue;

            int xpos = ob->gob_xpos - CAMERA_XPos;
            const int ypos = ob->gob_ypos - CAMERA_YPos;
            const auto drawf = [&](const char* fmt, ...) {
                static char buf[1024];
                va_list args;
                va_start(args, fmt);
                vsnprintf(buf, sizeof(buf), fmt, args);
                TXT_DrawPrintP(xpos, ypos, buf);
                xpos += TXT_PixelLength(buf) + GEX_POS(3);
                va_end(args);
            };

            const auto draw_work = [&](int work_flag) {
                int index = std::countr_zero(std::bit_cast<uint32_t>(work_flag)) - std::countr_zero(std::bit_cast<uint32_t>(k_ob_debug_draw_work0));
                if(ob_debug_draw_flags & work_flag)
                    drawf("%d:%x", index, (&ob->gob_work0)[index]);
            };

            if(ob_debug_draw_flags & k_ob_debug_draw_types)
                drawf("%d", ob->gob_type);
            if(ob_debug_draw_flags & k_ob_debug_draw_layer)
                drawf("l%x", ob->gob_flags & OB_LAYER_MASK);
            if(ob_debug_draw_flags & k_ob_debug_draw_cldprio)
                drawf("p%x", ob->gob_flags & OB_CLDPRIO_MASK >> 4);
            if(ob_debug_draw_flags & k_ob_debug_draw_cldtype)
                drawf("t%x", ob->gob_flags & OB_CLDTYPE_MASK >> 8);
            draw_work(k_ob_debug_draw_work0);
            draw_work(k_ob_debug_draw_work1);
            draw_work(k_ob_debug_draw_work2);
            draw_work(k_ob_debug_draw_work3);
            draw_work(k_ob_debug_draw_work4);
            draw_work(k_ob_debug_draw_work5);
            draw_work(k_ob_debug_draw_work6);
            draw_work(k_ob_debug_draw_work7);
        }
    }
}

void draw_info() {
    if(stats_flags & k_stats_short) {
        int frames = gTimer % 30;
        int seconds = (gTimer / 30) % 60;
        int minutes = gTimer / (30 * 60);
        TXT_DrawPrintF(GEX_POS(10), GEX_POS(10), "time %02d:%02d:%02d", minutes, seconds, frames);
        TXT_DrawPrintF(GEX_POS(140), GEX_POS(10), "level %d fmem %d", level, gNumFreeBlocks);
    }
    if(stats_flags & k_stats_long) {
        int px = 0, py = 0;
        if(gPlayerObject) {
            px = gPlayerObject->gob_xpos;
            py = gPlayerObject->gob_ypos;
            TXT_DrawPrintF(GEX_POS(32), GEX_POS(43), "pst = %s", gObStateNames[gPlayerObject->gob_state]);
            TXT_DrawPrintF(GEX_POS(32), GEX_POS(51), "pos = %04lx.%02lx,%04lx.%02lx", px >> 0x15, (px >> 0x10) & 0x1f, py >> 0x15, (py >> 0x10) & 0x1f);
        }
        TXT_DrawPrintF(GEX_POS(32), GEX_POS(22), "blocks = %ld", gNumFreeBlocks);
        TXT_DrawPrintF(GEX_POS(32), GEX_POS(29), "Obs = %ld", gNumObjects);
        // TODO: ftime
        // TODO: sx, sy
        // TODO: delay
        // TODO: codetime, celtime
        int blockt = 0;
        const auto attr = M1_GetBlockAttributeIDAtPos(M1_CurrentLevel, px, py);
        const auto l_screens_across = M1_CurrentLevel->lvl_map->rmp_screensAcross;
        const auto l_screens_down = M1_CurrentLevel->lvl_map->rmp_screensDown;
        const auto* screen =
            M1_CurrentLevel->lvl_map->rmp_screens[GEX_POS_SCREEN_INDEX(py) * l_screens_across + GEX_POS_SCREEN_INDEX(px)];
        if(screen) {
            const auto& row = screen->rms_Rows[GEX_POS_SCREEN_ROW_INDEX(py)];
            blockt = row.rmr_plots[GEX_POS_SCREEN_ROW_INDEX(px)];
        }
        // const auto block_index = M1_CurrentLevel->lvl_map->
        int contour = -1;
        TXT_DrawPrintF(GEX_POS(32), GEX_POS(59), "attr = %ld ($%04lx) C=%ld P=$%04lx", attr, blockt, contour >> 16);
    }
}

static std::deque<std::string> debug_log_datas{};
constexpr int k_max_debug_lines = 10;

void debug_data_add_str(const char* a_str) {
    static const std::unordered_set<std::string_view> k_to_filter = {
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

    if(k_to_filter.contains(a_str))
        return;

    if(debug_log_datas.size() >= k_max_debug_lines)
        debug_log_datas.pop_front();
    debug_log_datas.emplace_back(a_str);
}

void draw_debug_data() {
    int y = GEX_POS(10);
    for(const auto& data : debug_log_datas) {
        y += GEX_POS(10);
        TXT_DrawPrintP(GEX_POS(10), y, data.c_str());
    }
}

} // namespace debug_draw
