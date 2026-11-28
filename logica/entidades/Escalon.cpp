#include "Escalon.h"
#include "logica/Constantes.h"

Escalon::Escalon(qreal x, qreal y, qreal ancho, qreal alto, short indice, short cantidadTravesanos)
    : Entidad(x, y, ancho, alto, Constantes::SPR_NINGUNO),
      indice(indice),
      cantidadTravesanos(cantidadTravesanos > 0 ? cantidadTravesanos : 3) {
}

void Escalon::actualizar(qreal dt) {
    Q_UNUSED(dt);
}

short Escalon::getIndice() const {
    return indice;
}

short Escalon::getCantidadTravesanos() const {
    return cantidadTravesanos;
}

qreal Escalon::getSuperficieY() const {
    return posY;
}
