#include "Campana.h"
#include "Proyectil.h"
#include "logica/Constantes.h"

Campana::Campana(qreal xCentro, qreal y, qreal amplitud, qreal periodo)
    : Entidad(xCentro, y, 54.0, 64.0, Constantes::SPR_CAMPANA),
      modeloOscilacion(xCentro, y, amplitud, periodo, 0.0),
      tiempoAcumulado(0.0),
      suelta(false),
      cubriendoPuerta(false),
      velocidadCaida(0.0) {
}

void Campana::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    if (!suelta) {
        tiempoAcumulado += dt;
        QPointF pos = modeloOscilacion.calcularPosicion(tiempoAcumulado);
        posX = pos.x();
        posY = pos.y();
        return;
    }

    if (cubriendoPuerta) {
        return;
    }

    posX = 25.0;
    velocidadCaida += Constantes::GRAVEDAD_BASE * dt;
    velY = velocidadCaida;
    posY += velY * dt;

    if (posY + alto >= Constantes::PISO_NIVEL1) {
        posY = Constantes::PISO_NIVEL1 - alto;
        velocidadCaida = 0.0;
        velY = 0.0;
        cubriendoPuerta = true;
    }
}

bool Campana::detiene(const Proyectil* p) const {
    if (p == nullptr || !activa || !p->estaActiva()) {
        return false;
    }
    return colisionaCon(p);
}

void Campana::soltar() {
    if (suelta) {
        return;
    }
    suelta = true;
    cubriendoPuerta = false;
    posX = 25.0;
    velocidadCaida = 0.0;
    velX = 0.0;
    velY = 0.0;
}

void Campana::setPeriodo(qreal periodo) {
    modeloOscilacion.setPeriodo(periodo);
}

bool Campana::estaSuelta() const {
    return suelta;
}

bool Campana::estaCubriendoPuerta() const {
    return cubriendoPuerta;
}

qreal Campana::getVelocidadCaida() const {
    return velocidadCaida;
}
