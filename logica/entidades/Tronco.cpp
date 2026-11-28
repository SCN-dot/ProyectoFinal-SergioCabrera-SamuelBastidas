#include "Tronco.h"
#include "logica/Constantes.h"
#include <QtMath>

Tronco::Tronco(qreal xInicial, qreal velocidadHorizontal, short danio, qreal fuerzaImpacto)
    : Proyectil(xInicial, Constantes::PISO_NIVEL1 - 84.0,
                velocidadHorizontal > 0.0 ? velocidadHorizontal : 205.0,
                M_PI, 0.0, danio, fuerzaImpacto, Constantes::PROY_ESTANDAR),
      velocidadHorizontal(velocidadHorizontal > 0.0 ? velocidadHorizontal : 205.0),
      anguloRotacion(0.0),
      danioPuerta(8) {

    ancho = 52.0;
    alto = 84.0;
    posX = xInicial;
    posY = Constantes::PISO_NIVEL1 - alto;
    velX = -this->velocidadHorizontal;
    velY = 0.0;
    spriteId = Constantes::SPR_NINGUNO;
}

void Tronco::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    posX += velX * dt;
    posY = Constantes::PISO_NIVEL1 - alto;
    anguloRotacion -= 220.0 * dt;
    if (anguloRotacion < -360.0) {
        anguloRotacion += 360.0;
    }

    if (posX + ancho < -60.0) {
        activa = false;
    }
}

qreal Tronco::getAnguloRotacion() const {
    return anguloRotacion;
}

short Tronco::getDanioPuerta() const {
    return danioPuerta;
}
