#ifndef BARRICADA_H
#define BARRICADA_H

#include "Entidad.h"

class Barricada : public Entidad {
private:
    short resistencia;

public:
    Barricada(qreal x = 0.0, qreal y = 0.0, short resistencia = 1);

    void actualizar(qreal dt) override;
    void recibirImpactoRoca();

    short getResistencia() const;
};

#endif
