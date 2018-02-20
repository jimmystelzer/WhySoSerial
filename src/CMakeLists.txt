message(STATUS "FLTK inc = ${FLTK_INCLUDE_DIR}")
fltk_wrap_ui(WSSUi WhySoSerial.fl)
add_library(WSSUi STATIC ${WSSUi_FLTK_UI_SRCS})

add_executable(wsserial wsserial.cxx)
add_dependencies(wsserial WSSUi)
target_link_libraries(wsserial PUBLIC WSSUi)
target_link_libraries(wsserial PUBLIC ${LIBS})

