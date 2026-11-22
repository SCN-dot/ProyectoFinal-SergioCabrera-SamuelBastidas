#include "Adoquin.h"
#include "logica/Constantes.h"

Adoquin::Adoquin(qreal x, qreal y)
    : Entidad(x, y, 28.0, 28.0, Constantes::SPR_ADOQUIN) {
}

void Adoquin::actualizar(qreal dt) {
    Q_UNUSED(dt);
}

void Adoquin::recoger() {
    activa = false;
}
