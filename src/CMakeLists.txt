message(STATUS "FLTK inc = ${FLTK_INCLUDE_DIR}")
fltk_wrap_ui(WSSUi WhySoSerial.fl)
add_library(WSSUi STATIC ${WSSUi_FLTK_UI_SRCS})
add_library(Serial STATIC serial.cpp serial.h)


add_executable(wsserial wsserial.cpp)
add_dependencies(wsserial WSSUi)
add_dependencies(wsserial Serial)
target_link_libraries(wsserial PUBLIC WSSUi)
target_link_libraries(wsserial PUBLIC Serial)
target_link_libraries(wsserial PUBLIC ${LIBS})

