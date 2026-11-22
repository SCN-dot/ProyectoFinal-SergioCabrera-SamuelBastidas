#include "Alimento.h"
#include "logica/Constantes.h"

Alimento::Alimento(qreal x, qreal y, short curacion)
    : Entidad(x, y, 26.0, 26.0, Constantes::SPR_ALIMENTO),
      curacion(curacion) {
}

void Alimento::actualizar(qreal dt) {
    Q_UNUSED(dt);
}

short Alimento::consumir() {
    if (!activa) {
        return 0;
    }
    activa = false;
    return curacion;
}

short Alimento::getCuracion() const {
    return curacion;
}
