#include "OficialPatriota.h"
#include "Kirby.h"
#include "Proyectil.h"
#include "logica/Constantes.h"
#include "logica/agente/MemoriaNivel.h"

OficialPatriota::OficialPatriota(qreal x, qreal y, qreal tiempoRecarga, short umbralFallos)
    : Enemigo(x, y, 44.0, 52.0, Constantes::SPR_OFICIAL_PATRIOTA, 65.0),
      agente(umbralFallos),
      tiempoRecarga(tiempoRecarga > 0.0 ? tiempoRecarga : 2.5),
      tiempoAcumulado(0.0),
      posicionObjetivoX(760.0) {
}

void OficialPatriota::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    if (aturdido) {
        retirarse(dt);
        return;
    }

    if (posX > posicionObjetivoX) {
        posX -= velocidadMovimiento * dt;
        if (posX < posicionObjetivoX) {
            posX = posicionObjetivoX;
        }
    }
}

Proyectil* OficialPatriota::actualizarIA(qreal dt, Kirby* kirby, MemoriaNivel* memoria) {
    if (!activa || aturdido || kirby == nullptr || dt < 0.0) {
        return nullptr;
    }

    agente.evaluarUltimoDisparo(memoria);

    tiempoAcumulado += dt;
    if (tiempoAcumulado >= tiempoRecarga) {
        tiempoAcumulado = 0.0;
        return agente.ejecutarCiclo(kirby, this, memoria);
    }

    return nullptr;
}

void OficialPatriota::evaluarDisparoPendiente(MemoriaNivel* memoria) {
    agente.evaluarUltimoDisparo(memoria);
}

void OficialPatriota::setPosicionObjetivo(qreal x) {
    posicionObjetivoX = x;
}

void OficialPatriota::setTiempoRecarga(qreal recarga) {
    if (recarga > 0.0) {
        tiempoRecarga = recarga;
    }
}

void OficialPatriota::setUmbralFallos(short umbral) {
    agente.setUmbralFallos(umbral);
}

bool OficialPatriota::estaEnModoPreventivo() const {
    return agente.estaEnModoPreventivo();
}
