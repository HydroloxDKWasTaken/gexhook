#ifndef GEX_H
#define GEX_H
#include <stddef.h> // offsetof
#include <stdint.h>

// Helpers for Ghidra, since it will likely not find stdint.h
#ifndef UINT32_MAX
#define uint32_t unsigned int
#define int32_t int
#define uint16_t unsigned short
#define int16_t short
#define uint8_t unsigned char
#define int8_t signed char
#endif

// 3do: struct ErrorText (operror.h)
// 3do: enum errtxt_tags (operror.h)
// 3do: struct Timer (timer.h)
// 3do: enum timer_tags (timer.h)
// 3do: struct DiscLabel (discdata.h)
// 3do: struct DirectoryHeader (discdata.h)
// 3do: struct DirectoryRecord (discdata.h)
// 3do: struct Device (device.h)
// 3do: enum device_tags (device.h)
// 3do: struct TimerDevice (device.h)
// 3do: struct Driver (driver.h)
// 3do: enum driver_tags (driver.h)
// 3do: struct DeviceStatus (driver.h)
// 3do: struct RamDeviceStatus (driver.h)
// 3do: struct XBusDeviceStatus (driver.h)
// 3do: typedef HighLevelDisk (filesystem.h)
// 3do: typedef File (filesystem.h)
// 3do: typedef FileDriverQueueIt (filesystem.h)
// 3do: typedef FileDriverHook (filesystem.h)
// 3do: typedef FileDriverEA (filesystem.h)
// 3do: typedef FileDriverAbort (filesystem.h)
// 3do: typedef FileDriverEntry (filesystem.h)
// 3do: typedef FileDriverAlloc (filesystem.h)
// 3do: typedef FileDriverClose (filesystem.h)
// 3do: struct OptimizedDisk (filesystem.h)
// 3do: struct MacFileInfo (filesystem.h)
// 3do: struct MacDirectoryEntry (filesystem.h)
// 3do: struct MacDisk (filesystem.h)
// 3do: struct LinkedMemBlock (filesystem.h)
// 3do: struct LinkedMemFileEntrry (filesystem.h)
// 3do: enum LinkedMemDiskFSM (filesystem.h)
// 3do: struct LinkedMemDisk (filesystem.h)
// 3do: struct FileSystem (filesystem.h)
// 3do: struct File (filesystem.h)
// 3do: struct OpenFile (filesystem.h)
// 3do: struct BufferedFile (filesystem.h)
// 3do: struct FileIOReq (filesystem.h)
// 3do: struct FileStatus (filesystem.h)
// 3do: struct IoCacheEntry (filesystem.h)
// 3do: enum SchedulerSweepDirection (filesystem.h)
// 3do: struct Alias (filesystem.h)
// 3do: struct FileFolio (filesystem.h)
// 3do: struct FileFolioTaskData (filesystem.h)
// 3do: struct FileSystemEntry (filesystem.h)
// 3do: enum SeekOrigin (filestream.h)
// 3do: struct Stream (filestream.h)
// 3do: typedef VDLEntry (graphics.i)
// 3do: typedef Color (graphics.i)
// 3do: typedef Coord (graphics.i)
// 3do: typedef RGB888 (graphics.i)
// 3do: typedef CharMap (graphics.i)
// 3do: struct FontEntry (graphics.i)
// 3do: struct ScreenGroup (graphics.i)
// 3do: struct DisplayInfo (graphics.i)
// 3do: struct Bitmap (graphics.i)
// 3do: struct VDL (graphics.i)
// 3do: struct Screen (graphics.i)
// 3do: struct BitmapInfo (graphics.i)
// 3do: struct ScreenInfo (graphics.i)
// 3do: struct Point (graphics.i)
// 3do: struct Rect (graphics.i)
// 3do: struct GrafCon (graphics.i)
// 3do: struct CCB (graphics.i)
// 3do: struct FontChar (graphics.i)
// 3do: struct Font (graphics.i)
// 3do: struct GrafFolio (graphics.i)
// 3do: typedef frac16 (operamath.i)
// 3do: typedef frac30 (operamath.i)
// 3do: typedef frac14 (operamath.i)
// 3do: typedef ufrac16 (operamath.i)
// 3do: typedef ufrac30 (operamath.i)
// 3do: typedef ufrac14 (operamath.i)
// 3do: struct int64 (operamath.i)
// 3do: typedef uint64 (operamath.i)
// 3do: typedef frac32 (operamath.i)
// 3do: typedef ufrac32 (operamath.i)
// 3do: typedef frac60 (operamath.i)
// 3do: typedef ufrac60 (operamath.i)
// 3do: typedef vec3f16 (operamath.i)
// 3do: typedef vec4f16 (operamath.i)
// 3do: typedef mat33f16 (operamath.i)
// 3do: typedef mat44f16 (operamath.i)
// 3do: typedef mat34f16 (operamath.i)
// 3do: typedef vec3f30 (operamath.h)
// 3do: typedef vec4f30 (operamath.h)
// 3do: typedef mat33f30 (operamath.h)
// 3do: typedef mat44f30 (operamath.h)
// 3do: typedef mat34f30 (operamath.h)
// 3do: struct MathFolio (operamath.i)
// 3do: struct mmv3mm33d (operamath.i)
// 3do: struct ObjOffset1 (operamath.i)
// 3do: struct ObjOffset2 (operamath.i)
// 3do: enum audio_folio_tags (audio.h)
// 3do: enum DSPPResourceTypes (audio.h)
// 3do: typedef AudioTime (audio.h)
// 3do: struct DataTimePair (audio.h)
// 3do: typedef Int8 (form3do.h)
// 3do: typedef UInt8 (form3do.h)
// 3do: typedef Int16 (form3do.h)
// 3do: typedef UInt16 (form3do.h)
// 3do: typedef Int32 (form3do.h)
// 3do: typedef UInt32 (form3do.h)
// 3do: typedef RGB555 (form3do.h)
// 3do: struct RGB888 (form3do.h)
// 3do: struct WrapperChunk (form3do.h)
// 3do: struct ImageCC (form3do.h)
// 3do: struct PixelChunk (form3do.h)
// 3do: struct CCC (form3do.h)
// 3do: struct LoopRec (form3do.h)
// 3do: struct AnimChunk (form3do.h)
// 3do: struct PLUTChunk (form3do.h)
// 3do: struct VDL_REC (form3do.h)
// 3do: struct VDLCHUNK (form3do.h)
// 3do: struct Cpyr (form3do.h)
// 3do: struct Desc (form3do.h)
// 3do: struct Kwrd (form3do.h)
// 3do: struct Crdt (form3do.h)
// 3do: struct ScreenContext_TAG (init3do.h)
// 3do: struct tag_AnimFrame (parse3do.h)
// 3do: struct tag_ANIM (parse3do.h)
// 3do: struct tag_SoundInfo (parse3do.h)
// 3do: struct tag_Rectf16 (utils3do.h)
// 3do: struct tag_MoveVect (utils3do.h)
// 3do: struct tag_MoveRec (utils3do.h)
// 3do: struct CelLink (utils3do.h)


