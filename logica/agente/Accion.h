#ifndef ACCION_H
#define ACCION_H

#include "logica/Constantes.h"
#include <QtGlobal>

class Entidad;
class Proyectil;

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

#endif
