#ifndef MOVARMONICO_H
#define MOVARMONICO_H

#include "ModeloFisico.h"

/**
 * @brief Modelo de Movimiento Armónico Simple (oscilación horizontal).
 * Ecuación:
 *   x(t) = x0 + A * cos(omega * t + fase), donde omega = 2 * pi / T
 */
class MovArmonico : public ModeloFisico {
private:
    qreal amplitud;
    qreal omega;
    qreal fase;

public:
    MovArmonico(qreal x0 = 0.0, qreal y0 = 0.0,
                qreal amplitud = 50.0, qreal periodo = 2.0, qreal fase = 0.0);

    QPointF calcularPosicion(qreal t) const override;

    void setPeriodo(qreal periodo);
    void setAmplitud(qreal amplitud);
    void setFase(qreal fase);

    qreal getAmplitud() const;
    qreal getOmega() const;
    qreal getFase() const;
};

#endif // MOVARMONICO_H
