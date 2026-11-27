#ifndef AGENTEAUTONOMO_H
#define AGENTEAUTONOMO_H

#include "Percepcion.h"
#include "Razonamiento.h"
#include "Accion.h"
#include "Aprendizaje.h"

class Kirby;
class Entidad;
class MemoriaNivel;
class Proyectil;

/**
 * @brief Coordinador del ciclo cognitivo de 4 fases del Oficial Patriota:
 * Percepción -> Razonamiento -> Acción -> Aprendizaje.
 */
class AgenteAutonomo {
private:
    Percepcion percepcion;
    Razonamiento razonamiento;
    Accion accion;
    Aprendizaje aprendizaje;

    short ultimoTipoDisparo;
    short ultimoEstadoObjetivo;

public:
    explicit AgenteAutonomo(short umbralFallos = 4);

    Proyectil* ejecutarCiclo(Kirby* k, Entidad* host, MemoriaNivel* mem);
    void evaluarUltimoDisparo(MemoriaNivel* mem);

    void setUmbralFallos(short umbral);
    bool estaEnModoPreventivo() const;
};

#endif // AGENTEAUTONOMO_H
