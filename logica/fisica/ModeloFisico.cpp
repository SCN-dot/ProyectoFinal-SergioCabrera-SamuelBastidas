#include "ModeloFisico.h"

ModeloFisico::ModeloFisico(qreal x0, qreal y0)
    : x0(x0), y0(y0) {
}

void ModeloFisico::setOrigen(qreal x, qreal y) {
    x0 = x;
    y0 = y;
}

qreal ModeloFisico::getX0() const {
    return x0;
}

qreal ModeloFisico::getY0() const {
    return y0;
}
