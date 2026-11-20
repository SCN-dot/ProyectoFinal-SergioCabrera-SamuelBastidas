#include "MovCircular.h"
#include <QtMath>
#include <stdexcept>

MovCircular::MovCircular(qreal xc, qreal yc,
                         qreal radioMin, qreal radioMax,
                         qreal omega, qreal tasaExpansion)
    : ModeloFisico(xc, yc), xc(xc), yc(yc),
      radioMin(0.0), radioMax(0.0), omega(1.0), tasaExpansion(tasaExpansion) {
    setRadios(radioMin, radioMax);
    setOmega(omega);
}

qreal MovCircular::calcularRadio(qreal t) const {
    qreal radioMedio = (radioMin + radioMax) / 2.0;
    qreal amplitudRadio = (radioMax - radioMin) / 2.0;
    return radioMedio + amplitudRadio * qSin(tasaExpansion * t);
}

QPointF MovCircular::calcularPosicion(qreal t) const {
    qreal radio = calcularRadio(t);
    qreal x = xc + radio * qCos(omega * t);
    qreal y = yc + radio * qSin(omega * t);
    return QPointF(x, y);
}

void MovCircular::setCentro(qreal xc, qreal yc) {
    this->xc = xc;
    this->yc = yc;
    setOrigen(xc, yc);
}

void MovCircular::setRadios(qreal radioMin, qreal radioMax) {
    if (radioMin < 0.0 || radioMax < radioMin) {
        throw std::invalid_argument("Se requiere 0 <= radioMin <= radioMax en MovCircular.");
    }
    this->radioMin = radioMin;
    this->radioMax = radioMax;
}

void MovCircular::setOmega(qreal omega) {
    if (omega <= 0.0) {
        throw std::invalid_argument("La velocidad angular (omega) debe ser mayor que cero.");
    }
    this->omega = omega;
}

void MovCircular::setTasaExpansion(qreal tasa) {
    this->tasaExpansion = tasa;
}

qreal MovCircular::getXc() const {
    return xc;
}

qreal MovCircular::getYc() const {
    return yc;
}

qreal MovCircular::getRadioMin() const {
    return radioMin;
}

qreal MovCircular::getRadioMax() const {
    return radioMax;
}

qreal MovCircular::getOmega() const {
    return omega;
}

qreal MovCircular::getTasaExpansion() const {
    return tasaExpansion;
}
