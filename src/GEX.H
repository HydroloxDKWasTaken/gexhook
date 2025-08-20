#ifndef GEX_H
#define GEX_H
#include <stdint.h>

struct CFileInfo
{
	uint32_t cfi_fileHash; // 00
	uint32_t cfi_fileLen; // 04
	uint32_t cfi_filePos; // 08
	uint32_t cfi_fileChecksum; // 0C
	// 10
};

struct CFile;

struct CFileIOReq
{
	CFile* creq_file; // 00
	uint32_t creq_reqID; // 04
	/*READ_REQUEST*/ char cygs_rr[64]; // 08
	// 48
};


struct CFileTracker
{
	uint32_t /*unknown*/ cft_file; // 00
	CFileIOReq* cft_ioReq[8]; // 04
	uint32_t /*unknown*/ cft_ioSent[8]; // 24
	uint32_t cft_reqCheck; // 44
	uint32_t cft_reqUse; // 48
	void* cygs_fh; // 4C
	void* /*unknown*/ cygs_sr; // 50
	// 54
};

struct CFile
{
	CFileInfo* cf_fileInfo; // 00
	uint32_t cf_curPos; // 04
	CFileTracker* cf_cTrack; // 08
	CFileTracker cf_cTrackX; // 0C
	CFileInfo cf_fileInfoX; // 60
	// 70	
};

// ====== CFileIOReq is actually supposed to be HERE ======

struct CDirectory
{
	uint32_t cdir_bank; // 00
	char cdir_datDir[256]; // 04
	char** cdir_nameTbl; // 104
	CFile dir_filex; // 108
	CFileTracker cdir_fileTracker; // 178
	uint32_t cdir_numFiles; // 1CC
	CFileInfo* cdir_fileInfo; // 1D0
	// 1D4
};

struct CD_IMAGE
{
	uint32_t cdi_width; // 00
	uint32_t cdi_height; // 04
	uint32_t cdi_xOffset; // 08
	uint32_t cdi_yOffset;  // 0C
	uint32_t cdi_pixc; // 10
	// 14
};

struct CD_CEL
{
	uint32_t cel_flags; // 00
	CD_CEL* cel_nextPtr; // 04
	void* cel_sourcePtr; // 08
	void* cel_PLUTPtr; // 0C
	int32_t cel_xPos; // 10
	int32_t cel_yPos; // 14
	int32_t cel_hdx; // 18
	int32_t cel_hdy; // 1C
	int32_t cel_vdx; // 20
	int32_t cel_vdy; // 24
	int32_t cel_hddx; // 28
	int32_t cel_hddy; // 2C
	uint32_t cel_pixc; // 30
	// 34
};

struct CD_UIMAGE
{
	CD_IMAGE cdu_image; // 00
	void* cdu_data; // 14
	// 18
};

struct CD_CIMAGE
{
	CD_IMAGE cdc_image; // 00
	char cdc_plut[64]; // 14
	void* cdc_data; // 54
	// 58
};

// CD_IMAGE_NOPLUT
// CD_IMAGE_PLUT32

struct FONTPLUT
{
	void* /*unknown*/ plut; // 00
	CD_UIMAGE* cels; // 04
	uint8_t firstChar; // 08
	uint8_t lastChar;// 09
	uint8_t pad0; // 0A
	uint8_t pad1; // 0B
	uint32_t charHeight; // 0C
	uint32_t charXAdjust; // 10
	// 14
};

// FONTType

struct NodeType
{
	NodeType* nd_next; // 00
	NodeType* nd_prev; // 04
	// 08
};

struct ListType
{
	NodeType* lst_head; // 00
	NodeType* lst_tail; // 04
	NodeType* lst_tailpred; // 08
	// 0C
};

// ----------------------------------------------------------------------------
//                                 LEVELS

struct GXAniScript
{
	char* gas_scriptPtr; // 00
	uint32_t gas_waitCount; // 04
	char* gas_stackPtr; // 08
	uint32_t gas_stack[2]; // 0C
	char* gas_loopPtr; // 14
	uint32_t gas_loopVars[2]; // 18
	// 20
};

