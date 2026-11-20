#ifndef MOVCIRCULAR_H
#define MOVCIRCULAR_H

#include "ModeloFisico.h"

/**
 * @brief Modelo de movimiento circular en espiral con radio oscilante.
 * Ecuaciones:
 *   R(t) = (Rmin + Rmax) / 2 + ((Rmax - Rmin) / 2) * sin(tasaExpansion * t)
 *   x(t) = xc + R(t) * cos(omega * t)
 *   y(t) = yc + R(t) * sin(omega * t)
 */
class MovCircular : public ModeloFisico {
private:
    qreal xc;
    qreal yc;
    qreal radioMin;
    qreal radioMax;
    qreal omega;
    qreal tasaExpansion;

public:
    MovCircular(qreal xc = 0.0, qreal yc = 0.0,
                qreal radioMin = 40.0, qreal radioMax = 120.0,
                qreal omega = 2.0, qreal tasaExpansion = 1.5);

    QPointF calcularPosicion(qreal t) const override;
    qreal calcularRadio(qreal t) const;

    void setCentro(qreal xc, qreal yc);
    void setRadios(qreal radioMin, qreal radioMax);
    void setOmega(qreal omega);
    void setTasaExpansion(qreal tasa);

    qreal getXc() const;
    qreal getYc() const;
    qreal getRadioMin() const;
    qreal getRadioMax() const;
    qreal getOmega() const;
    qreal getTasaExpansion() const;
};

#endif // MOVCIRCULAR_H
