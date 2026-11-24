#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "Entidad.h"
#include "logica/fisica/MovParabolico.h"

/**
 * @brief Proyectil balístico disparado por los enemigos.
 * Utiliza un modelo de tiro parabólico (MovParabolico) para su trayectoria.
 */
class Proyectil : public Entidad {
protected:
    MovParabolico modeloTrayectoria;
    short danio;
    qreal fuerzaImpacto;
    qreal tiempoVuelo;
    bool acertoKirby;

public:
    Proyectil(qreal x0 = 0.0, qreal y0 = 0.0,
              qreal v0 = 400.0, qreal theta = 0.5, qreal g = 980.0,
              short danio = 15, qreal fuerzaImpacto = 220.0);

    void actualizar(qreal dt) override;

    void marcarAciertoKirby();
    bool getAcertoKirby() const;
    short getDanio() const;
    qreal getFuerzaImpacto() const;
    qreal getDireccionHorizontal() const;
};

#endif // PROYECTIL_H
