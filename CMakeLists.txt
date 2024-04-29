cmake_minimum_required(VERSION 3.5)

project(scc_algorithms_visualizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        visualizationwindow.ui
        visualizationwindow.h visualizationwindow.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(scc_algorithms_visualizer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        graphwidget.h graphwidget.cpp
        node.h node.cpp
        edge.h edge.cpp
        visualizationwindow.h visualizationwindow.cpp visualizationwindow.ui
        animationwidget.h animationwidget.cpp
        resources.qrc
        animationspeeddialog.h animationspeeddialog.cpp animationspeeddialog.ui
        algorithmpickerdialog.h algorithmpickerdialog.cpp algorithmpickerdialog.ui
        stack.h stack.cpp
        utils.cpp
        utils.h
        table.h table.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET scc_algorithms_visualizer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(scc_algorithms_visualizer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(scc_algorithms_visualizer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(scc_algorithms_visualizer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.scc_algorithms_visualizer)
endif()
set_target_properties(scc_algorithms_visualizer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS scc_algorithms_visualizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(scc_algorithms_visualizer)
endif()
