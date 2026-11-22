#ifndef KIRBY_H
#define KIRBY_H

#include "Entidad.h"
#include "logica/fisica/MovParabolico.h"
#include "logica/fisica/MovDinamico.h"

class Adoquin;
class Alimento;
class Viento;
class Proyectil;

class Kirby : public Entidad {
private:
    short estado;
    short salud;
    short saludMaxima;
    qreal tiempoRoca;
    qreal tiempoGlobo;
    bool modoCenital;

    MovParabolico modeloSalto;
    MovDinamico modeloFuerzas;

    qreal masaBase;
    qreal velocidadBase;
    qreal tiempoSalto;
    qreal pisoY;
    qreal tiempoInvulnerable;

    void actualizarSpritePorEstado();

public:
    Kirby(qreal x = 140.0, qreal y = 460.0, short saludMaxima = 100);

    void actualizar(qreal dt) override;
    void actualizarEstado(qreal dt);

    void moverHorizontal(qreal direccion, qreal dt);
    void moverCenital(qreal dx, qreal dy, qreal dt);
    void saltar();
    void inflarGlobo();
    void desinflarGlobo();

    void absorberAdoquin(Adoquin* adoquin);
    void comer(Alimento* alimento);
    void aplicarViento(const Viento* viento);
    void recibirImpacto(const Proyectil* proyectil);
    void recibirDanio(short cantidad);

    short getEstado() const;
    short getSalud() const;
    short getSaludMaxima() const;
    qreal getMasaActual() const;
    qreal getVelocidadActual() const;
    bool estaEnRoca() const;
    bool estaEnGlobo() const;
    bool esInvulnerable() const;

    void setModoCenital(bool cenital);
    void setPisoY(qreal y);
};

#endif
