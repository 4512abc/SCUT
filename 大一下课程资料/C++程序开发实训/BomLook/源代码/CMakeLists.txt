cmake_minimum_required(VERSION 3.16)
project(text VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=.*;-system-headers")


set(CMAKE_PREFIX_PATH "D:/Qt/6.8.0/mingw_64")

#set(CMAKE_PREFIX_PATH "D:/QT/6.8.0/msvc2022_64")
if(MSVC)
    add_compile_options(/Zc:__cplusplus)
else()
    add_compile_options(-fstack-protector-strong)
    add_link_options(-fstack-protector-strong)
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)



set(TS_FILES text_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        MyMainWindow.cpp
        MyMainWindow.h
        MyMainWindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(text
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        LevelTwo.h LevelTwo.cpp
        Cell.h Cell.cpp

        Game.h Game.cpp

        ACDialog.h ACDialog.cpp
        WADialog.h WADialog.cpp
        TimeWatch.h TimeWatch.cpp



        GameIntroduction.h GameIntroduction.cpp
        MapChoose.h MapChoose.cpp


        MAP.qrc



        Player.h Player.cpp
        Login.h Login.cpp Login.ui
        Register.h Register.cpp Register.ui
        Home.h Home.cpp Home.ui
        Ranking.h Ranking.cpp Ranking.ui
        Funny.h Funny.cpp
        musicPlayer.h musicPlayer.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET text APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(text SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(text
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(text PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(text PRIVATE Qt6::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.text)
endif()
set_target_properties(text PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS text
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(text)
endif()
