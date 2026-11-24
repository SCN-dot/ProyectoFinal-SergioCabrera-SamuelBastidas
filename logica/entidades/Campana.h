#ifndef CAMPANA_H
#define CAMPANA_H

#include "Entidad.h"
#include "logica/fisica/MovArmonico.h"

class Proyectil;

/**
 * @brief Campana monumental de la catedral en el Nivel 1.
 * Oscila horizontalmente con movimiento armónico simple y bloquea proyectiles.
 */
class Campana : public Entidad {
private:
    MovArmonico modeloOscilacion;
    qreal tiempoAcumulado;

public:
    Campana(qreal xCentro = 180.0, qreal y = 160.0,
            qreal amplitud = 70.0, qreal periodo = 2.0);

    void actualizar(qreal dt) override;
    bool detiene(const Proyectil* p) const;

    void setPeriodo(qreal periodo);
};

#endif // CAMPANA_H
