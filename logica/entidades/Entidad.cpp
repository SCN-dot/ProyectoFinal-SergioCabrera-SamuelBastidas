#include "Entidad.h"

Entidad::Entidad(qreal x, qreal y, qreal ancho, qreal alto, short spriteId)
    : posX(x), posY(y), velX(0.0), velY(0.0),
      ancho(ancho), alto(alto), spriteId(spriteId),
      frame(0), activa(true) {
}

void Entidad::mover(qreal dx, qreal dy) {
    posX += dx;
    posY += dy;
}

void Entidad::siguienteFrame() {
    frame = (frame + 1) % 4;
}

QRectF Entidad::cajaColision() const {
    return QRectF(posX, posY, ancho, alto);
}

bool Entidad::colisionaCon(const Entidad* otra) const {
    if (otra == nullptr || !activa || !otra->estaActiva()) {
        return false;
    }
    return cajaColision().intersects(otra->cajaColision());
}

qreal Entidad::getPosX() const { return posX; }
qreal Entidad::getPosY() const { return posY; }
qreal Entidad::getVelX() const { return velX; }
qreal Entidad::getVelY() const { return velY; }
qreal Entidad::getAncho() const { return ancho; }
qreal Entidad::getAlto() const { return alto; }
short Entidad::getSpriteId() const { return spriteId; }
short Entidad::getFrame() const { return frame; }
bool Entidad::estaActiva() const { return activa; }

void Entidad::setPosicion(qreal x, qreal y) {
    posX = x;
    posY = y;
}

void Entidad::setVelocidad(qreal vx, qreal vy) {
    velX = vx;
    velY = vy;
}

void Entidad::setSpriteId(short id) {
    spriteId = id;
}

void Entidad::setActiva(bool estado) {
    activa = estado;
}
