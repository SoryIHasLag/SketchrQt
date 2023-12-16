cmake_minimum_required(VERSION 3.5)

project(SketchrQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Java source file
set(JAVA_SOURCE src/Main.java)

# Add a custom target to compile Java source
add_custom_target(JavaCompile
    COMMAND javac -source 8 -target 8 -d ${CMAKE_CURRENT_BINARY_DIR} ${JAVA_SOURCE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Compiling Java source"
)


# Specify your C++ source files
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/imagemanipulator.cpp
    src/screenselection.cpp

    src/mainwindow.h
    src/imagemanipulator.h
    src/screenselection.h

    src/mainwindow.ui
    res/resources.qrc
)

# Set the icon resource for Windows
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/icon.rc")

# Use qt_add_executable if Qt version is 6 or later
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SketchrQt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        src/imagemanipulator.h src/imagemanipulator.cpp
        ${APP_ICON_RESOURCE_WINDOWS}
        src/screenselection.h src/screenselection.cpp
    )
else()
    add_executable(SketchrQt ${PROJECT_SOURCES})
endif()

# Link Qt libraries
target_link_libraries(SketchrQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set properties for Windows
if(WIN32)
    set_target_properties(SketchrQt PROPERTIES
        WIN32_EXECUTABLE TRUE
        VS_RESOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.ico"
    )
endif()

# Set bundle properties for macOS
if(APPLE)
    set_target_properties(SketchrQt PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SketchrQt
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
    )
endif()

# Install targets
include(GNUInstallDirs)
install(TARGETS SketchrQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SketchrQt)
endif()

# Add dependency on JavaCompile for the SketchrQt target
add_dependencies(SketchrQt JavaCompile)
