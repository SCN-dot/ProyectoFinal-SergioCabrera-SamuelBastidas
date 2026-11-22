#include "Kirby.h"
#include "Adoquin.h"
#include "Alimento.h"
#include "Proyectil.h"
#include "logica/Constantes.h"
#include "logica/fisica/Viento.h"
#include <QtMath>
#include <stdexcept>

Kirby::Kirby(qreal x, qreal y, short saludMaxima)
    : Entidad(x, y, 40.0, 40.0, Constantes::SPR_KIRBY_REPOSO),
      estado(ESTADO_SUELO),
      salud(saludMaxima),
      saludMaxima(saludMaxima),
      tiempoRoca(0.0),
      tiempoGlobo(0.0),
      modoCenital(false),
      modeloSalto(x, y, 520.0, M_PI / 2.0, Constantes::GRAVEDAD_BASE),
      modeloFuerzas(x, y, 10.0, 0.0, 0.0, 0.0, 0.0),
      masaBase(10.0),
      velocidadBase(240.0),
      tiempoSalto(0.0),
      pisoY(Constantes::PISO_NIVEL1),
      tiempoInvulnerable(0.0) {
    if (saludMaxima <= 0) {
        throw std::invalid_argument("La salud máxima de Kirby debe ser mayor que cero.");
    }
}

void Kirby::actualizarSpritePorEstado() {
    switch (estado) {
    case ESTADO_ROCA:
        spriteId = Constantes::SPR_KIRBY_ROCA;
        break;
    case ESTADO_GLOBO:
        spriteId = Constantes::SPR_KIRBY_GLOBO;
        break;
    case ESTADO_SALTANDO:
        spriteId = Constantes::SPR_KIRBY_SALTANDO;
        break;
    case ESTADO_SUELO:
    default:
        spriteId = (qAbs(velX) > 1.0) ? Constantes::SPR_KIRBY_CAMINANDO
                                      : Constantes::SPR_KIRBY_REPOSO;
        break;
    }
}

void Kirby::actualizarEstado(qreal dt) {
    if (tiempoInvulnerable > 0.0) {
        tiempoInvulnerable -= dt;
        if (tiempoInvulnerable < 0.0) {
            tiempoInvulnerable = 0.0;
        }
    }

    if (estado == ESTADO_ROCA) {
        tiempoRoca -= dt;
        if (tiempoRoca <= 0.0) {
            tiempoRoca = 0.0;
            estado = ESTADO_SUELO;
            modeloFuerzas.setMasa(masaBase);
        }
    } else if (estado == ESTADO_GLOBO) {
        tiempoGlobo -= dt;
        if (tiempoGlobo <= 0.0) {
            desinflarGlobo();
        }
    }
}

void Kirby::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    actualizarEstado(dt);

    qreal ax = modeloFuerzas.getAceleracionX();
    velX += ax * dt;
    posX += velX * dt;

    velX *= 0.88;
    if (qAbs(velX) < 1.0) {
        velX = 0.0;
    }
    modeloFuerzas.setFuerza(0.0, 0.0);

    if (!modoCenital) {
        if (estado == ESTADO_SALTANDO) {
            tiempoSalto += dt;
            QPointF posSalto = modeloSalto.calcularPosicion(tiempoSalto);
            posY = posSalto.y();

            if (posY + alto >= pisoY) {
                posY = pisoY - alto;
                estado = ESTADO_SUELO;
                tiempoSalto = 0.0;
            }
        } else if (estado == ESTADO_GLOBO) {

            qreal gravedadEfectiva = Constantes::GRAVEDAD_BASE * 0.30;
            velY += gravedadEfectiva * dt;
            if (velY > 110.0) {
                velY = 110.0;
            }
            posY += velY * dt;

            if (posY < 20.0) {
                posY = 20.0;
                velY = 0.0;
            }
            if (posY + alto >= pisoY) {
                posY = pisoY - alto;
                velY = 0.0;
                desinflarGlobo();
            }
        } else {

            if (posY + alto < pisoY) {
                velY += Constantes::GRAVEDAD_BASE * dt;
                posY += velY * dt;
                if (posY + alto >= pisoY) {
                    posY = pisoY - alto;
                    velY = 0.0;
                }
            } else {
                posY = pisoY - alto;
                velY = 0.0;
            }
        }
    }

    if (posX < 0.0) {
        posX = 0.0;
    } else if (posX + ancho > Constantes::ANCHO_ESCENARIO) {
        posX = Constantes::ANCHO_ESCENARIO - ancho;
    }

    if (modoCenital) {
        if (posY < 0.0) {
            posY = 0.0;
        } else if (posY + alto > Constantes::ALTO_ESCENARIO) {
            posY = Constantes::ALTO_ESCENARIO - alto;
        }
    }

    actualizarSpritePorEstado();
}

