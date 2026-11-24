#include "Barricada.h"
#include "logica/Constantes.h"

Barricada::Barricada(qreal x, qreal y, short resistencia)
    : Entidad(x, y, 42.0, 56.0, Constantes::SPR_BARRICADA),
      resistencia(resistencia) {
}

void Barricada::actualizar(qreal dt) {
    Q_UNUSED(dt);
}

void Barricada::recibirImpactoRoca() {
    if (!activa) {
        return;
    }
    resistencia--;
    if (resistencia <= 0) {
        resistencia = 0;
        activa = false;
    }
}

short Barricada::getResistencia() const {
    return resistencia;
}
