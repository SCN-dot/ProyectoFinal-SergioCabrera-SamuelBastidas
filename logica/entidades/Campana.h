#ifndef CAMPANA_H
#define CAMPANA_H

#include "Entidad.h"
#include "logica/fisica/MovArmonico.h"

class Proyectil;

class Campana : public Entidad {
private:
    MovArmonico modeloOscilacion;
    qreal tiempoAcumulado;
    bool suelta;
    bool cubriendoPuerta;
    qreal velocidadCaida;

public:
    Campana(qreal xCentro = 180.0, qreal y = 160.0,
            qreal amplitud = 70.0, qreal periodo = 2.0);

    void actualizar(qreal dt) override;
    bool detiene(const Proyectil* p) const;
    void soltar();

    void setPeriodo(qreal periodo);

    bool estaSuelta() const;
    bool estaCubriendoPuerta() const;
    qreal getVelocidadCaida() const;
};

#endif