/*
 * NOTE: These structs vary A LOT depending on the platform!
 *   The Windows versions are much simpler, and the PSX versions more complex (i.e. larger)
 *   CFileInfo seems to be the only exception to this rule.
 */
typedef struct CFileInfo
{
	uint32_t cfi_fileHash; // 00
	uint32_t cfi_fileLen; // 04
	uint32_t cfi_filePos; // 08
	uint32_t cfi_fileChecksum; // 0C
	// 10
} CFileInfo;

typedef struct CFileTracker
{
	int32_t cft_file; // 00
	int32_t cft_ioReq[8]; // 04
	uint32_t cft_ioSent[8]; // 24
	uint32_t cft_reqCheck; // 44
	uint32_t cft_reqUse; // 48
	int32_t cygs_fh; // 4C
	int32_t cygs_sr; // 50
	// 54
} CFileTracker;

typedef struct CFile
{
	CFileInfo* cf_fileInfo; // 00
	uint32_t cf_curPos; // 04
	CFileTracker* cf_cTrack; // 08
	CFileTracker cf_cTrackX; // 0C
	CFileInfo cf_fileInfoX; // 60
	// 70	
} CFile;

typedef struct CFileIOReq
{
	CFile* creq_file; // 00
	uint32_t creq_reqID; // 04
	/*READ_REQUEST*/ char cygs_rr[64]; // 08
	// 48
} CFileIOReq;

