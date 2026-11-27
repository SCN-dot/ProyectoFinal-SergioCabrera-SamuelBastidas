#include "Aprendizaje.h"
#include "MemoriaNivel.h"
#include "Percepcion.h"
#include "Razonamiento.h"
#include "logica/Constantes.h"
#include <stdexcept>

Aprendizaje::Aprendizaje(short umbralFallos)
    : umbralFallos(umbralFallos > 0 ? umbralFallos : 4) {
}

void Aprendizaje::evaluarYRegistrar(const Percepcion& percepcion,
                                    short tipoDisparo,
                                    short estadoObjetivo,
                                    MemoriaNivel* memoria,
                                    Razonamiento* razonamiento) {
    if (!percepcion.tieneResultado() || memoria == nullptr) {
        return;
    }

    if (percepcion.getUltimoAcerto()) {
        memoria->registrarAcierto(tipoDisparo, estadoObjetivo);
    } else {
        memoria->registrarFallo(tipoDisparo, estadoObjetivo);

        if (estadoObjetivo == ESTADO_SALTANDO || estadoObjetivo == ESTADO_GLOBO) {
            memoria->incrementarFallosSalto();
        }

        if (memoria->getFallosPorSalto() >= umbralFallos) {
            memoria->activarTendenciaEvasion(true);
            adaptar(razonamiento);
        }
    }
}

void Aprendizaje::adaptar(Razonamiento* razonamiento) {
    if (razonamiento == nullptr) {
        return;
    }
    razonamiento->activarModoPreventivo(true);
    razonamiento->reajustarAngulos(34.0, 58.0, 68.0);
}

void Aprendizaje::setUmbralFallos(short umbral) {
    if (umbral <= 0) {
        throw std::invalid_argument("El umbral de fallos del agente debe ser mayor que cero.");
    }
    umbralFallos = umbral;
}

short Aprendizaje::getUmbralFallos() const {
    return umbralFallos;
}
