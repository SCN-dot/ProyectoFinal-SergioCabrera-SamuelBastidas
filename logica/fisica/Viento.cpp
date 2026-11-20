#include "Viento.h"
#include <cmath>
#include <stdexcept>

Viento::Viento(qreal fuerza, qreal direccion,
               qreal periodoRafaga, qreal tiempoAviso, qreal duracionRafaga)
    : fuerza(0.0), direccion(direccion >= 0.0 ? 1.0 : -1.0),
      periodoRafaga(8.0), tiempoAviso(1.5),
      duracionRafaga(duracionRafaga), tiempoCiclo(0.0),
      enAviso(false), activo(false) {
    setFuerza(fuerza);
    setPeriodoRafaga(periodoRafaga);
    setTiempoAviso(tiempoAviso);
    if (duracionRafaga <= 0.0) {
        throw std::invalid_argument("La duración de la ráfaga debe ser mayor que cero.");
    }
}

void Viento::actualizar(qreal dt) {
    if (dt < 0.0) {
        return;
    }

    tiempoCiclo += dt;
    qreal cicloTotal = periodoRafaga + tiempoAviso + duracionRafaga;

    if (tiempoCiclo >= cicloTotal) {
        tiempoCiclo = std::fmod(tiempoCiclo, cicloTotal);
        // Alterna dirección en cada nuevo ciclo de ráfaga
        direccion = -direccion;
    }

    if (tiempoCiclo < periodoRafaga) {
        enAviso = false;
        activo = false;
    } else if (tiempoCiclo < periodoRafaga + tiempoAviso) {
        enAviso = true;
        activo = false;
    } else {
        enAviso = false;
        activo = true;
    }
}

qreal Viento::calcularFuerza(qreal t) const {
    qreal cicloTotal = periodoRafaga + tiempoAviso + duracionRafaga;
    qreal fase = std::fmod(std::abs(t), cicloTotal);

    // Si t está dentro de la ventana de ráfaga activa (o el estado actual está activo)
    if (activo || fase >= periodoRafaga + tiempoAviso) {
        return fuerza * direccion;
    }
    return 0.0;
}

bool Viento::hayAviso() const {
    return enAviso;
}

bool Viento::estaActivo() const {
    return activo;
}

void Viento::setFuerza(qreal fuerza) {
    if (fuerza < 0.0) {
        throw std::invalid_argument("La fuerza del viento no puede ser negativa.");
    }
    this->fuerza = fuerza;
}

void Viento::setDireccion(qreal direccion) {
    this->direccion = (direccion >= 0.0) ? 1.0 : -1.0;
}

void Viento::setPeriodoRafaga(qreal periodo) {
    if (periodo <= 0.0) {
        throw std::invalid_argument("El período de ráfaga debe ser mayor que cero.");
    }
    this->periodoRafaga = periodo;
}

void Viento::setTiempoAviso(qreal tiempo) {
    if (tiempo < 0.0) {
        throw std::invalid_argument("El tiempo de aviso del viento no puede ser negativo.");
    }
    this->tiempoAviso = tiempo;
}

qreal Viento::getFuerza() const {
    return fuerza;
}

qreal Viento::getDireccion() const {
    return direccion;
}

qreal Viento::getPeriodoRafaga() const {
    return periodoRafaga;
}

qreal Viento::getTiempoAviso() const {
    return tiempoAviso;
}
