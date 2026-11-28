#ifndef CAPITANRIFLES_H
#define CAPITANRIFLES_H

#include "Enemigo.h"
#include "BolaCadena.h"
#include <QPointF>

class CapitanRifles : public Enemigo {
private:
    BolaCadena bolaCadena;
    qreal tiempoCombate;
    short faseActual;
    int nodoActual;
    QPointF objetivoActual;

    static QPointF posicionNodoH(int nodo);
    void elegirSiguienteObjetivo();

public:
    CapitanRifles(qreal x = 500.0, qreal y = 280.0);

    void actualizar(qreal dt) override;
    void aturdir() override;

    const BolaCadena* getBolaCadena() const;
    BolaCadena* getBolaCadena();
    short getFaseActual() const;
};

#endif
