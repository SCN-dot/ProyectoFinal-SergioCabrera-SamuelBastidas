#include "MovArmonico.h"
#include <QtMath>
#include <stdexcept>

MovArmonico::MovArmonico(qreal x0, qreal y0, qreal amplitud, qreal periodo, qreal fase)
    : ModeloFisico(x0, y0), amplitud(amplitud), omega(0.0), fase(fase) {
    setPeriodo(periodo);
}

QPointF MovArmonico::calcularPosicion(qreal t) const {
    qreal x = x0 + amplitud * qCos(omega * t + fase);
    return QPointF(x, y0);
}

void MovArmonico::setPeriodo(qreal periodo) {
    if (periodo <= 0.0) {
        throw std::invalid_argument("El período (T) del movimiento armónico debe ser mayor que cero.");
    }
    omega = (2.0 * M_PI) / periodo;
}

void MovArmonico::setAmplitud(qreal amplitud) {
    this->amplitud = amplitud;
}

void MovArmonico::setFase(qreal fase) {
    this->fase = fase;
}

qreal MovArmonico::getAmplitud() const {
    return amplitud;
}

qreal MovArmonico::getOmega() const {
    return omega;
}

qreal MovArmonico::getFase() const {
    return fase;
}