typedef struct CDirectory
{
	uint32_t cdir_bank; // 00
	char cdir_datDir[256]; // 04
	char** cdir_nameTbl; // 104
	CFile dir_filex; // 108
	CFileTracker cdir_fileTracker; // 178
	uint32_t cdir_numFiles; // 1CC
	CFileInfo* cdir_fileInfo; // 1D0
	// 1D4
} CDirectory;

typedef struct CD_IMAGE
{
	int32_t cdi_width; // 00
	int32_t cdi_height; // 04
	int32_t cdi_xOffset; // 08
	int32_t cdi_yOffset;  // 0C
	uint32_t cdi_pixc; // 10
	// 14
} CD_IMAGE;

typedef struct CD_CEL
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
} CD_CEL;

typedef struct CD_UIMAGE
{
	CD_IMAGE cdu_image; // 00
	uint32_t cdu_data[1]; // 14
	// 18
} CD_UIMAGE;

typedef struct CD_CIMAGE
{
	CD_IMAGE cdc_image; // 00
	uint16_t cdc_plut[32]; // 14
	uint32_t cdc_data[1]; // 54
	// 58
} CD_CIMAGE;

typedef CD_UIMAGE CD_IMAGE_NOPLUT;
typedef CD_CIMAGE CD_IMAGE_PLUT32;

typedef struct {
	uint16_t data[32];
} FONTPLUT;

typedef struct FONTType
{
	FONTPLUT* plut; // 00
	CD_UIMAGE** cels; // 04
	uint8_t firstChar; // 08
	uint8_t lastChar;// 09
	uint8_t pad0; // 0A
	uint8_t pad1; // 0B
	int32_t charHeight; // 0C
	int32_t charXAdjust; // 10
	// 14
} FONTType;

typedef struct NodeType
{
	NodeType* nd_next; // 00
	NodeType* nd_prev; // 04
	// 08
} NodeType;

typedef struct ListType
{
	NodeType* lst_head; // 00
	NodeType* lst_tail; // 04
	NodeType* lst_tailPred; // 08
	// 0C
} ListType;

// ----------------------------------------------------------------------------
//                                 LEVELS

typedef struct GXAniScript
{
	char* gas_scriptPtr; // 00
	uint32_t gas_waitCount; // 04
	char* gas_stackPtr; // 08
	uint32_t gas_stack[2]; // 0C
	char* gas_loopPtr; // 14
	uint32_t gas_loopVars[2]; // 18
	// 20
} GXAniScript;

typedef struct RM_SRow
{
	uint16_t rmr_plots[8]; // 00
	// 10
} RM_SRow;

typedef struct RM_Screen
{
	uint32_t rms_flags; // 00
	void* rms_InitList; // 04
	RM_SRow rms_Rows[8]; // 08
	// 88
} RM_Screen;

typedef struct ObjIntro
{
	uint32_t oi_position; // 00
	uint32_t oi_yndxNtype; // 04 - "Y-index and type"
	uint32_t oi_flagsNloadID; // 08 - "flags and load ID"
	void* oi_data; // 0C
	// 10
} ObjIntro;

typedef struct RM_Map
{
	void** rmp_sounds; // 00
	int32_t rmp_width; // 04
	int32_t rmp_height; // 08
	int32_t rmp_screensAcross; // 0C
	int32_t rmp_screensDown; // 10
	int32_t rmp_flags; // 14
	void* rmp_blockTable; // 18
	void* rmp_contours; // 1C
	void** rmp_objectGroups; // 20
	void** rmp_objIntroLists; // 24
	void** rmp_tilesetList; // 28
	RM_Screen* rmp_screens[1]; // 2C - array of size rmp_screensAcross * rmp_screensDown
	// 30
} RM_Map;

