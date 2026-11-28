#ifndef OFICIALPATRIOTA_H
#define OFICIALPATRIOTA_H

#include "Enemigo.h"
#include "logica/agente/AgenteAutonomo.h"

class Kirby;
class MemoriaNivel;
class Proyectil;

class OficialPatriota : public Enemigo {
private:
    AgenteAutonomo agente;
    qreal tiempoRecarga;
    qreal tiempoAcumulado;
    qreal posicionObjetivoX;

public:
    OficialPatriota(qreal x = 920.0, qreal y = 496.0,
                    qreal tiempoRecarga = 2.5, short umbralFallos = 4);

    void actualizar(qreal dt) override;
    Proyectil* actualizarIA(qreal dt, Kirby* kirby, MemoriaNivel* memoria);
    void evaluarDisparoPendiente(MemoriaNivel* memoria);

    void setPosicionObjetivo(qreal x);
    void setTiempoRecarga(qreal recarga);
    void setUmbralFallos(short umbral);
    bool estaEnModoPreventivo() const;
};

#endif
