#include "Mortero.h"
#include "logica/Constantes.h"

Mortero::Mortero(const QPointF& puntoImpacto, qreal tiempoAviso, short danio)
    : Proyectil(puntoImpacto.x(), -40.0, 0.0, 0.0, Constantes::GRAVEDAD_BASE, danio, 250.0),
      puntoImpacto(puntoImpacto),
      tiempoAviso(tiempoAviso > 0.0 ? tiempoAviso : 1.5),
      tiempoTranscurrido(0.0),
      enAviso(true),
      exploto(false) {
    spriteId = Constantes::SPR_MORTERO;
    ancho = 28.0;
    alto = 28.0;
    // Se posiciona sobre el punto de impacto durante la caída vertical/parabólica
    posX = puntoImpacto.x() - ancho / 2.0;
    posY = -40.0;
    modeloTrayectoria.setOrigen(posX, posY);
}

void Mortero::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    tiempoTranscurrido += dt;

    if (enAviso) {
        if (tiempoTranscurrido >= tiempoAviso) {
            enAviso = false;
            tiempoVuelo = 0.0;
        }
        return;
    }

    // Fase de caída parabólica hacia el puntoImpacto
    tiempoVuelo += dt;
    QPointF nuevaPos = modeloTrayectoria.calcularPosicion(tiempoVuelo);
    posX = nuevaPos.x();
    posY = nuevaPos.y();

    if (posY + alto >= puntoImpacto.y()) {
        posY = puntoImpacto.y() - alto;
        exploto = true;
        activa = false;
    }
}

bool Mortero::estaEnAviso() const {
    return enAviso;
}

bool Mortero::haExplotado() const {
    return exploto;
}

QPointF Mortero::getPuntoImpacto() const {
    return puntoImpacto;
}

qreal Mortero::getProgresoAviso() const {
    if (tiempoAviso <= 0.0) {
        return 1.0;
    }
    qreal progreso = tiempoTranscurrido / tiempoAviso;
    return (progreso > 1.0) ? 1.0 : progreso;
}
