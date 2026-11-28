#include "Accion.h"
#include "logica/Constantes.h"
#include "logica/entidades/Entidad.h"
#include "logica/entidades/Proyectil.h"

Accion::Accion()
    : ultimoProyectil(nullptr) {
}

Proyectil* Accion::ejecutarDisparo(const Entidad* lanzador, qreal v0, qreal theta,
                                   short tipoProyectil) {
    if (lanzador == nullptr) {
        return nullptr;
    }

    qreal origenX = lanzador->getPosX();
    qreal origenY = lanzador->getPosY() + lanzador->getAlto() * 0.3;

    short danio = 16;
    qreal fuerzaImpacto = 220.0;
    qreal gravedad = Constantes::GRAVEDAD_BASE;

    if (tipoProyectil == PROY_RAPIDO_LIGERO) {
        danio = 9;
        fuerzaImpacto = 160.0;
        gravedad = Constantes::GRAVEDAD_BASE;
    } else if (tipoProyectil == PROY_PESADO_ROCA) {
        danio = 16;
        fuerzaImpacto = 280.0;
        gravedad = Constantes::GRAVEDAD_BASE * Constantes::FACTOR_GRAVEDAD_PESADO;
    }

    Proyectil* nuevo = new Proyectil(origenX, origenY, v0, theta,
                                     gravedad, danio, fuerzaImpacto, tipoProyectil);
    ultimoProyectil = nuevo;
    return nuevo;
}

Proyectil* Accion::getUltimoProyectil() const {
    return ultimoProyectil;
}

void Accion::limpiarReferenciaProyectil() {
    ultimoProyectil = nullptr;
}
