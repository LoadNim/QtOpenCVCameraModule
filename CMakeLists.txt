cmake_minimum_required(VERSION 3.16)

project(QtOpenCVCameraModule VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(PROJECT_SOURCES
    ${INCLUDE_DIR}/mainwindow.h
    ${INCLUDE_DIR}/cammanager.h

    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/mainwindow.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtOpenCVCameraModule
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/cammanager.cpp
        include/frameprocessor.h
        src/frameprocessor.cpp
        include/frameflowhandler.h
        src/frameflowhandler.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtOpenCVCameraModule APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtOpenCVCameraModule SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtOpenCVCameraModule
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(QtOpenCVCameraModule PRIVATE ${INCLUDE_DIR})

target_link_libraries(QtOpenCVCameraModule PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

find_package(OpenCV REQUIRED)
target_include_directories(QtOpenCVCameraModule PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(QtOpenCVCameraModule PRIVATE ${OpenCV_LIBS})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtOpenCVCameraModule)
endif()
set_target_properties(QtOpenCVCameraModule PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtOpenCVCameraModule
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtOpenCVCameraModule)
endif()