struct RM_SRow
{
	uint8_t /*unknown*/ rmr_plots[16]; // 00
	// 10
};

struct RM_Screen
{
	uint32_t rms_flags; // 00
	uint8_t /*unknown*/ rms_InitList; // 04
	RM_SRow* rms_Rows[16]; // 08
	// 88
};

struct ObjIntro
{
	uint32_t oi_position; // 00
	uint32_t oi_yndxNtype; // 04 - "Y-index and type"
	uint32_t oi_flagsNloadID; // 08 - "flags and load ID"
	void* /*unknown*/ oi_data; // 0C
	// 10
};

struct GXLoadObject;

struct RM_Map
{
	void* /*unknown*/ rmp_sounds; // 00
	uint32_t rmp_width; // 04
	uint32_t rmp_height; // 08
	uint32_t rmp_screensAcross; // 0C
	uint32_t rmp_screensDown; // 10
	uint32_t rmp_flags; // 14
	// NOTE: the number of indirection levels for these are UNKNOWN
	void** rmp_blockTable; // 18
	void** rmp_contours; // 1C
	GXLoadObject*** rmp_objectGroups; // 20 - null terminated
	void* /*unknown*/ rmp_objIntroLists; // 24
	void* /*unknown*/ rmp_tilesetList; // 28
	RM_Screen* rmp_screens; // 2C
	// 30
};

struct M1Contour;

struct M1Tile
{
	CD_UIMAGE* mt_image; // 00
	uint32_t /*unknown*/ mt_plut; // 04
	uint32_t /*unknown*/ mt_pixc; // 08
	// 0C
};

struct M1TileTable
{
	uint32_t mtt_tileID; // 00
	M1Tile mtt_tile; // 04 - probably dynamic array?
	// 10
};

struct M1Block
{
	uint16_t blk_tileID; // 00
	uint16_t blk_contourID; // 02
	uint16_t blk_contour2ID; // 04
	uint16_t blk_attributeID; // 06
	uint16_t blk_tile2ID; // 08
	uint16_t blk_alternateID; // 0A
	uint16_t blk_junk0; // 0C
	uint16_t blk_junk1; // 0E
	// 10
};

struct M1BlockAnim
{
	M1Block* ban_blocks; // 00
	uint32_t ban_blockID; // 04
	uint32_t ban_index; // 08
	uint32_t ban_timer; // 0C
	uint32_t ban_speed; // 10
	// 14
};

struct M1TileAnim
{
	M1Tile* tan_tiles;// 00
	uint32_t tan_tileID; // 04
	uint32_t tan_index; // 08
	uint32_t tan_timer; // 0C
	uint32_t tan_speed; // 10
	// 14
};

struct M1Level
{
	CDirectory* lvl_dir; // 00
	RM_Map* lvl_map; // 04
	void* lvl_mapBlk; // 08
	void* lvl_contours; // 0C
	void* lvl_contoursBlk; // 10
	M1Block* lvl_blocks; // 14 - zero terminated
	void* lvl_blocksBlk; // 18
	M1BlockAnim* lvl_blockAnims; // 1C - zero terminated
	M1Tile* lvl_tiles; // 20
	// 24
};

// ----------------------------------------------------------------------------
//                                 OBJECTS

// struct NOT from debug info!
struct ObjectIntro_Wired
{
	//     &0xffff - variable index
	//		variable index in GXObject, where 0 means gob_points (@0x68), 1 means gob_flags (@0x6c), and so on...
	//         (notably, 12 is gob_work0)
	//      said variable will be set to "data"
	// &0x10000000 - is child intro?
	//    if set, variable index is ignored, and "data" is the index of another intro
	// &0x20000000 - unused
	// &0x40000000 - unused
	// &0x80000000 - is the variable a pointer? (for example, strings, etc.)
	uint32_t type;
	uint32_t data;
};

