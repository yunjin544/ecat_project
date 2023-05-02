cmake_minimum_required(VERSION 3.0.0)
project(soem_bridge_board_tets VERSION 0.1.0)

execute_process(COMMAND uname -r OUTPUT_VARIABLE UNAME_RES OUTPUT_STRIP_TRAILING_WHITESPACE)
message("-- kernel version : " ${UNAME_RES})
execute_process(COMMAND xeno-config --posix --cflags OUTPUT_VARIABLE XENO_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND xeno-config --posix --ldflags OUTPUT_VARIABLE XENO_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#message(" xeno flags : " ${XENO_CFLAGS})
string(FIND ${UNAME_RES} "xenomai" wsloc)

add_executable(soem_bridge_board_test src/ecat_server.cpp src/KITECH_CoE_TEST.cpp src/IPC.cpp)
add_executable(test_node src/ros_ipc.cpp src/IPC.cpp)


include_directories(
    /usr/include/soem
    /usr/xenomai/include/
    /usr/xenomai/include/alchemy
    /usr/xenomai/include/cobalt
    includes/struct
    includes/
)

target_link_libraries(soem_bridge_board_test 
  -lsoem
  -lpthread
  -lalchemy 
  -lcopperplate
    ${XENO_CFLAGS}
    ${XENO_LDFLAGS}
)

target_link_libraries(test_node 
  -lsoem
  -lpthread
  -lalchemy 
  -lcopperplate
    ${XENO_CFLAGS}
    ${XENO_LDFLAGS}
)
  

