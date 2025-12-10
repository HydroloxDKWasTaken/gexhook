#ifndef GAME_SYMBOLS_H
#define GAME_SYMBOLS_H

#include "GEX.H"

inline auto gObStateNames = ( const char** )0x00457648;
inline auto& gEnableScrolling = *( int* )0x004a2a04;
inline auto& gCurrentVK = *( int* )0x00487fd4;
inline auto& gNoProcess = *( int* )0x00455c4c;
inline auto& gTimer = *( int* )0x004a2ac8;
inline auto& level = *( int* )0x004a2964;
inline auto& M1_CurrentLevel = *( M1Level** )0x004a2990;
inline auto& gPlayerObject = *( GXObject** )0x004a27fc;
inline auto& CAMERA_XPos = *( int* )0x004a2a38;
inline auto& CAMERA_YPos = *( int* )0x004a2a1c;
inline auto& gObjectLists = *( ListType ( * )[10] )0x004a28a0;
inline auto& gNumObjects = *( int* )0x004a27a4;
inline auto& gCurrentCheatCode = *( int* )0x00455b38;
inline auto& gEnableSFX = *( int* )0x00455c08;
inline auto& gEnableVFX = *( int* )0x00455c0c;
inline auto& gEnableMUS = *( int* )0x00455c10;
inline auto& gNumFreeBlocks = *( int* )0x004a2924;
inline auto& M1_004a2a80 = *( int* )0x004a2a80;

inline auto TXT_DrawPrintP = ( void ( * )( int x, int y, const char* text ) )( 0x0043fa70 );
inline auto TXT_DrawPrintF = ( void ( * )( int x, int y, const char* text, ... ) )( 0x0043faa0 );
inline auto TXT_PixelLength = ( int ( * )( const char* text ) )( 0x0043fae0 );
inline auto M1_GetBlockAttributeIDAtPos = ( uint32_t ( * )( M1Level* level, int x, int y ) )( 0x0040f170 );
inline auto DrawARect = ( void ( * )( int unused_arg, int x1, int y1, int x2, int y2, uint32_t color, uint32_t pixc ) )( 0x00444800 );

enum class ob_type
{
    gravemap_cloud = 242,
    kungfumap_cloud = 247,
};

#endif // GAME_SYMBOLS_H
