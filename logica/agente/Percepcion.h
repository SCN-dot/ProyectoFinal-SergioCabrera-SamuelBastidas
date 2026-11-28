#ifndef PERCEPCION_H
#define PERCEPCION_H

#include <QtGlobal>

class Kirby;
class Entidad;
class Proyectil;

class Percepcion {
private:
    short estadoKirby;
    qreal alturaKirby;
    qreal distanciaKirby;
    qreal deltaY;
    bool objetivoALaIzquierda;
    bool hayResultado;
    bool ultimoAcerto;

public:
    Percepcion();

    void percibir(const Kirby* k, const Entidad* oficial);
    void percibirResultado(const Proyectil* p);
    void limpiarResultado();

    short getEstadoKirby() const;
    qreal getAlturaKirby() const;
    qreal getDistanciaKirby() const;
    qreal getDeltaY() const;
    bool estaALaIzquierda() const;
    bool tieneResultado() const;
    bool getUltimoAcerto() const;
};

#endif
