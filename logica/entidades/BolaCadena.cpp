#include "BolaCadena.h"
#include "Kirby.h"
#include "logica/Constantes.h"

BolaCadena::BolaCadena(qreal xc, qreal yc,
                       qreal radioMin, qreal radioMax,
                       qreal omega, qreal tasaExpansion)
    : Entidad(xc, yc, 36.0, 36.0, Constantes::SPR_BOLA_CADENA),
      modeloEspiral(xc, yc, radioMin, radioMax, omega, tasaExpansion),
      tiempoAcumulado(0.0) {
    QPointF posInicial = modeloEspiral.calcularPosicion(0.0);
    posX = posInicial.x() - ancho / 2.0;
    posY = posInicial.y() - alto / 2.0;
}

void BolaCadena::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    tiempoAcumulado += dt;
    QPointF centroBola = modeloEspiral.calcularPosicion(tiempoAcumulado);
    posX = centroBola.x() - ancho / 2.0;
    posY = centroBola.y() - alto / 2.0;
}

bool BolaCadena::golpea(const Kirby* k) const {
    if (k == nullptr || !activa || !k->estaActiva()) {
        return false;
    }

    QRectF cajaKirby = k->cajaColision();
    if (cajaColision().intersects(cajaKirby)) {
        return true;
    }

    // Verificación segmental a lo largo de la cadena radial (de centro a bola)
    qreal cx = modeloEspiral.getXc();
    qreal cy = modeloEspiral.getYc();
    qreal bx = posX + ancho / 2.0;
    qreal by = posY + alto / 2.0;

    const int segmentos = 8;
    for (int i = 1; i < segmentos; ++i) {
        qreal t = static_cast<qreal>(i) / segmentos;
        qreal px = cx + t * (bx - cx);
        qreal py = cy + t * (by - cy);
        if (cajaKirby.contains(px, py)) {
            return true;
        }
    }

    return false;
}

void BolaCadena::setCentro(qreal xc, qreal yc) {
    modeloEspiral.setCentro(xc, yc);
}

void BolaCadena::setVelocidadAngular(qreal omega) {
    modeloEspiral.setOmega(omega);
}

qreal BolaCadena::getCentroX() const {
    return modeloEspiral.getXc();
}

qreal BolaCadena::getCentroY() const {
    return modeloEspiral.getYc();
}