typedef uint8_t M1Contour[32];

typedef struct M1Tile
{
	CD_UIMAGE* mt_image; // 00
	uint16_t* mt_plut; // 04
	uint32_t mt_pixc; // 08
	// 0C
} M1Tile;

typedef struct M1TileTable
{
	int32_t mtt_tileID; // 00
	M1Tile mtt_tile; // 04
	// 10
} M1TileTable;

typedef struct M1Block
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
} M1Block;

typedef struct M1BlockAnim
{
	M1Block* ban_blocks; // 00
	int32_t ban_blockID; // 04
	int32_t ban_index; // 08
	int32_t ban_timer; // 0C
	int32_t ban_speed; // 10
	// 14
} M1BlockAnim;

typedef struct M1TileAnim
{
	M1Tile* tan_tiles;// 00
	int32_t tan_tileID; // 04
	int32_t tan_index; // 08
	int32_t tan_timer; // 0C
	int32_t tan_speed; // 10
	// 14
} M1TileAnim;

typedef struct M1Level
{
	CDirectory* lvl_dir; // 00
	RM_Map* lvl_map; // 04
	void** lvl_mapBlk; // 08
	M1Contour** lvl_contours; // 0C
	void** lvl_contoursBlk; // 10
	M1Block** lvl_blocks; // 14 - zero terminated
	void** lvl_blocksBlk; // 18
	M1BlockAnim* lvl_blockAnims; // 1C - zero terminated
	M1Tile* lvl_tiles; // 20
	// 24
} M1Level;

// ----------------------------------------------------------------------------
//                                 OBJECTS

// struct NOT from debug info!
struct ObjectIntro_Wired
{
	//     &0xffff - variable index
	//		variable index in GXObject, where 0 means gob_points (@0x68), 1 means gob_flags (@0x6c), and so on...
	//         (notably, 12 is gob_work0). see the OBVAR_ macros for this.
	//      said variable will be set to "data"
	// &0x10000000 - is child intro?
	//    if set, variable index is ignored, and "data" is the index of another intro
	// &0x20000000 - unused
	// &0x40000000 - unused
	// &0x80000000 - is the variable a pointer? (for example, strings, etc.)
	uint32_t type;
	uint32_t data;
};

typedef struct ObjectIntro
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
	ObjectIntro_Wired* oin_pWired; // 0C
	// 10
} ObjectIntro;

typedef struct ObjectIntroTracker
{
	ObjectIntro* oit_rgOinFirst; // 00
	void* oit_pAddFunc; // 04
	int32_t oit_cntOin; // 08
	int32_t oit_dxWrap; // 0C
	int32_t oit_dyWrap; // 10
	int32_t oit_iXL; // 14
	int32_t oit_iXR; // 18
	int32_t oit_iYT; // 1C
	int32_t oit_iYB; // 20
	int32_t oit_dxScreen; // 24
	int32_t oit_dyScreen; // 28
	int32_t oit_cxScreen; // 2C
	int32_t oit_cyScreen; // 30
	int32_t oit_dpixIntro; // 34 - introduction distance in pixels
	int32_t oit_dpixRemove; // 38 - removal distancce in pixels
	// 3C
} ObjectIntroTracker;

typedef struct GXHotTable
{
	int32_t gxhtb_numTables; // 00
	// gxhtb_tables[x]:
	//   gxhtb_tables[x][0] - number of hotspots
	//   gxhtb_tables[x][1] - hotspot 1 x
	//   gxhtb_tables[x][2] - hotspot 1 y
	//   gxhtb_tables[x][3] - hotspot 2 x
	//   ...
	int32_t** gxhtb_tables; // 04
	// 08
} GXHotTable;

typedef struct GXHitArea
{
	int32_t gxha_left; // 00
	int32_t gxha_top; // 04
	int32_t gxha_right; // 08
	int32_t gxha_bottom; // 0C
	// 10
} GXHitArea;

