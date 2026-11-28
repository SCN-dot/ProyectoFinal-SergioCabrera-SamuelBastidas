#include "Soldado.h"
#include "Proyectil.h"
#include "logica/Constantes.h"
#include <QtMath>

Soldado::Soldado(qreal x, qreal y, qreal tiempoRecarga)
    : Enemigo(x, y, 40.0, 48.0, Constantes::SPR_SOLDADO, 55.0),
      tiempoRecarga(tiempoRecarga > 0.0 ? tiempoRecarga : 3.0),
      tiempoAcumulado(0.0),
      posicionObjetivoX(620.0) {
}

void Soldado::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    if (aturdido) {
        retirarse(dt);
        return;
    }

    if (posX > posicionObjetivoX) {
        posX -= velocidadMovimiento * dt;
        if (posX < posicionObjetivoX) {
            posX = posicionObjetivoX;
        }
    }
}

Proyectil* Soldado::intentarDisparar(qreal dt) {
    if (!activa || aturdido || dt < 0.0) {
        return nullptr;
    }

    tiempoAcumulado += dt;
    if (tiempoAcumulado >= tiempoRecarga) {
        tiempoAcumulado = 0.0;

        qreal angulo = M_PI - qDegreesToRadians(32.0);
        return new Proyectil(posX, posY + 12.0, 660.0, angulo,
                             Constantes::GRAVEDAD_BASE, 12, 180.0);
    }

    return nullptr;
}

void Soldado::setPosicionObjetivo(qreal x) {
    posicionObjetivoX = x;
}
