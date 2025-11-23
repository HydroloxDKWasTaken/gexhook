cmake_minimum_required( VERSION 3.31 )
project( gexhook VERSION 1.0 )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32" )
set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32" )
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

include( FetchContent )
set( SUBHOOK_TESTS OFF )
set( SUBHOOK_STATIC ON )
set( SUBHOOK_INSTALL OFF )
FetchContent_Declare(
    subhook
    GIT_REPOSITORY https://github.com/p5-vbnekit/subhook.forks.git
)
FetchContent_MakeAvailable( subhook )

add_library( gexhook SHARED 
    src/debug_draw.cpp
    src/debug_draw.h
    src/debug_menu.cpp
    src/debug_menu.h
    src/game.h
    src/GEX.H
    src/global.h
    src/main.cpp
    src/menus.h
)

target_link_libraries( gexhook PRIVATE subhook::subhook )
set_target_properties( gexhook PROPERTIES COMPILE_OPTIONS "-m32" LINK_FLAGS "-m32" )
set_target_properties( gexhook PROPERTIES SUFFIX ".asi" )

install( TARGETS gexhook
         RUNTIME DESTINATION . )
install( FILES $<TARGET_PDB_FILE:gexhook>
         DESTINATION . OPTIONAL )
set( CPACK_GENERATOR "ZIP" )
set( CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF )
set( CPACK_PACKAGE_FILE_NAME "gexhook-${PROJECT_VERSION}" )
include( CPack )