typedef struct GXObImage
{
	int32_t gximg_offset; // 00
	int32_t gximg_flags; // 04
	CD_UIMAGE* gximg_image; // 08
	uint16_t* gximg_plut; // 0C
	int32_t gximg_pixc; // 10
	// 14
} GXObImage;

typedef struct GXContour
{
	uint32_t gxcon_xoffset; // 00
	uint32_t gxcon_yoffset; // 04
	uint32_t gxcon_width; // 08
	uint8_t gxcon_data[4]; // 0C
	// 10
} GXContour;

typedef struct GXPath
{
	uint16_t gxpath_length; // 00
	uint8_t gxpath_startmark[2]; // 02
	uint8_t gxpath_data[4]; // 04
	// 08
} GXPath;

typedef struct GXObFrame
{
	int32_t gxfrm_left; // 00
	int32_t gxfrm_top; // 04
	int32_t gxfrm_right; // 08
	int32_t gxfrm_bottom; // 0C
	GXHitArea* gxfrm_hitAreas;// 10
	GXHotTable* gxfrm_hotspots; // 14
	GXObImage** gxfrm_images; // 18
	GXPath* gxfrm_path; // 1C
	GXContour* gxfrm_contour; // 20
	// 24
} GXObFrame;

typedef struct GXLoadObject
{
	GXObFrame** gxlob_anims; // 00
	uint8_t** gxlob_scripts; // 04
	uint32_t gxlob_version; // 08
	int32_t gxlob_numAnims; // 0C
	int32_t* gxlob_numFrames; // 10 - yes, this is a pointer!
	// 14	
} GXLoadObject;

typedef struct GXObject GXObject;
typedef struct CollideInfo CollideInfo;

typedef struct GXObjectData
{
	void (*gdat_initFunc)( GXObject*, int isRemoving ); // 00
	void (*gdat_doitFunc)( GXObject* ); // 04
	void (*gdat_drawFunc)( GXObject* ); // 08
	void (*gdat_clidFunc)( GXObject*, CollideInfo* ); // 0C
	uint32_t gdat_points; // 10 - score given when the ob is killed/activated/whatever
	uint32_t gdat_flags; // 14 -  same as GXObject:gob_flags
	// 18
} GXObjectData;

typedef struct GXObjecTableEntry // [sic]
{
	GXLoadObject* gte_loadData; // 00
	void* gte_initData; // 04
	// 08
} GXObjecTableEntry;

typedef struct GXObjectEvent
{
	uint32_t goe_eventType; // 00
	void* goe_eventScript; // 04
	// 08
} GXObjectEvent;

typedef struct CollideObject CollideObject;

