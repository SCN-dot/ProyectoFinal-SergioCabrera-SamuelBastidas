#include "Percepcion.h"
#include "logica/entidades/Entidad.h"
#include "logica/entidades/Kirby.h"
#include "logica/entidades/Proyectil.h"
#include <QtMath>

Percepcion::Percepcion()
    : estadoKirby(0),
      alturaKirby(0.0),
      distanciaKirby(0.0),
      deltaY(0.0),
      objetivoALaIzquierda(true),
      hayResultado(false),
      ultimoAcerto(false) {
}

void Percepcion::percibir(const Kirby* k, const Entidad* oficial) {
    if (k == nullptr || oficial == nullptr) {
        return;
    }

    estadoKirby = k->getEstado();

    qreal kx = k->getPosX() + k->getAncho() / 2.0;
    qreal ky = k->getPosY() + k->getAlto() / 2.0;
    qreal ox = oficial->getPosX() + oficial->getAncho() / 2.0;
    qreal oy = oficial->getPosY() + oficial->getAlto() / 2.0;

    alturaKirby = ky;
    distanciaKirby = qAbs(ox - kx);
    objetivoALaIzquierda = (kx <= ox);

    // En pantalla Y crece hacia abajo: deltaY positivo indica que Kirby está más arriba
    deltaY = oy - ky;
}

void Percepcion::percibirResultado(const Proyectil* p) {
    if (p == nullptr) {
        hayResultado = false;
        return;
    }

    // Si el proyectil aún está en vuelo, todavía no hay veredicto definitivo
    if (p->estaActiva()) {
        hayResultado = false;
        return;
    }

    hayResultado = true;
    ultimoAcerto = p->getAcertoKirby();
}

void Percepcion::limpiarResultado() {
    hayResultado = false;
    ultimoAcerto = false;
}

short Percepcion::getEstadoKirby() const { return estadoKirby; }
qreal Percepcion::getAlturaKirby() const { return alturaKirby; }
qreal Percepcion::getDistanciaKirby() const { return distanciaKirby; }
qreal Percepcion::getDeltaY() const { return deltaY; }
bool Percepcion::estaALaIzquierda() const { return objetivoALaIzquierda; }
bool Percepcion::tieneResultado() const { return hayResultado; }
bool Percepcion::getUltimoAcerto() const { return ultimoAcerto; }
