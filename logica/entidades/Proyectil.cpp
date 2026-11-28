#include "Proyectil.h"
#include "logica/Constantes.h"
#include <QtMath>

Proyectil::Proyectil(qreal x0, qreal y0, qreal v0, qreal theta, qreal g,
                     short danio, qreal fuerzaImpacto, short tipoProyectil)
    : Entidad(x0, y0, 14.0, 14.0, Constantes::SPR_PROYECTIL),
      modeloTrayectoria(x0, y0, v0, theta, g),
      danio(danio), fuerzaImpacto(fuerzaImpacto),
      tiempoVuelo(0.0), acertoKirby(false),
      tipoProyectil(tipoProyectil) {
    if (tipoProyectil == Constantes::PROY_RAPIDO_LIGERO) {
        ancho = 12.0;
        alto = 12.0;
    } else if (tipoProyectil == Constantes::PROY_PESADO_ROCA) {
        ancho = 22.0;
        alto = 22.0;
    }
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
    velY = -modeloTrayectoria.getV0() * qSin(modeloTrayectoria.getTheta())
           + modeloTrayectoria.getGravedad() * tiempoVuelo;

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

short Proyectil::getTipoProyectil() const {
    return tipoProyectil;
}

bool Proyectil::esRapidoLigero() const {
    return tipoProyectil == Constantes::PROY_RAPIDO_LIGERO;
}

bool Proyectil::esPesadoRoca() const {
    return tipoProyectil == Constantes::PROY_PESADO_ROCA;
}
