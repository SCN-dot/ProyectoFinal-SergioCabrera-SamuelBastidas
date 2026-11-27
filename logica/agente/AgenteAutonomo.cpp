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

    // Si hay un disparo previo pendiente de evaluación y ya terminó su vuelo, evaluarlo
    evaluarUltimoDisparo(mem);

    // 1. Percepción
    percepcion.percibir(k, host);

    // 2. Razonamiento
    qreal v0 = 0.0;
    qreal thetaRad = 0.0;
    short tipoProyectil = PROY_RAPIDO_LIGERO;
    razonamiento.decidir(percepcion, mem, v0, thetaRad, tipoProyectil);

    ultimoTipoDisparo = razonamiento.getTipoDisparoSeleccionado();
    ultimoEstadoObjetivo = percepcion.getEstadoKirby();

    // 3. Acción
    return accion.ejecutarDisparo(host, v0, thetaRad, tipoProyectil);
}

void AgenteAutonomo::evaluarUltimoDisparo(MemoriaNivel* mem) {
    Proyectil* p = accion.getUltimoProyectil();
    if (p == nullptr) {
        return;
    }

    // 4. Aprendizaje (solo si el proyectil ya finalizó su trayectoria)
    percepcion.percibirResultado(p);
    if (percepcion.tieneResultado()) {
        aprendizaje.evaluarYRegistrar(percepcion, ultimoTipoDisparo,
                                      ultimoEstadoObjetivo, mem, &razonamiento);
        percepcion.limpiarResultado();
        // Anular referencia no propietaria tras evaluar para evitar puntero colgante
        accion.limpiarReferenciaProyectil();
    }
}

void AgenteAutonomo::setUmbralFallos(short umbral) {
    aprendizaje.setUmbralFallos(umbral);
}

bool AgenteAutonomo::estaEnModoPreventivo() const {
    return razonamiento.estaEnModoPreventivo();
}