struct ObjectIntro
{
	// &0xffff0000 - gob_xpos
	// &0x0000ffff - gob_ypos
	uint32_t oin_InitPos; // 00
	// &0x3fff - gob_type
	// &0x4000 - is enabled? (will not be added if this flag is not set)
	// &0x8000 - does object exist in game? (set and unset at runtime)
	uint32_t oin_IndexByYNType; // 04
	// &0x0000ffff - LoadID (index in rmp_objectGroups[0])
	// &0xffff0000 - Flags
	//   &0xc0000000 - valid flags (OB_FLIPX and OB_FLIPY)
	//   &0x0f000000 - object priority
	uint32_t oin_FlagsNLoadID; // 08
	ObjectIntro_Wired* /*unknown*/ oin_pWired; // 0C
	// 10
};

struct ObjectIntroTracker
{
	ObjectIntro* oit_rgOinFirst; // 00
	void* oit_pAddFunc; // 04
	uint32_t oit_cntOin; // 08
	uint32_t oit_dxWrap; // 0C
	uint32_t oit_dyWrap; // 10
	uint32_t oit_iXL; // 14
	uint32_t oit_iXR; // 18
	uint32_t oit_iYT; // 1C
	uint32_t oit_iYB; // 20
	uint32_t oit_dxScreen; // 24
	uint32_t oit_dyScreen; // 28
	uint32_t oit_cxScreen; // 2C
	uint32_t oit_cyScreen; // 30
	uint32_t oit_dpixIntro; // 34 - introduction distance in pixels
	uint32_t oit_dpixRemove; // 38 - removal distancce in pixels
	// 3C
};

struct GXHotTable
{
	uint32_t gxhtb_numTables; // 00
	void* /*unknown*/ gxhtb_tables; // 04
	// 08
};

struct GXHitArea
{
	uint32_t gxha_left; // 00
	uint32_t gxha_top; // 04
	uint32_t gxha_right; // 08
	uint32_t gxha_bottom; // 0C
	// 10
};

struct GXObImage
{
	uint32_t gximg_offset; // 00
	uint32_t gximg_flags; // 04
	CD_UIMAGE* gximg_image; // 08
	uint32_t /*unknown*/ gximg_plut; // 0C
	uint32_t /*unknown*/ gximg_pixc; // 10
	// 14
};

struct GXContour
{
	uint32_t gxcon_xoffset; // 00
	uint32_t gxcon_yoffset; // 04
	uint32_t gxcon_width; // 08
	char* gxcon_data; // 0C
	// 10
};

struct GXPath
{
	uint16_t gxpath_length; // 00
	uint16_t gxpath_startmark; // 02
	char* gxpath_data; // 04
	// 08
};

struct GXObFrame
{
	uint32_t gxfrm_left; // 00
	uint32_t gxfrm_top; // 04
	uint32_t gxfrm_right; // 08
	uint32_t gxfrm_bottom; // 0C
	GXHitArea* gxfrm_hitAreas;// 10
	GXHotTable* gxfrm_hotspots; // 14
	GXObImage* gxfrm_images; // 18
	GXPath* gxfrm_path; // 1C
	GXContour* gxfrm_contour; // 20
	// 24
};

struct GXLoadObject
{
	GXObFrame** gxlob_anims; // 00
	void** gxlob_scripts; // 04
	uint32_t gxlob_version; // 08
	uint32_t gxlob_numAnims; // 0C
	uint32_t* gxlob_numFrames; // 10 - yes, this is a pointer!
	// 14	
};

struct GXObject;
struct CollideInfo;

struct GXObjectData
{
	void (*gdat_initFunc)( GXObject*, int isRemoving ); // 00
	void (*gdat_doitFunc)( GXObject* ); // 04
	void (*gdat_drawFunc)( GXObject* ); // 08
	void (*gdat_clidFunc)( GXObject*, CollideInfo* ); // 0C
	int32_t gdat_points; // 10
	uint32_t gdat_flags; // 14 -  same as GXObject:gob_flags
	// 18
};

struct GXObjectTableEntry
{
	GXLoadObject* gte_loadData; // 00
	void* gte_initData; // 04
	// 08
};

struct GXObjectEvent
{
	uint32_t goe_eventType; // 00
	void* goe_eventScript; // 04
	// 08
};

struct CollideObject;

