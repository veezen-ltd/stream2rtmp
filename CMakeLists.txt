cmake_minimum_required(VERSION 3.21)
project(veezen2rtmp)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)
#set(DOWNLOAD_DIR /home/b0n3/Downloads)
add_executable(veezen2rtmp main.cpp)
find_package(boost_context )
find_package(yarpl)
find_package(rsocket)
find_package(folly)

target_include_directories(veezen2rtmp PUBLIC /usr/local/include/folly)
target_include_directories(veezen2rtmp PUBLIC /usr/local/include/yarpl)
target_include_directories(veezen2rtmp PUBLIC /usr/local/include/rsocket)

target_link_libraries(veezen2rtmp PUBLIC pthread gflags ${GFLAGS_LIBRARY}  glog boost_context folly yarpl rsocket)

#target_include_directories(veezen2rtmp PRIVATE ./includes)
#target_link_libraries(veezen2rtmp PRIVATE ./src)

#find_package(folly)
#target_link_libraries(${PROJECT_NAME} Folly::folly)
#set(RSOCKET_DIR ./lib/rsocket)
#set(RSOCKET_LIBRARY_DIR ./lib/rsocket/lib)
#set(RSOCKET_INCLUDE_DIR ./lib/rsocket/include)
#
#ExternalProject_Add(rsocket
#        URL file://${DOWNLOAD_DIR}/rsocket-cpp-v2021.08.30.00.zip
#        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rsocket
#        )
#
#ExternalProject_Get_Property(rsocket install_dir)
#set(rsocket_install_dir ${install_dir})
#include_directories(${rsocket_install_dir}/include)
#
##add_dependencies(veezen2rtmp rsocket)
#find_package(yarpl)
#find_package(rsocket)
#target_link_libraries(veezen2rtmp  rsocket::Rsocket)
