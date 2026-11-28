#include "CapitanRifles.h"
#include "logica/Constantes.h"
#include <QRandomGenerator>
#include <QtMath>

namespace {
constexpr qreal H_X_IZQ = 240.0;
constexpr qreal H_X_DER = 720.0;
constexpr qreal H_Y_ARRIBA = 120.0;
constexpr qreal H_Y_CENTRO = 285.0;
constexpr qreal H_Y_ABAJO = 450.0;
}

CapitanRifles::CapitanRifles(qreal x, qreal y)
    : Enemigo(x, y, 56.0, 72.0, Constantes::SPR_CAPITAN_RIFLES, 75.0),
      bolaCadena(x + 28.0, y + 36.0, 55.0, 175.0, 2.2, 1.4),
      tiempoCombate(0.0),
      faseActual(1),
      nodoActual(QRandomGenerator::global()->bounded(2) == 0 ? 1 : 4),
      objetivoActual(posicionNodoH(nodoActual)) {
}

QPointF CapitanRifles::posicionNodoH(int nodo) {
    switch (nodo) {
    case 0: return QPointF(H_X_IZQ, H_Y_ARRIBA);
    case 1: return QPointF(H_X_IZQ, H_Y_CENTRO);
    case 2: return QPointF(H_X_IZQ, H_Y_ABAJO);
    case 3: return QPointF(H_X_DER, H_Y_ARRIBA);
    case 4: return QPointF(H_X_DER, H_Y_CENTRO);
    case 5: return QPointF(H_X_DER, H_Y_ABAJO);
    default: return QPointF(H_X_IZQ, H_Y_CENTRO);
    }
}

void CapitanRifles::elegirSiguienteObjetivo() {

    static constexpr int vecinos[6][3] = {
        {1, -1, -1},
        {0,  2,  4},
        {1, -1, -1},
        {4, -1, -1},
        {3,  5,  1},
        {4, -1, -1}
    };
    static constexpr int conteoVecinos[6] = {1, 3, 1, 1, 3, 1};

    int indice = (nodoActual >= 0 && nodoActual < 6) ? nodoActual : 1;
    int opciones = conteoVecinos[indice];
    int eleccion = QRandomGenerator::global()->bounded(opciones);
    nodoActual = vecinos[indice][eleccion];
    objetivoActual = posicionNodoH(nodoActual);
}

void CapitanRifles::actualizar(qreal dt) {
    if (!activa || dt < 0.0) {
        return;
    }

    tiempoCombate += dt;

    short nuevaFase = 1;
    if (tiempoCombate >= 80.0) {
        nuevaFase = 3;
    } else if (tiempoCombate >= 40.0) {
        nuevaFase = 2;
    }

    if (nuevaFase != faseActual) {
        faseActual = nuevaFase;
        if (faseActual == 2) {
            bolaCadena.setVelocidadAngular(3.2);
        } else if (faseActual == 3) {
            bolaCadena.setVelocidadAngular(4.4);
        }
    }

    qreal dx = objetivoActual.x() - posX;
    qreal dy = objetivoActual.y() - posY;
    qreal dist = qHypot(dx, dy);

    if (dist < 5.0) {
        posX = objetivoActual.x();
        posY = objetivoActual.y();
        elegirSiguienteObjetivo();
    } else {
        qreal paso = velocidadMovimiento * dt;
        if (paso >= dist) {
            posX = objetivoActual.x();
            posY = objetivoActual.y();
            elegirSiguienteObjetivo();
        } else {
            posX += (dx / dist) * paso;
            posY += (dy / dist) * paso;
        }
    }

    bolaCadena.setCentro(posX + ancho / 2.0, posY + alto / 2.0);
    bolaCadena.actualizar(dt);
}

void CapitanRifles::aturdir() {

    aturdido = false;
}

const BolaCadena* CapitanRifles::getBolaCadena() const {
    return &bolaCadena;
}

BolaCadena* CapitanRifles::getBolaCadena() {
    return &bolaCadena;
}

short CapitanRifles::getFaseActual() const {
    return faseActual;
}