struct GXObject
{
	NodeType gob_node; // 00
	uint32_t gob_type; // 08
	GXLoadObject* gob_objectLoadData; // 0C
	GXAniScript gob_scripts[2]; // 10
	int32_t gob_currentFrameGroup; // 50
	int32_t gob_currentFrameIndex; // 54
	void (*gob_initFunc)( GXObject*, int isRemoving ); // 58
	void (*gob_doitFunc)( GXObject* ); // 5C
	void (*gob_drawFunc)( GXObject* ); // 60
	void (*gob_clidFunc)( GXObject*, CollideInfo* ); // 64
	uint32_t gob_points; // 68
	uint32_t gob_flags; // 6C
	uint32_t gob_state; // 70
	uint32_t gob_newState; // 74
	int32_t gob_xpos; // 78
	int32_t gob_ypos; // 7C
	int32_t gob_xVel; // 80
	int32_t gob_maxxVel; // 84
	int32_t gob_xAccl; // 88
	int32_t gob_yVel; // 8C
	int32_t gob_maxyVel; // 90
	int32_t gob_yAccl; // 94
	uint32_t gob_work0; // 98
	uint32_t gob_work1; // 9C
	uint32_t gob_work2; // A0
	uint32_t gob_work3; // A4
	uint32_t gob_work4; // A8
	uint32_t gob_work5; // AC
	uint32_t gob_work6; // B0
	uint32_t gob_work7; // B4
	int32_t gob_flashTime; // B8
	uint32_t gob_pixc; // BC
	int16_t* gob_plut; // C0
	int32_t gob_angle; // C4
	int32_t gob_xScale; // C8
	int32_t gob_yScale; // CC
	int32_t gob_removeDist; // D0
	int32_t gob_xold; // D4
	int32_t gob_yold; // D8
	int32_t gob_oldContourDist; // DC
	uint32_t gob_flags2; // E0
	int32_t gob_leftEdge; // E4
	int32_t gob_rightEdge; // E8
	int32_t gob_topEdge; // EC
	int32_t gob_bottomEdge; // F0
	uint32_t gob_oldGroup; // F4
	uint32_t gob_oldIndex; // F8
	uint32_t gob_oldFlags; // FC
	uint32_t gob_sWork0; // 100
	uint32_t gob_sWork1; // 104
	uint32_t gob_sWork2; // 108
	uint32_t gob_sWork3; // 10C
	GXObject* gob_platform; // 110
	uint32_t gob_platHitType; // 114
	uint32_t gob_dummy_for_pluts; // 118
	int16_t gob_workPLUT[32]; // 11C
	GXObject* gob_parent; // 15C
	GXObject* gob_child; // 160
	GXObject* gob_sibling; // 164
	uint32_t gob_ClidPriority; // 168
	int (*gob_pCheckClidFunc)( GXObject*, GXObject* ); // 16C
	GXHitArea* gob_phaClid; // 170
	GXHitArea* gob_phaClidWith; // 174
	GXObject* gob_pgobClidWith; // 178
	uint32_t gob_ClidWithPri; // 17C
	CollideObject* gob_pclo; // 180
	int32_t gob_checkXpos; // 184
	int32_t gob_checkYpos; // 188
	ObjectIntro* gob_poin; // 18C
	ObjectIntroTracker* gob_poit; // 190
	GXObjectEvent gob_events[12]; // 194
	uint32_t gob_lastShown; // 1F4
	uint32_t gob_last_x; // 1F8
	uint32_t gob_last_y; // 1FC
	// 200
};

// ObjectFunc
// ObListFuncPtr
// INPUT_RECORDING
// INPUT_TIMEOUT_FUNCTION
// INPUT_PLAYBACK_FUNCTION
// INPUT_EMULATION_FUNCTION

struct BUTTON_RECORD
{
	uint8_t buttonLeft; // 00
	uint8_t buttonRight; // 01
	uint8_t buttonUp; // 02
	uint8_t buttonDown; // 03
	uint8_t buttonA; // 04
	uint8_t buttonB; // 05
	uint8_t buttonC; // 06
	uint8_t buttonX; // 07
	uint8_t buttonL; // 08
	uint8_t buttonR; // 09
	uint8_t buttonStart; // 0A
	uint8_t buttonSelect; // 0B
	uint8_t buttonD; // 0C
	uint8_t buttonL2; // 0D
	uint8_t buttonR2; // 0E
	// 0F
};

