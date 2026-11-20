#ifndef MOVPARABOLICO_H
#define MOVPARABOLICO_H

#include "ModeloFisico.h"

/**
 * @brief Modelo de tiro parabólico balístico en coordenadas de pantalla.
 * Ecuaciones:
 *   x(t) = x0 + v0 * cos(theta) * t
 *   y(t) = y0 - (v0 * sin(theta) * t - 0.5 * g * t^2)
 */
class MovParabolico : public ModeloFisico {
private:
    qreal v0;
    qreal theta; // Ángulo en radianes
    qreal g;     // Aceleración gravitacional (>= 0)

public:
    MovParabolico(qreal x0 = 0.0, qreal y0 = 0.0,
                  qreal v0 = 0.0, qreal theta = 0.0, qreal g = 980.0);

    QPointF calcularPosicion(qreal t) const override;

    void setParametros(qreal v0, qreal theta, qreal g);
    void setV0(qreal v0);
    void setTheta(qreal theta);
    void setGravedad(qreal g);

    qreal getV0() const;
    qreal getTheta() const;
    qreal getGravedad() const;
};

#endif // MOVPARABOLICO_H