typedef struct GXObject
{
	NodeType gob_node; // 00
	int32_t gob_type; // 08
	GXLoadObject* gob_objectLoadData; // 0C
	GXAniScript gob_scripts[2]; // 10
	int32_t gob_currentFrameGroup; // 50
	int32_t gob_currentFrameIndex; // 54
	void (*gob_initFunc)( GXObject*, int isRemoving ); // 58
	void (*gob_doitFunc)( GXObject* ); // 5C
	void (*gob_drawFunc)( GXObject* ); // 60
	void (*gob_clidFunc)( GXObject*, CollideInfo* ); // 64
	uint32_t gob_points; // 68
#define OB_LAYER_MASK    0xf
#define OB_CLDPRIO_MASK  0xf0
#define OB_CLDTYPE_MASK  0xf00
// 0x1000 is unused
#define OB_IS_MAPOBJECT  0x2000
#define OB_ALLOWXCHANGE  0x4000
#define OB_ALLOWYCHANGE  0x8000
// 0x10000 is unknown
// 0x20000 is unknown
// 0x40000 is unknown
// 0x80000 is unknown
#define OB_REMOVED 		 0x100000
#define OB_TRYING_TO_EAT 0x200000
// 0x400000 is unknown
#define OB_PARAOBJECT 	 0x800000
#define OB_EVENTMASK 	 0x1f000000
// 0x2000000 is unknown
#define OB_FLIPY 		 0x40000000
#define OB_FLIPX 		 0x80000000
	uint32_t gob_flags; // 6C
	int32_t gob_state; // 70
	int32_t gob_newState; // 74
	int32_t gob_xpos; // 78
	int32_t gob_ypos; // 7C
	int32_t gob_xVel; // 80
	int32_t gob_maxxVel; // 84
	int32_t gob_xAccl; // 88
	int32_t gob_yVel; // 8C
	int32_t gob_maxyVel; // 90
	int32_t gob_yAccl; // 94
	int32_t gob_work0; // 98
	int32_t gob_work1; // 9C
	int32_t gob_work2; // A0
	int32_t gob_work3; // A4
	int32_t gob_work4; // A8
	int32_t gob_work5; // AC
	int32_t gob_work6; // B0
	int32_t gob_work7; // B4
	int32_t gob_flashTime; // B8
	uint32_t gob_pixc; // BC
	void* gob_plut; // C0
	int32_t gob_angle; // C4
	int32_t gob_xScale; // C8
	int32_t gob_yScale; // CC
	int32_t gob_removeDist; // D0
	int32_t gob_xold; // D4
	int32_t gob_yold; // D8
	int32_t gob_oldContourDist; // DC
	int32_t gob_flags2; // E0
	int32_t gob_leftEdge; // E4
	int32_t gob_rightEdge; // E8
	int32_t gob_topEdge; // EC
	int32_t gob_bottomEdge; // F0
	int32_t gob_oldGroup; // F4
	int32_t gob_oldIndex; // F8
	int32_t gob_oldFlags; // FC
	int32_t gob_sWork0; // 100
	int32_t gob_sWork1; // 104
	int32_t gob_sWork2; // 108
	int32_t gob_sWork3; // 10C
	GXObject* gob_platform; // 110
	int32_t gob_platHitType; // 114
	int32_t gob_dummy_for_pluts; // 118
	uint16_t gob_workPLUT[32]; // 11C
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
	int32_t gob_lastShown; // 1F4
	int32_t gob_last_x; // 1F8
	int32_t gob_last_y; // 1FC
	// 200
} GXObject;
// the prefix OBVAR_ is known thanks to a script in the retail 3do version
// "SHOOTTV : OBVAR_WORK7 is ZERO!!!"
#define OBVAR_BASE_OFFSET offsetof( GXObject, gob_xpos )
#define OBVAR_OFFSET(f) ( ( OBVAR_BASE_OFFSET - offsetof( GXObject, f ) ) / 4 )

