#ifndef ESCALON_H
#define ESCALON_H

#include "Entidad.h"

class Escalon : public Entidad {
private:
    short indice;
    short cantidadTravesanos;

public:
    Escalon(qreal x = 0.0, qreal y = 0.0,
            qreal ancho = 72.0, qreal alto = 63.0,
            short indice = 0,
            short cantidadTravesanos = 3);

    void actualizar(qreal dt) override;

    short getIndice() const;
    short getCantidadTravesanos() const;
    qreal getSuperficieY() const;
};

#endif
