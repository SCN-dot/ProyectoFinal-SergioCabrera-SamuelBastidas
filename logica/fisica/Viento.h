#ifndef VIENTO_H
#define VIENTO_H

#include <QtGlobal>

/**
 * @brief Perturbación ambiental periódica que genera ráfagas de viento horizontal.
 * Emite un aviso previo antes de activar la fuerza física del viento.
 */
class Viento {
private:
    qreal fuerza;
    qreal direccion;       // 1.0 (derecha) o -1.0 (izquierda)
    qreal periodoRafaga;   // Tiempo entre ráfagas (segundos)
    qreal tiempoAviso;     // Duración de la alerta previa (segundos)
    qreal duracionRafaga;  // Duración de la ráfaga activa (segundos)
    qreal tiempoCiclo;     // Acumulador interno del ciclo actual
    bool enAviso;
    bool activo;

public:
    Viento(qreal fuerza = 150.0, qreal direccion = -1.0,
           qreal periodoRafaga = 8.0, qreal tiempoAviso = 1.5,
           qreal duracionRafaga = 2.5);

    void actualizar(qreal dt);
    qreal calcularFuerza(qreal t) const;
    bool hayAviso() const;
    bool estaActivo() const;

    void setFuerza(qreal fuerza);
    void setDireccion(qreal direccion);
    void setPeriodoRafaga(qreal periodo);
    void setTiempoAviso(qreal tiempo);

    qreal getFuerza() const;
    qreal getDireccion() const;
    qreal getPeriodoRafaga() const;
    qreal getTiempoAviso() const;
};

#endif // VIENTO_H
