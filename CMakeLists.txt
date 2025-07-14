cmake_minimum_required(VERSION 3.16)

project(MobileOperators VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    Qml
    Gui
    QuickControls2

    Sql
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appMobileOperators
    Main.cpp
)

qt_add_qml_module(appMobileOperators
    URI MobileOperators
    VERSION 1.0

    SOURCES SQL/SqlManager.hpp SQL/SqlManager.cpp
    SOURCES ViewModel/CombinedModel.hpp ViewModel/CombinedModel.cpp

    SOURCES Data/Structures/IndexedMap.hpp

    SOURCES Data/Storage/DataStorage.hpp Data/Storage/DataStorage.cpp

    SOURCES Data/Entities/Country.hpp
    SOURCES Data/Entities/Operator.hpp


    QML_FILES Main.qml

    QML_FILES UI/Dialogs/OperatorEditDialog.qml

    QML_FILES UI/TreeElements/CountryComponent.qml
    QML_FILES UI/TreeElements/OperatorComponent.qml

    QML_FILES UI/Common/ReliableImage.qml
    QML_FILES UI/Dialogs/OperatorAddDialog.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMobileOperators PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMobileOperators
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMobileOperators
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::Qml
    PRIVATE Qt${QT_VERSION_MAJOR}::Gui
    PRIVATE Qt${QT_VERSION_MAJOR}::QuickControls2
    PRIVATE Qt${QT_VERSION_MAJOR}::Sql
)

include(GNUInstallDirs)
install(TARGETS appMobileOperators
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_custom_command(TARGET appMobileOperators POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources
    $<TARGET_FILE_DIR:appMobileOperators>/Resources
)
