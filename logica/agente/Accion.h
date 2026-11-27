#ifndef ACCION_H
#define ACCION_H

#include "logica/Constantes.h"
#include <QtGlobal>

class Entidad;
class Proyectil;

/**
 * @brief Fase 3 del Agente Inteligente: Acción.
 * Materializa la decisión instanciando el Proyectil en memoria dinámica
 * y mantiene una referencia no propietaria para su evaluación posterior.
 */
class Accion {
private:
    Proyectil* ultimoProyectil;

public:
    Accion();

    Proyectil* ejecutarDisparo(const Entidad* lanzador, qreal v0, qreal theta,
                               short tipoProyectil = Constantes::PROY_ESTANDAR);
    Proyectil* getUltimoProyectil() const;
    void limpiarReferenciaProyectil();
};

#endif // ACCION_H