struct INPUT_REMAP_TABLE
{
	uint8_t remapLeft; // 00
	uint8_t remapRight; // 01
	uint8_t remapUp; // 02
	uint8_t remapDown; // 03
	uint8_t remapA; // 04
	uint8_t remapB; // 05
	uint8_t remapC; // 06
	uint8_t remapX; // 07
	uint8_t remapL; // 08
	uint8_t remapR; // 09
	uint8_t remapStart; // 0A
	uint8_t remapSelect; // 0B
	uint8_t remapD; // 0C
	uint8_t remapL2; // 0D
	uint8_t remapR2; // 0E
	// 0F
};

struct INPUT_CODE_TABLE
{
	// types unknown for these!
	uint32_t queueSize; // 00
	uint32_t nextEntry; // 04
	uint32_t firstEntry; // 08
	uint32_t lastInputBits; // 0C
	uint32_t bitQueue; // 10
	uint32_t codes; // 14
	// 18
};

struct InputRecordingInfo
{
	// 00
	// 04
	// 08
	// 0C
	// 10
	// 14
	// 18
	// 1C
};

struct InputPlaybackInfo
{
	uint32_t playbackFlag; // 00
	void* playbackFunctionsTable; // 04 - unknown type
	void* playbackRecording; // 08 - unknown type
	uint32_t playbackCount; // 0C
	uint32_t playbackBits; // 10
	int32_t playbackAxisValue; // 14
	// 18
};

struct CONTROLLER_INFO
{
	uint32_t controllerType; // 00
	uint32_t inputBits; // 04
	uint32_t oldInputBits; // 08
	InputPlaybackInfo playbackInfo; // 0C
	// 24
};

struct GXInputRecord;

struct TileData;

struct CollideObject
{
	NodeType clo_node; // 00
	GXObject* clo_pgobThis; // 08
	// 0C
};

struct FrameInfo
{
	GXObFrame* fi_frame; // 00
	uint32_t fi_angle; // 04
	uint32_t fi_xpos; // 08
	uint32_t fi_ypos; // 0C
	uint32_t fi_xflip; // 10
	uint32_t fi_yflip; // 14
	uint32_t fi_left; // 18
	uint32_t fi_right; // 1C
	uint32_t fi_top; // 20
	uint32_t fi_bottom; // 24
	// 28
};

struct CollideInfo
{
	uint32_t /*unknown*/ cld_small; // 00
	uint32_t cld_type; // 04
	FrameInfo cld_g; // 08
	FrameInfo cld_o; // 30
	// 58
};

struct ParaObject
{
	uint32_t gdo_flags; // 00
	GXLoadObject* gdo_objectLoadData; // 04
	uint32_t gdo_currentFrameGroup; // 08
	uint32_t gdo_currentFrameNdx; // 0C
	int32_t gdo_xoffset; // 10
	int32_t gdo_yoffset; // 14
	int32_t gdo_dist; // 18
	int32_t gdo_animSpeed; // 1C
	int32_t gdo_animTimer; // 20
	// 24
};

struct ParaStrip
{
	uint32_t prs_flags; // 00
	int32_t prs_xOffset; // 04
	int32_t prs_yPos; // 08
	int32_t prs_yPos2; // 0C
	uint32_t prs_xSpeed; // 10
	uint32_t prs_ySpeed; // 14
	uint32_t prs_xVel; // 18
	uint32_t prs_yVel; // 1C
	int32_t prs_xold; // 20
	int32_t prs_yold; // 24
	uint32_t prs_firstImageNdx; // 28
	uint32_t prs_lastImageNdx; // 2C
	void* prs_objects; // 30
	// 34
};

struct Parallax
{
	uint32_t par_flags; // 00
	int32_t par_height; // 04
	int32_t par_oldXPos; // 08
	int32_t par_oldYPos; // 0C
	int32_t par_yPos; // 10
	int32_t par_ySpeed; // 14
	void* /*probably ParaStrip* */ par_strips; // 18
	// 1C
};

#endif
