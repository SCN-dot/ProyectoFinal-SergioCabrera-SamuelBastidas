#include "Razonamiento.h"
#include "MemoriaNivel.h"
#include "Percepcion.h"
#include "logica/Constantes.h"
#include <QtMath>

Razonamiento::Razonamiento()
    : tipoDisparoSeleccionado(TIRO_BAJO),
      tipoProyectilSeleccionado(PROY_RAPIDO_LIGERO),
      anguloBajoGrados(30.0),
      anguloAltoGrados(55.0),
      anguloPreventivoGrados(65.0),
      modoPreventivo(false) {
}

qreal Razonamiento::calcularVelocidadBalistica(qreal d, qreal deltaY, qreal thetaRad, qreal g) const {
    if (d < 10.0) {
        d = 10.0;
    }

    qreal cosTheta = qCos(thetaRad);
    qreal tanTheta = qTan(thetaRad);
    qreal terminoAltura = d * tanTheta - deltaY;
    qreal denominador = 2.0 * cosTheta * cosTheta * terminoAltura;

    if (denominador <= 0.0) {
        // Ángulo de respaldo más vertical si el objetivo está muy elevado
        qreal thetaRespaldo = qDegreesToRadians(78.0);
        qreal cosR = qCos(thetaRespaldo);
        qreal denR = 2.0 * cosR * cosR * (d * qTan(thetaRespaldo) - deltaY);
        if (denR <= 0.0) {
            return 600.0;
        }
        return qSqrt((g * d * d) / denR);
    }

    return qSqrt((g * d * d) / denominador);
}

void Razonamiento::decidir(const Percepcion& percepcion, const MemoriaNivel* memoria,
                           qreal& outV0, qreal& outThetaRad, short& outTipoProyectil) {
    short estado = percepcion.getEstadoKirby();
    bool tendenciaEvasion = (memoria != nullptr) && memoria->hayTendenciaEvasion();

    // Selección del proyectil especializado del Oficial Patriota según el estado de Kirby
    if (estado == ESTADO_ROCA) {
        tipoProyectilSeleccionado = PROY_PESADO_ROCA;
        tipoDisparoSeleccionado = TIRO_ELEVADO;
    } else {
        tipoProyectilSeleccionado = PROY_RAPIDO_LIGERO;
        if (modoPreventivo || tendenciaEvasion) {
            tipoDisparoSeleccionado = TIRO_PREVENTIVO;
        } else if (estado == ESTADO_SALTANDO || estado == ESTADO_GLOBO) {
            tipoDisparoSeleccionado = TIRO_ELEVADO;
        } else {
            tipoDisparoSeleccionado = TIRO_BAJO;
        }
    }
    outTipoProyectil = tipoProyectilSeleccionado;

    qreal d = percepcion.getDistanciaKirby();
    if (d < 20.0) {
        d = 20.0;
    }
    qreal deltaY = percepcion.getDeltaY();

    if (tipoProyectilSeleccionado == PROY_PESADO_ROCA) {
        // Parábola lenta y elevada que da margen visual al jugador para reaccionar
        qreal anguloDirectoGrados = qRadiansToDegrees(qAtan2(deltaY, d));
        qreal anguloGrados = qMax(anguloAltoGrados + 9.0, anguloDirectoGrados + 10.0);
        if (anguloGrados < 58.0) anguloGrados = 58.0;
        if (anguloGrados > 80.0) anguloGrados = 80.0;

        qreal thetaBaseRad = qDegreesToRadians(anguloGrados);
        qreal gEfectiva = Constantes::GRAVEDAD_BASE * Constantes::FACTOR_GRAVEDAD_PESADO;
        outV0 = calcularVelocidadBalistica(d, deltaY, thetaBaseRad, gEfectiva);
        if (outV0 > 900.0) outV0 = 900.0;

        outThetaRad = percepcion.estaALaIzquierda() ? (M_PI - thetaBaseRad) : thetaBaseRad;
        return;
    }

    // PROY_RAPIDO_LIGERO: trayectoria más tensa y veloz apuntando a la altura actual o de vuelo
    if (tipoDisparoSeleccionado == TIRO_PREVENTIVO) {
        deltaY += 55.0;
    }

    qreal anguloDirectoGrados = qRadiansToDegrees(qAtan2(deltaY, d));
    qreal margenAngulo = (tipoDisparoSeleccionado == TIRO_PREVENTIVO) ? 16.0 : 14.0;
    qreal anguloMinimo = (tipoDisparoSeleccionado == TIRO_PREVENTIVO) ? 22.0 : 18.0;
    qreal anguloGrados = qMax(anguloMinimo, anguloDirectoGrados + margenAngulo);
    if (anguloGrados > 80.0) {
        anguloGrados = 80.0;
    }

    qreal thetaBaseRad = qDegreesToRadians(anguloGrados);
    outV0 = calcularVelocidadBalistica(d, deltaY, thetaBaseRad, Constantes::GRAVEDAD_BASE);
    if (outV0 > 1200.0) {
        outV0 = 1200.0;
    }

    // Si Kirby está a la izquierda del oficial, reflejar el ángulo horizontalmente
    outThetaRad = percepcion.estaALaIzquierda() ? (M_PI - thetaBaseRad) : thetaBaseRad;
}

void Razonamiento::activarModoPreventivo(bool activar) {
    modoPreventivo = activar;
}

void Razonamiento::reajustarAngulos(qreal nuevoBajo, qreal nuevoAlto, qreal nuevoPreventivo) {
    anguloBajoGrados = nuevoBajo;
    anguloAltoGrados = nuevoAlto;
    anguloPreventivoGrados = nuevoPreventivo;
}

short Razonamiento::getTipoDisparoSeleccionado() const {
    return tipoDisparoSeleccionado;
}

short Razonamiento::getTipoProyectilSeleccionado() const {
    return tipoProyectilSeleccionado;
}

bool Razonamiento::estaEnModoPreventivo() const {
    return modoPreventivo;
}
