cmake_minimum_required(VERSION 3.21)
project(veezen2rtmp)
#include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)
set(RSOCKET_IMPL_DIR src/rsocket_implementation/src)

set(UTILS_DIR src/utils)

file(GLOB utils_SRC
        "${UTILS_DIR}/*.cpp")
file(GLOB rsocketImple_SRC
        "${RSOCKET_IMPL_DIR}/*.cpp")


#set(DOWNLOAD_DIR /home/b0n3/Downloads)
add_executable(${PROJECT_NAME}
        main.cpp
        src/rsocket_implementation/src/Client.cpp
        src/rsocket_implementation/src/VeeRsocketServer.cpp
        src/rsocket_implementation/include/veeRsocketService.h
        src/rsocket_implementation/src/VeeRsocketContext.cpp
        src/rsocket_implementation/include/VeeRsocketContext.h
        src/rsocket_implementation/include/RsocketConnectionEventHandler.h
        src/rsocket_implementation/src/RsocketResponder.cpp
        src/rsocket_implementation/include/RsocketResponder.h

        src/utils/UUID.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./src/api)
target_include_directories(${PROJECT_NAME} PUBLIC ./src/utils)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/folly)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/yarpl)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/rsocket)
find_package(boost_context)
find_package(yarpl )
find_package(rsocket )
find_package(folly)
find_package(boost_regex)
#add_subdirectory(src/rsocket_implementation)
#add_subdirectory(src/utils)
target_link_libraries(${PROJECT_NAME} PUBLIC rsocket yarpl  glog boost_context folly   boost_regex pthread gflags
        ${GFLAGS_LIBRARY})

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
