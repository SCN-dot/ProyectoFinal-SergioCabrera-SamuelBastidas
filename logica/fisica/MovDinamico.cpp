#include "MovDinamico.h"
#include <stdexcept>

MovDinamico::MovDinamico(qreal x0, qreal y0, qreal masa,
                         qreal v0x, qreal v0y, qreal fx, qreal fy)
    : ModeloFisico(x0, y0), masa(1.0),
      velInicialX(v0x), velInicialY(v0y),
      fuerzaX(fx), fuerzaY(fy) {
    setMasa(masa);
}

QPointF MovDinamico::calcularPosicion(qreal t) const {
    qreal ax = fuerzaX / masa;
    qreal ay = fuerzaY / masa;
    qreal x = x0 + velInicialX * t + 0.5 * ax * t * t;
    qreal y = y0 + velInicialY * t + 0.5 * ay * t * t;
    return QPointF(x, y);
}

void MovDinamico::setMasa(qreal m) {
    if (m <= 0.0) {
        throw std::invalid_argument("La masa (m) debe ser estrictamente mayor que cero.");
    }
    masa = m;
}

void MovDinamico::setVelocidadInicial(qreal vx, qreal vy) {
    velInicialX = vx;
    velInicialY = vy;
}

void MovDinamico::setFuerza(qreal fx, qreal fy) {
    fuerzaX = fx;
    fuerzaY = fy;
}

qreal MovDinamico::getMasa() const {
    return masa;
}

qreal MovDinamico::getAceleracionX() const {
    return fuerzaX / masa;
}

qreal MovDinamico::getAceleracionY() const {
    return fuerzaY / masa;
}

qreal MovDinamico::getFuerzaX() const {
    return fuerzaX;
}

qreal MovDinamico::getFuerzaY() const {
    return fuerzaY;
}
