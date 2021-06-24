set(SOURCES
        UserException.cpp
        LogHelper.cpp)

set(HEADERS
        CharFastStackBuffer.h
        FastStackStreamBuffer.h
        LogHelper.h
        UserException.h
        FastStackBuffer.h)

set(BIN_PATH ${PROJECT_SOURCE_DIR}/bin)

set(HEADERS_PATH ${CMAKE_INSTALL_PREFIX}/include/StdCoreLib)
set(DESTINATION_PATH ${CMAKE_INSTALL_PREFIX}/lib)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${DESTINATION_PATH})
install(FILES ${HEADERS}
        DESTINATION ${HEADERS_PATH})
