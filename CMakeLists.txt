cmake_minimum_required(VERSION 3.16)

project(QtOpenCVCameraModule VERSION 0.1 LANGUAGES CXX)

# Qt 설정
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 패키지 검색 - Quick과 QuickWidgets 추가
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick QuickWidgets VirtualKeyboard)

# OpenCV 패키지 검색
find_package(OpenCV REQUIRED)

# include 디렉토리 정리
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(INCLUDE_CAMERA ${INCLUDE_DIR}/camera)
set(INCLUDE_RECOGNITION ${INCLUDE_DIR}/recognition)
set(INCLUDE_UI ${INCLUDE_DIR}/ui)

# 소스 디렉토리 정리
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_CAMERA ${SRC_DIR}/camera)
set(SRC_RECOGNITION ${SRC_DIR}/recognition)
set(SRC_UI ${SRC_DIR}/ui)

# 소스 파일 목록
set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp

    # Camera
    ${INCLUDE_CAMERA}/cammanager.h
    ${SRC_CAMERA}/cammanager.cpp
    ${INCLUDE_CAMERA}/frameprocessor.h
    ${SRC_CAMERA}/frameprocessor.cpp

    # Recognition
    ${INCLUDE_RECOGNITION}/recognizer.h
    ${SRC_RECOGNITION}/recognizer.cpp
    ${INCLUDE_RECOGNITION}/frameflowhandler.h
    ${SRC_RECOGNITION}/frameflowhandler.cpp

    # UI
    ${INCLUDE_UI}/mainwindow.h
    ${SRC_UI}/mainwindow.cpp
    ${INCLUDE_UI}/maininterface.h
    ${SRC_UI}/maininterface.cpp
    ${INCLUDE_UI}/videolabel.h
    ${SRC_UI}/videolabel.cpp
    ${INCLUDE_UI}/togglemenu.h
    ${SRC_UI}/togglemenu.cpp
    ${INCLUDE_UI}/keypad.h
    ${SRC_UI}/keypad.cpp
    ${INCLUDE_UI}/regist.h
    ${SRC_UI}/regist.cpp
)

# 실행 파일 생성
qt_add_executable(QtOpenCVCameraModule
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    include/ui/qrwizard.h
    src/ui/qrwizard.cpp
)

# QML 모듈 추가
qt_add_qml_module(QtOpenCVCameraModule
    URI VirtualKeyboardApp
    VERSION 1.0
    SOURCES
)

# include 디렉토리 등록
target_include_directories(QtOpenCVCameraModule PRIVATE
    ${INCLUDE_DIR}
    ${INCLUDE_CAMERA}
    ${INCLUDE_RECOGNITION}
    ${INCLUDE_UI}
    ${OpenCV_INCLUDE_DIRS}
)

# 라이브러리 링크 - Quick과 QuickWidgets 추가
target_link_libraries(QtOpenCVCameraModule PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickWidgets
    Qt6::VirtualKeyboard
    ${OpenCV_LIBS}
)

# 정적 빌드용 QML 플러그인 import
if(QT_FEATURE_static)
    qt6_import_qml_plugins(QtOpenCVCameraModule)
endif()

# 윈도우 및 macOS용 설정 (라즈베리파이에서는 신경 안 써도 됨)
set_target_properties(QtOpenCVCameraModule PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 설치 경로
include(GNUInstallDirs)
install(TARGETS QtOpenCVCameraModule
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt6 최종 마무리
qt_finalize_executable(QtOpenCVCameraModule)
