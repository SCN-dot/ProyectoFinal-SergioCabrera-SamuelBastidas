#include "AgenteAutonomo.h"
#include "MemoriaNivel.h"
#include "logica/Constantes.h"
#include "logica/entidades/Entidad.h"
#include "logica/entidades/Kirby.h"
#include "logica/entidades/Proyectil.h"

AgenteAutonomo::AgenteAutonomo(short umbralFallos)
    : aprendizaje(umbralFallos),
      ultimoTipoDisparo(TIRO_BAJO),
      ultimoEstadoObjetivo(ESTADO_SUELO) {
}

Proyectil* AgenteAutonomo::ejecutarCiclo(Kirby* k, Entidad* host, MemoriaNivel* mem) {
    if (k == nullptr || host == nullptr) {
        return nullptr;
    }

    evaluarUltimoDisparo(mem);

    percepcion.percibir(k, host);

    qreal v0 = 0.0;
    qreal thetaRad = 0.0;
    short tipoProyectil = PROY_RAPIDO_LIGERO;
    razonamiento.decidir(percepcion, mem, v0, thetaRad, tipoProyectil);

    ultimoTipoDisparo = razonamiento.getTipoDisparoSeleccionado();
    ultimoEstadoObjetivo = percepcion.getEstadoKirby();

    return accion.ejecutarDisparo(host, v0, thetaRad, tipoProyectil);
}

void AgenteAutonomo::evaluarUltimoDisparo(MemoriaNivel* mem) {
    Proyectil* p = accion.getUltimoProyectil();
    if (p == nullptr) {
        return;
    }

    percepcion.percibirResultado(p);
    if (percepcion.tieneResultado()) {
        aprendizaje.evaluarYRegistrar(percepcion, ultimoTipoDisparo,
                                      ultimoEstadoObjetivo, mem, &razonamiento);
        percepcion.limpiarResultado();

        accion.limpiarReferenciaProyectil();
    }
}

void AgenteAutonomo::setUmbralFallos(short umbral) {
    aprendizaje.setUmbralFallos(umbral);
}

bool AgenteAutonomo::estaEnModoPreventivo() const {
    return razonamiento.estaEnModoPreventivo();
}
