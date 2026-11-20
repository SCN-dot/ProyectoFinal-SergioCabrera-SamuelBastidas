#ifndef MOVDINAMICO_H
#define MOVDINAMICO_H

#include "ModeloFisico.h"

/**
 * @brief Modelo de dinámica newtoniana con masa variable (a = F / m).
 * Ecuaciones:
 *   ax = Fx / m, ay = Fy / m
 *   x(t) = x0 + v0x * t + 0.5 * ax * t^2
 *   y(t) = y0 + v0y * t + 0.5 * ay * t^2
 */
class MovDinamico : public ModeloFisico {
private:
    qreal masa;
    qreal velInicialX;
    qreal velInicialY;
    qreal fuerzaX;
    qreal fuerzaY;

public:
    MovDinamico(qreal x0 = 0.0, qreal y0 = 0.0, qreal masa = 1.0,
                qreal v0x = 0.0, qreal v0y = 0.0,
                qreal fx = 0.0, qreal fy = 0.0);

    QPointF calcularPosicion(qreal t) const override;

    void setMasa(qreal m);
    void setVelocidadInicial(qreal vx, qreal vy);
    void setFuerza(qreal fx, qreal fy);

    qreal getMasa() const;
    qreal getAceleracionX() const;
    qreal getAceleracionY() const;
    qreal getFuerzaX() const;
    qreal getFuerzaY() const;
};

#endif // MOVDINAMICO_H
