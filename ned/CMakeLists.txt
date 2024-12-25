cmake_minimum_required(VERSION 3.31)

project(ned VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
   ned.h
   ned.cpp
   SubCmd.cpp
   CmdCsr.cpp
   CmdIns.cpp
   CmdFind.cpp
   CmdFile.cpp
   CmdBlk.cpp
   CmdEtc.cpp
   CmdMap.cpp
   stv/os.cpp
   stv/ui.cpp
   stv/uiKey.cpp
)

 qt_add_executable(ned rc/rc.qrc
     MANUAL_FINALIZATION
     ${PROJECT_SOURCES}
 )

target_link_libraries(ned PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ned PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ned
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(ned)

install(TARGETS ned
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
