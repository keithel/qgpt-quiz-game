cmake_minimum_required(VERSION 3.16)

project(qgpt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ThirdParty)

find_package(Qt6 REQUIRED COMPONENTS Quick Concurrent)

set(QML_SOURCES
    main.qml
)

qt_add_executable(qgpt)

add_subdirectory(src)
add_subdirectory(qml)

target_link_libraries(qgpt PRIVATE Qt6::Quick Qt6::Concurrent oai)

target_include_directories(qgpt PRIVATE ${CMAKE_SOURCE_DIR}/ThirdParty/liboai/liboai/include/)

set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.kyzivat.qgpt)
set_target_properties(qgpt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS qgpt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(qgpt)
