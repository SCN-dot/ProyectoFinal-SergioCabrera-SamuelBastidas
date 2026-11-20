#ifndef MODELOFISICO_H
#define MODELOFISICO_H

#include <QPointF>
#include <QtGlobal>

/**
 * @brief Clase base abstracta para los modelos físicos parametrizables.
 * Abstrae el cálculo de posición bidimensional en función del tiempo t.
 */
class ModeloFisico {
protected:
    qreal x0;
    qreal y0;

public:
    explicit ModeloFisico(qreal x0 = 0.0, qreal y0 = 0.0);
    virtual ~ModeloFisico() = default;

    /**
     * @brief Calcula la posición (x, y) en el instante de tiempo t (en segundos).
     */
    virtual QPointF calcularPosicion(qreal t) const = 0;

    void setOrigen(qreal x, qreal y);
    qreal getX0() const;
    qreal getY0() const;
};

#endif // MODELOFISICO_H
