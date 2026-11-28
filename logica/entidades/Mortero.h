#ifndef MORTERO_H
#define MORTERO_H

#include "Proyectil.h"
#include <QPointF>

class Mortero : public Proyectil {
private:
    QPointF puntoImpacto;
    qreal tiempoAviso;
    qreal tiempoTranscurrido;
    bool enAviso;
    bool exploto;
    qreal radioExplosion;

public:
    Mortero(const QPointF& puntoImpacto, qreal tiempoAviso = 1.5,
            short danio = 20, qreal radioExplosion = 90.0);

    void actualizar(qreal dt) override;

    bool estaEnAviso() const;
    bool haExplotado() const;
    QPointF getPuntoImpacto() const;
    qreal getProgresoAviso() const;
    qreal getRadioExplosion() const;
};

#endif
