cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_C_FLAGS             "${CMAKE_C_FLAGS} -fno-stack-protector -llog")
add_library(opoctf-jni SHARED
        opoctf.c)



target_link_libraries(opoctf-jni
                      android
                      log)
