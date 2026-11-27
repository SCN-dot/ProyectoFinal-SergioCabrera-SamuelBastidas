#include "MemoriaNivel.h"
#include "logica/Constantes.h"
#include <stdexcept>

MemoriaNivel::MemoriaNivel()
    : aciertos(new short[Constantes::TAMANIO_MEMORIA]{0}),
      fallos(new short[Constantes::TAMANIO_MEMORIA]{0}),
      fallosPorSalto(0),
      tendenciaEvasion(false) {
}

MemoriaNivel::~MemoriaNivel() {
    delete[] aciertos;
    delete[] fallos;
    aciertos = nullptr;
    fallos = nullptr;
}

int MemoriaNivel::calcularIndice(short tipoDisparo, short estadoKirby) const {
    if (tipoDisparo < 0 || tipoDisparo >= NUM_TIROS ||
        estadoKirby < 0 || estadoKirby >= NUM_ESTADOS) {
        throw std::out_of_range("Índice fuera de rango en MemoriaNivel (tipoDisparo o estadoKirby inválido).");
    }
    return tipoDisparo * NUM_ESTADOS + estadoKirby;
}

void MemoriaNivel::registrarAcierto(short tipoDisparo, short estadoKirby) {
    int idx = calcularIndice(tipoDisparo, estadoKirby);
    aciertos[idx]++;
}

void MemoriaNivel::registrarFallo(short tipoDisparo, short estadoKirby) {
    int idx = calcularIndice(tipoDisparo, estadoKirby);
    fallos[idx]++;
}

short MemoriaNivel::getAciertos(short tipoDisparo, short estadoKirby) const {
    int idx = calcularIndice(tipoDisparo, estadoKirby);
    return aciertos[idx];
}

short MemoriaNivel::getFallos(short tipoDisparo, short estadoKirby) const {
    int idx = calcularIndice(tipoDisparo, estadoKirby);
    return fallos[idx];
}

void MemoriaNivel::incrementarFallosSalto() {
    fallosPorSalto++;
}

short MemoriaNivel::getFallosPorSalto() const {
    return fallosPorSalto;
}

bool MemoriaNivel::hayTendenciaEvasion() const {
    return tendenciaEvasion;
}

void MemoriaNivel::activarTendenciaEvasion(bool activar) {
    tendenciaEvasion = activar;
}

void MemoriaNivel::reiniciar() {
    for (int i = 0; i < Constantes::TAMANIO_MEMORIA; ++i) {
        aciertos[i] = 0;
        fallos[i] = 0;
    }
    fallosPorSalto = 0;
    tendenciaEvasion = false;
}
