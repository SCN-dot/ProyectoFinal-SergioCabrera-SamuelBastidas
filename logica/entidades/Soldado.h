#ifndef SOLDADO_H
#define SOLDADO_H

#include "Enemigo.h"

class Proyectil;

class Soldado : public Enemigo {
private:
    qreal tiempoRecarga;
    qreal tiempoAcumulado;
    qreal posicionObjetivoX;

public:
    Soldado(qreal x = 900.0, qreal y = 500.0, qreal tiempoRecarga = 3.0);

    void actualizar(qreal dt) override;
    Proyectil* intentarDisparar(qreal dt);

    void setPosicionObjetivo(qreal x);
};

#endif
