cmake_minimum_required( VERSION 3.31 )
project( gexhook )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32" )
set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32" )
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

include( FetchContent )
set( SUBHOOK_TESTS OFF )
set( SUBHOOK_STATIC ON )
FetchContent_Declare(
    subhook
    GIT_REPOSITORY https://github.com/p5-vbnekit/subhook.forks.git
)
FetchContent_MakeAvailable( subhook )

add_library( gexhook SHARED src/main.cpp )
target_link_libraries( gexhook PRIVATE subhook::subhook )
set_target_properties( gexhook PROPERTIES COMPILE_OPTIONS "-m32" LINK_FLAGS "-m32" )
set_target_properties( gexhook PROPERTIES SUFFIX ".asi" )