#define OBVAR_POINTS OBVAR_OFFSET( gob_points )
#define OBVAR_FLAGS OBVAR_OFFSET( gob_flags )
#define OBVAR_STATE OBVAR_OFFSET( gob_state )
#define OBVAR_NEWSTATE OBVAR_OFFSET( gob_newState )
#define OBVAR_XPOS OBVAR_OFFSET( gob_xpos )
#define OBVAR_YPOS OBVAR_OFFSET( gob_ypos )
#define OBVAR_XVEL OBVAR_OFFSET( gob_xVel )
#define OBVAR_MAXXVEL OBVAR_OFFSET( gob_maxxVel )
#define OBVAR_XACCL OBVAR_OFFSET( gob_xAccl )
#define OBVAR_YVEL OBVAR_OFFSET( gob_yVel )
#define OBVAR_MAXYVEL OBVAR_OFFSET( gob_maxyVel )
#define OBVAR_YACCL OBVAR_OFFSET( gob_yAccl )
#define OBVAR_WORK0 OBVAR_OFFSET( gob_work0 )
#define OBVAR_WORK1 OBVAR_OFFSET( gob_work1 )
#define OBVAR_WORK2 OBVAR_OFFSET( gob_work2 )
#define OBVAR_WORK3 OBVAR_OFFSET( gob_work3 )
#define OBVAR_WORK4 OBVAR_OFFSET( gob_work4 )
#define OBVAR_WORK5 OBVAR_OFFSET( gob_work5 )
#define OBVAR_WORK6 OBVAR_OFFSET( gob_work6 )
#define OBVAR_WORK7 OBVAR_OFFSET( gob_work7 )
#define OBVAR_FLASHTIME OBVAR_OFFSET( gob_flashTime )
#define OBVAR_PIXC OBVAR_OFFSET( gob_pixc )
// #define OBVAR_PLUT OBVAR_OFFSET( gob_plut ) - ptr so probably not used
#define OBVAR_ANGLE OBVAR_OFFSET( gob_angle )
#define OBVAR_XSCALE OBVAR_OFFSET( gob_xScale )
#define OBVAR_YSCALE OBVAR_OFFSET( gob_yScale )
#define OBVAR_REMOVEDIST OBVAR_OFFSET( gob_removeDist )
#define OBVAR_XOLD OBVAR_OFFSET( gob_xold )
#define OBVAR_YOLD OBVAR_OFFSET( gob_yold )
#define OBVAR_OLDCONTOURDIST OBVAR_OFFSET( gob_oldContourDist )
#define OBVAR_FLAGS2 OBVAR_OFFSET( gob_flags2 )
#define OBVAR_LEFTEDGE OBVAR_OFFSET( gob_leftEdge )
#define OBVAR_RIGHTEDGE OBVAR_OFFSET( gob_rightEdge )
#define OBVAR_TOPEDGE OBVAR_OFFSET( gob_topEdge )
#define OBVAR_BOTTOMEDGE OBVAR_OFFSET( gob_bottomEdge )
#define OBVAR_OLDGROUP OBVAR_OFFSET( gob_oldGroup )
#define OBVAR_OLDINDEX OBVAR_OFFSET( gob_oldIndex )
#define OBVAR_OLDFLAGS OBVAR_OFFSET( gob_oldFlags )
#define OBVAR_SWORK0 OBVAR_OFFSET( gob_sWork0 )
#define OBVAR_SWORK1 OBVAR_OFFSET( gob_sWork1 )
#define OBVAR_SWORK2 OBVAR_OFFSET( gob_sWork2 )
#define OBVAR_SWORK3 OBVAR_OFFSET( gob_sWork3 )
// #define OBVAR_PLATFORM OBVAR_OFFSET( gob_platform ) - ptr
#define OBVAR_PLATHITTYPE OBVAR_OFFSET( gob_platHitType )
// #define OBVAR_WORKPLUT OBVAR_OFFSET( gob_workPLUT ) - ptr
// #define OBVAR_PARENT OBVAR_OFFSET( gob_parent ) - ptr
// #define OBVAR_CHILD OBVAR_OFFSET( gob_child ) - ptr
// #define OBVAR_SIBLING OBVAR_OFFSET( gob_sibling ) - ptr
#define OBVAR_CLIDPRIORITY OBVAR_OFFSET( gob_ClidPriority )
// #define OBVAR_PCHECKCLIDFUNC OBVAR_OFFSET( gob_pCheckClidFunc ) - ptr
// #define OBVAR_PHACLID OBVAR_OFFSET( gob_phaClid ) - ptr
// #define OBVAR_PHACLIDWITH OBVAR_OFFSET( gob_phaClidWith ) - ptr
// #define OBVAR_PGOBCLIDWITH OBVAR_OFFSET( gob_pgobClidWith ) - ptr
#define OBVAR_CLIDWITHPRI OBVAR_OFFSET( gob_ClidWithPri )
// #define OBVAR_PCLO OBVAR_OFFSET( gob_pclo )
#define OBVAR_CHECKXPOS OBVAR_OFFSET( gob_checkXpos )
#define OBVAR_CHECKYPOS OBVAR_OFFSET( gob_checkYpos )
// #define OBVAR_POIN OBVAR_OFFSET( gob_poin ) - ptr
// #define OBVAR_POIT OBVAR_OFFSET( gob_poit ) - ptr
// #define OBVAR_EVENTS OBVAR_OFFSET( gob_events ) - ptr
#define OBVAR_LASTSHOWN OBVAR_OFFSET( gob_lastShown )
#define OBVAR_LASTX OBVAR_OFFSET( gob_last_x )
#define OBVAR_LASTY OBVAR_OFFSET( gob_last_y )

