#ifndef ALIMENTO_H
#define ALIMENTO_H

#include "Entidad.h"

class Alimento : public Entidad {
private:
    short curacion;

public:
    Alimento(qreal x = 0.0, qreal y = 0.0, short curacion = 25);

    void actualizar(qreal dt) override;
    short consumir();

    short getCuracion() const;
};

#endif
