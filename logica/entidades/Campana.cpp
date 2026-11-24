#include "Campana.h"
#include "Proyectil.h"
#include "logica/Constantes.h"

Campana::Campana(qreal xCentro, qreal y, qreal amplitud, qreal periodo)
    : Entidad(xCentro, y, 54.0, 64.0, Constantes::SPR_CAMPANA),
      modeloOscilacion(xCentro, y, amplitud, periodo, 0.0),
      tiempoAcumulado(0.0) {
}

void Campana::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    tiempoAcumulado += dt;
    QPointF pos = modeloOscilacion.calcularPosicion(tiempoAcumulado);
    posX = pos.x();
    posY = pos.y();
}

bool Campana::detiene(const Proyectil* p) const {
    if (p == nullptr || !activa || !p->estaActiva()) {
        return false;
    }
    return colisionaCon(p);
}

void Campana::setPeriodo(qreal periodo) {
    modeloOscilacion.setPeriodo(periodo);
}
