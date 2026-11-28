#ifndef TRONCO_H
#define TRONCO_H

#include "Proyectil.h"

class Tronco : public Proyectil {
private:
    qreal velocidadHorizontal;
    qreal anguloRotacion;
    short danioPuerta;

public:
    Tronco(qreal xInicial = 900.0,
           qreal velocidadHorizontal = 205.0,
           short danio = 35,
           qreal fuerzaImpacto = 260.0);

    void actualizar(qreal dt) override;

    qreal getAnguloRotacion() const;
    short getDanioPuerta() const;
};

#endif
