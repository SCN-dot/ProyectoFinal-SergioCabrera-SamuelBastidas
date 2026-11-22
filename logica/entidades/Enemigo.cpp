#include "Enemigo.h"
#include "logica/Constantes.h"

Enemigo::Enemigo(qreal x, qreal y, qreal ancho, qreal alto,
                 short spriteId, qreal velocidad)
    : Entidad(x, y, ancho, alto, spriteId),
      aturdido(false),
      velocidadMovimiento(velocidad),
      direccionRetiro(1.0) {
}

void Enemigo::aturdir() {
    aturdido = true;
}

void Enemigo::retirarse(qreal dt) {
    if (!activa || !aturdido || dt < 0.0) {
        return;
    }

    posX += direccionRetiro * (velocidadMovimiento * 2.2) * dt;
    if (posX > Constantes::ANCHO_ESCENARIO + 60.0 || posX + ancho < -60.0) {
        activa = false;
    }
}

bool Enemigo::estaAturdido() const {
    return aturdido;
}
