#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Entidad.h"

class Enemigo : public Entidad {
protected:
    bool aturdido;
    qreal velocidadMovimiento;
    qreal direccionRetiro;

public:
    Enemigo(qreal x = 0.0, qreal y = 0.0,
            qreal ancho = 40.0, qreal alto = 48.0,
            short spriteId = -1, qreal velocidad = 60.0);
    virtual ~Enemigo() = default;

    virtual void aturdir();
    void retirarse(qreal dt);
    bool estaAturdido() const;
};

#endif
