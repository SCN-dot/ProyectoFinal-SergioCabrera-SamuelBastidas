#ifndef BOLACADENA_H
#define BOLACADENA_H

#include "Entidad.h"
#include "logica/fisica/MovCircular.h"

class Kirby;

class BolaCadena : public Entidad {
private:
    MovCircular modeloEspiral;
    qreal tiempoAcumulado;

public:
    BolaCadena(qreal xc = 500.0, qreal yc = 300.0,
               qreal radioMin = 50.0, qreal radioMax = 150.0,
               qreal omega = 2.2, qreal tasaExpansion = 1.5);

    void actualizar(qreal dt) override;
    bool golpea(const Kirby* k) const;

    void setCentro(qreal xc, qreal yc);
    void setVelocidadAngular(qreal omega);

    qreal getCentroX() const;
    qreal getCentroY() const;
};

#endif
