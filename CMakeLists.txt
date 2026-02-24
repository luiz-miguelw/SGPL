cmake_minimum_required(VERSION 3.16)

project(SGPL VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- CORREÇÃO PRINCIPAL ---
# Adicionado "Sql" aqui. Sem isso, o CMake não encontra o módulo de banco de dados.
find_package(Qt6 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appSGPL
    main.cpp
)

qt_add_qml_module(appSGPL
    URI SGPL
    VERSION 1.0

    QML_FILES
        Main.qml
        MenuPrincipal.qml
        VitrineProdutos.qml
        RealizarPedido.qml
        ListarPedidos.qml

    SOURCES
        produto.h
        produto.cpp
        catalogocontroller.h
        catalogocontroller.cpp
        pedidoservice.h
        pedidoservice.cpp
        pedido.h
        pedido.cpp
        itempedido.h
        itempedido.cpp
        PedidoController.h
        PedidoController.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSGPL PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSGPL
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Agora o target Qt6::Sql será encontrado porque adicionamos no find_package lá em cima
target_link_libraries(appSGPL
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appSGPL
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