// ObjectFunc
// ObListFuncPtr
// INPUT_RECORDING
// INPUT_TIMEOUT_FUNCTION
// INPUT_PLAYBACK_FUNCTION
// INPUT_EMULATION_FUNCTION

typedef struct
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
} BUTTON_RECORD;

typedef struct
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
} INPUT_REMAP_TABLE;

typedef struct
{
	int32_t queueSize; // 00
	int32_t nextEntry; // 04
	int32_t firstEntry; // 08
	uint32_t lastInputBits; // 0C
	uint32_t* bitQueue; // 10
	uint32_t** codes; // 14
	// 18
} INPUT_CODE_TABLE;

typedef struct
{
	int32_t recordingFlag; // 00
	void* recordingFile; // 04
	int32_t inputRecordingType; // 08
	int32_t lastRecordingType; // 0C
	uint32_t lastReadBits; // 10
	int32_t lastReadAxis; // 14
	int32_t lastReadAxisValue; // 18
	// 1C
} InputRecordingInfo;

typedef struct
{
	int32_t playbackFlag; // 00
	uint8_t** playbackFunctionsTable; // 04
	uint8_t* playbackRecording; // 08
	int32_t playbackCount; // 0C
	uint32_t playbackBits; // 10
	int32_t playbackAxisValue; // 14
	// 18
} InputPlaybackInfo;

typedef struct
{
	int32_t controllerType; // 00
	uint32_t inputBits; // 04
	uint32_t oldInputBits; // 08
	InputPlaybackInfo playbackInfo; // 0C
	// 24
} CONTROLLER_INFO;

typedef struct
{
	BUTTON_RECORD gxir_padButtons; // 00
	BUTTON_RECORD gxir_padJustOnButtons; // 0F
	int32_t gxir_dValue; // 20
	// 24
} GXInputRecord;

typedef struct TileData
{
	uint32_t til_flags; // 00
	int32_t til_data; // 04
	void* til_ptr; // 08
	void* til_leftFunc; // 0C
	void* til_rightFunc; // 10
	void* til_upFunc; // 14
	void* til_downFunc; // 18
	void* til_groundFunc; // 1C
	// 20
} TileData;

typedef struct CollideObject
{
	NodeType clo_node; // 00
	GXObject* clo_pgobThis; // 08
	// 0C
} CollideObject;

typedef struct FrameInfo
{
	GXObFrame* fi_frame; // 00
	int32_t fi_angle; // 04
	int32_t fi_xpos; // 08
	int32_t fi_ypos; // 0C
	int32_t fi_xflip; // 10
	int32_t fi_yflip; // 14
	int32_t fi_left; // 18
	int32_t fi_right; // 1C
	int32_t fi_top; // 20
	int32_t fi_bottom; // 24
	// 28
} FrameInfo;

typedef struct CollideInfo
{
	int32_t cld_small; // 00
	int32_t cld_type; // 04
	FrameInfo cld_g; // 08
	FrameInfo cld_o; // 30
	// 58
} CollideInfo;

typedef struct ParaObject
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
} ParaObject;

typedef struct ParaStrip
{
	uint32_t prs_flags; // 00
	int32_t prs_xOffset; // 04
	int32_t prs_yPos; // 08
	int32_t prs_yPos2; // 0C
	int32_t prs_xSpeed; // 10
	int32_t prs_ySpeed; // 14
	int32_t prs_xVel; // 18
	int32_t prs_yVel; // 1C
	int32_t prs_xold; // 20
	int32_t prs_yold; // 24
	int32_t prs_firstImageNdx; // 28
	int32_t prs_lastImageNdx; // 2C
	void* prs_objects; // 30
	// 34
} ParaStrip;

typedef struct Parallax
{
	uint32_t par_flags; // 00
	int32_t par_height; // 04
	int32_t par_oldXPos; // 08
	int32_t par_oldYPos; // 0C
	uint32_t par_yPos; // 10
	int32_t par_ySpeed; // 14
	void* /*probably ParaStrip* */ par_strips; // 18
	// 1C
} Parallax;

#endif
