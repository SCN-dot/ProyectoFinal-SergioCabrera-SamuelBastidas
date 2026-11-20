#include "MovParabolico.h"
#include <QtMath>
#include <stdexcept>

MovParabolico::MovParabolico(qreal x0, qreal y0, qreal v0, qreal theta, qreal g)
    : ModeloFisico(x0, y0), v0(0.0), theta(theta), g(0.0) {
    setParametros(v0, theta, g);
}

QPointF MovParabolico::calcularPosicion(qreal t) const {
    qreal x = x0 + v0 * qCos(theta) * t;
    // Signo negativo en Y porque el eje vertical de pantalla crece hacia abajo
    qreal y = y0 - (v0 * qSin(theta) * t - 0.5 * g * t * t);
    return QPointF(x, y);
}

void MovParabolico::setParametros(qreal v0, qreal theta, qreal g) {
    if (v0 < 0.0) {
        throw std::invalid_argument("La velocidad inicial (v0) no puede ser negativa.");
    }
    if (g < 0.0) {
        throw std::invalid_argument("La gravedad (g) no puede ser negativa.");
    }
    this->v0 = v0;
    this->theta = theta;
    this->g = g;
}

void MovParabolico::setV0(qreal v0) {
    if (v0 < 0.0) {
        throw std::invalid_argument("La velocidad inicial (v0) no puede ser negativa.");
    }
    this->v0 = v0;
}

void MovParabolico::setTheta(qreal theta) {
    this->theta = theta;
}

void MovParabolico::setGravedad(qreal g) {
    if (g < 0.0) {
        throw std::invalid_argument("La gravedad (g) no puede ser negativa.");
    }
    this->g = g;
}

qreal MovParabolico::getV0() const {
    return v0;
}

qreal MovParabolico::getTheta() const {
    return theta;
}

qreal MovParabolico::getGravedad() const {
    return g;
}
