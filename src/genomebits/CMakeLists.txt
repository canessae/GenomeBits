cmake_minimum_required(VERSION 3.5)

project(genomebits LANGUAGES CXX)

set(MAJOR_VERSION "1")
set(MINOR_VERSION "0")
set(PATCH_VERSION "1")

set(CURRVERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/config.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Help REQUIRED)

if(ANDROID)
  add_library(genomebits SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    license.h
    license.cpp
    about.h
    about.cpp
    config.h
    launchscripts.cpp
    launchscripts.h
    countrytreewidget.cpp
    countrytreewidget.h
    common.h
    aspectratiopixmaplabel.cpp
    aspectratiopixmaplabel.h
    showtext.cpp
    showtext.h
    plottreewidget.cpp
    plottreewidget.h
    comparisontreewidget.cpp
    comparisontreewidget.h
    processingstatus.cpp
    processingstatus.h
    genomehelp.cpp
    genomehelp.h
    genomemanual.cpp
    genomemanual.h
    genomemanual.ui
    showtext.ui
    license.ui
    about.ui
    icons.qrc
  )
else()
  add_executable(genomebits
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    license.h
    license.cpp
    about.h
    about.cpp
    config.h
    launchscripts.cpp
    launchscripts.h
    countrytreewidget.h
    countrytreewidget.cpp
    common.h
    aspectratiopixmaplabel.cpp
    aspectratiopixmaplabel.h
    showtext.cpp
    showtext.h
    plottreewidget.cpp
    plottreewidget.h
    comparisontreewidget.cpp
    comparisontreewidget.h
    processingstatus.cpp
    processingstatus.h
    genomehelp.cpp
    genomehelp.h
    genomemanual.cpp
    genomemanual.h
    genomemanual.ui
    showtext.ui
    license.ui
    about.ui
    icons.qrc
  )
endif()

target_link_libraries(genomebits PRIVATE Qt5::Widgets Qt5::Help)
install(TARGETS genomebits DESTINATION bin)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/../../scripts DESTINATION .
    USE_SOURCE_PERMISSIONS
    PATTERN ".keep" EXCLUDE)
install(FILES ${CMAKE_SOURCE_DIR}/doc/linux/manual.qch ${CMAKE_SOURCE_DIR}/doc/linux/genomebits.qhc DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/../../doc/ DESTINATION doc)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/icons/ DESTINATION icons)
install(FILES ${CMAKE_SOURCE_DIR}/icons/48x48/apps/genomebits.png DESTINATION "/usr/share/icons/hicolor/48x48/apps/")
install(FILES ${CMAKE_SOURCE_DIR}/icons/64x64/apps/genomebits.png DESTINATION "/usr/share/icons/hicolor/64x64/apps/")
install(FILES ${CMAKE_SOURCE_DIR}/icons/128x128/apps/genomebits.png DESTINATION "/usr/share/icons/hicolor/128x128/apps/")
install(FILES ${CMAKE_SOURCE_DIR}/desktop/genomebits.desktop DESTINATION "/usr/share/applications")

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_DESCRIPTION "Software to uncovering characteristics signals from genome (fasta) sequences")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GenomeBits is an analyzing tool for uncovering signals from genome (fasta) sequences.")
set(CPACK_PACKAGE_VENDOR "ICTP")
set(CPACK_PACKAGE_CONTACT "sdu@ictp.it")
set(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
set(CPACK_STRIP_FILES TRUE)
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/genomebits")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Livius Tenze")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "perl, python-tk, python-numpy, python2, gnuplot")

include(CPack)