void Kirby::moverHorizontal(qreal direccion, qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }
    qreal desplazamiento = direccion * getVelocidadActual() * dt;
    posX += desplazamiento;
    if (posX < 0.0) {
        posX = 0.0;
    } else if (posX + ancho > Constantes::ANCHO_ESCENARIO) {
        posX = Constantes::ANCHO_ESCENARIO - ancho;
    }
}

void Kirby::moverCenital(qreal dx, qreal dy, qreal dt) {
    if (!activa || !modoCenital || dt < 0.0) {
        return;
    }
    qreal norma = qSqrt(dx * dx + dy * dy);
    if (norma > 0.0) {
        dx /= norma;
        dy /= norma;
    }
    qreal vel = getVelocidadActual();
    posX += dx * vel * dt;
    posY += dy * vel * dt;
}

void Kirby::saltar() {
    if (!activa || modoCenital || estado == ESTADO_ROCA) {
        return;
    }
    if (estado == ESTADO_SUELO) {
        estado = ESTADO_SALTANDO;
        tiempoSalto = 0.0;
        modeloSalto.setOrigen(posX, posY);
        modeloSalto.setParametros(520.0, M_PI / 2.0, Constantes::GRAVEDAD_BASE);
    }
}

void Kirby::inflarGlobo() {
    if (!activa || modoCenital || estado == ESTADO_ROCA) {
        return;
    }
    estado = ESTADO_GLOBO;
    tiempoGlobo = 4.5;
    modeloFuerzas.setMasa(masaBase * 0.25);
    velY = -180.0;
}

void Kirby::desinflarGlobo() {
    if (estado == ESTADO_GLOBO) {
        estado = ESTADO_SUELO;
        tiempoGlobo = 0.0;
        modeloFuerzas.setMasa(masaBase);
    }
}

void Kirby::absorberAdoquin(Adoquin* adoquin) {
    if (adoquin == nullptr || !adoquin->estaActiva()) {
        return;
    }
    adoquin->recoger();
    estado = ESTADO_ROCA;
    tiempoRoca = 8.0;
    tiempoGlobo = 0.0;
    modeloFuerzas.setMasa(masaBase * 5.0);
    if (posY + alto < pisoY && !modoCenital) {
        velY = 300.0;
    }
}

void Kirby::comer(Alimento* alimento) {
    if (alimento == nullptr || !alimento->estaActiva()) {
        return;
    }
    short curacion = alimento->consumir();
    salud += curacion;
    if (salud > saludMaxima) {
        salud = saludMaxima;
    }
}

void Kirby::aplicarViento(const Viento* viento) {
    if (viento == nullptr || !viento->estaActivo()) {
        return;
    }

    if (estado == ESTADO_ROCA) {
        return;
    }
    qreal fuerzaViento = viento->calcularFuerza(0.0);

    modeloFuerzas.setFuerza(fuerzaViento * 12.0, 0.0);
}

void Kirby::recibirImpacto(const Proyectil* proyectil) {
    if (proyectil == nullptr || !activa) {
        return;
    }

    if (estado != ESTADO_ROCA) {
        qreal fuerza = proyectil->getFuerzaImpacto() * proyectil->getDireccionHorizontal();
        modeloFuerzas.setFuerza(fuerza * 15.0, 0.0);
        velX += (fuerza / modeloFuerzas.getMasa()) * 4.5;
    }

    recibirDanio(proyectil->getDanio());
}

void Kirby::recibirDanio(short cantidad) {
    if (cantidad <= 0 || tiempoInvulnerable > 0.0 || !activa) {
        return;
    }

    short danioFinal = (estado == ESTADO_ROCA) ? static_cast<short>(cantidad / 2) : cantidad;
    salud -= danioFinal;
    if (salud <= 0) {
        salud = 0;
        activa = false;
    } else {
        tiempoInvulnerable = 0.6;
    }
}

short Kirby::getEstado() const { return estado; }
short Kirby::getSalud() const { return salud; }
short Kirby::getSaludMaxima() const { return saludMaxima; }
qreal Kirby::getMasaActual() const { return modeloFuerzas.getMasa(); }

qreal Kirby::getVelocidadActual() const {
    if (estado == ESTADO_ROCA) {
        return velocidadBase * 0.40;
    }
    if (estado == ESTADO_GLOBO) {
        return velocidadBase * 0.85;
    }
    return velocidadBase;
}

bool Kirby::estaEnRoca() const { return estado == ESTADO_ROCA; }
bool Kirby::estaEnGlobo() const { return estado == ESTADO_GLOBO; }
bool Kirby::esInvulnerable() const { return tiempoInvulnerable > 0.0; }

void Kirby::setModoCenital(bool cenital) {
    modoCenital = cenital;
    if (cenital) {
        estado = ESTADO_SUELO;
        velY = 0.0;
    }
}

void Kirby::setPisoY(qreal y) {
    pisoY = y;
}
