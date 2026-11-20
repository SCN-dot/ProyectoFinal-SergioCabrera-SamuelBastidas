QT += core gui widgets
qtHaveModule(multimedia) {
    QT += multimedia
    DEFINES += TIENE_MULTIMEDIA
} else {
    message("Advertencia: modulo Qt6 Multimedia no instalado; se omite temporalmente.")
}

CONFIG += c++17

TARGET = KirbyNavidadNegra
TEMPLATE = app

INCLUDEPATH += .

HEADERS += \
    logica/Constantes.h \
    logica/fisica/ModeloFisico.h \
    logica/fisica/MovParabolico.h \
    logica/fisica/MovArmonico.h \
    logica/fisica/MovCircular.h \
    logica/fisica/MovDinamico.h \
    logica/fisica/Viento.h \
    logica/entidades/Entidad.h \
    logica/entidades/Barricada.h \
    logica/entidades/Adoquin.h \
    logica/entidades/Alimento.h \
    logica/entidades/Proyectil.h \
    logica/entidades/Mortero.h \
    logica/entidades/Campana.h \
    logica/entidades/BolaCadena.h \
    logica/entidades/Kirby.h \
    logica/entidades/Enemigo.h \
    logica/entidades/Soldado.h \
    logica/entidades/CapitanRifles.h \
    logica/entidades/OficialPatriota.h \
    logica/agente/MemoriaNivel.h \
    logica/agente/Percepcion.h \
    logica/agente/Razonamiento.h \
    logica/agente/Accion.h \
    logica/agente/Aprendizaje.h \
    logica/agente/AgenteAutonomo.h \
    logica/juego/Dificultad.h \
    logica/juego/Temporizador.h \
    logica/juego/Nivel.h \
    logica/juego/Nivel1.h \
    logica/juego/Nivel2.h \
    logica/juego/Juego.h \
    gui/Audio.h \
    gui/Lienzo.h \
    gui/VentanaPrincipal.h

SOURCES += \
    main.cpp \
    logica/fisica/ModeloFisico.cpp \
    logica/fisica/MovParabolico.cpp \
    logica/fisica/MovArmonico.cpp \
    logica/fisica/MovCircular.cpp \
    logica/fisica/MovDinamico.cpp \
    logica/fisica/Viento.cpp \
    logica/entidades/Entidad.cpp \
    logica/entidades/Barricada.cpp \
    logica/entidades/Adoquin.cpp \
    logica/entidades/Alimento.cpp \
    logica/entidades/Proyectil.cpp \
    logica/entidades/Mortero.cpp \
    logica/entidades/Campana.cpp \
    logica/entidades/BolaCadena.cpp \
    logica/entidades/Kirby.cpp \
    logica/entidades/Enemigo.cpp \
    logica/entidades/Soldado.cpp \
    logica/entidades/CapitanRifles.cpp \
    logica/entidades/OficialPatriota.cpp \
    logica/agente/MemoriaNivel.cpp \
    logica/agente/Percepcion.cpp \
    logica/agente/Razonamiento.cpp \
    logica/agente/Accion.cpp \
    logica/agente/Aprendizaje.cpp \
    logica/agente/AgenteAutonomo.cpp \
    logica/juego/Dificultad.cpp \
    logica/juego/Temporizador.cpp \
    logica/juego/Nivel.cpp \
    logica/juego/Nivel1.cpp \
    logica/juego/Nivel2.cpp \
    logica/juego/Juego.cpp \
    gui/Audio.cpp \
    gui/Lienzo.cpp \
    gui/VentanaPrincipal.cpp

RESOURCES += \
    recursos.qrc
