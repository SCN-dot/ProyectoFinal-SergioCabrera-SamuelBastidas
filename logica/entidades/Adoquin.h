#ifndef ADOQUIN_H
#define ADOQUIN_H

#include "Entidad.h"

class Adoquin : public Entidad {
public:
    Adoquin(qreal x = 0.0, qreal y = 0.0);

    void actualizar(qreal dt) override;
    void recoger();
};

#endif
