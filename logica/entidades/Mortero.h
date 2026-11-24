#ifndef MORTERO_H
#define MORTERO_H

#include "Proyectil.h"
#include <QPointF>

/**
 * @brief Proyectil de artillería del Nivel 2 con fase previa de advertencia visual.
 * Permanece en aviso mostrando su sombra en puntoImpacto antes de caer parabólicamente.
 */
class Mortero : public Proyectil {
private:
    QPointF puntoImpacto;
    qreal tiempoAviso;
    qreal tiempoTranscurrido;
    bool enAviso;
    bool exploto;

public:
    Mortero(const QPointF& puntoImpacto, qreal tiempoAviso = 1.5, short danio = 20);

    void actualizar(qreal dt) override;

    bool estaEnAviso() const;
    bool haExplotado() const;
    QPointF getPuntoImpacto() const;
    qreal getProgresoAviso() const;
};

#endif // MORTERO_H
