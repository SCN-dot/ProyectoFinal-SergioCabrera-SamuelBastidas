#include "Proyectil.h"
#include "logica/Constantes.h"
#include <QtMath>

Proyectil::Proyectil(qreal x0, qreal y0, qreal v0, qreal theta, qreal g,
                     short danio, qreal fuerzaImpacto)
    : Entidad(x0, y0, 14.0, 14.0, Constantes::SPR_PROYECTIL),
      modeloTrayectoria(x0, y0, v0, theta, g),
      danio(danio), fuerzaImpacto(fuerzaImpacto),
      tiempoVuelo(0.0), acertoKirby(false) {
    velX = v0 * qCos(theta);
    velY = -v0 * qSin(theta);
}

void Proyectil::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    tiempoVuelo += dt;
    QPointF nuevaPos = modeloTrayectoria.calcularPosicion(tiempoVuelo);
    posX = nuevaPos.x();
    posY = nuevaPos.y();

    // Desactivar si sale de los límites razonables del escenario
    if (posX < -100.0 || posX > Constantes::ANCHO_ESCENARIO + 100.0 ||
        posY > Constantes::ALTO_ESCENARIO + 100.0 || posY < -400.0) {
        activa = false;
    }
}

void Proyectil::marcarAciertoKirby() {
    acertoKirby = true;
    activa = false;
}

bool Proyectil::getAcertoKirby() const {
    return acertoKirby;
}

short Proyectil::getDanio() const {
    return danio;
}

qreal Proyectil::getFuerzaImpacto() const {
    return fuerzaImpacto;
}

qreal Proyectil::getDireccionHorizontal() const {
    return (velX >= 0.0) ? 1.0 : -1.0;
}
