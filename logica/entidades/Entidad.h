#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QRectF>
#include <QtGlobal>

class Entidad {
protected:
    qreal posX;
    qreal posY;
    qreal velX;
    qreal velY;
    qreal ancho;
    qreal alto;
    short spriteId;
    short frame;
    bool activa;

public:
    Entidad(qreal x = 0.0, qreal y = 0.0,
            qreal ancho = 32.0, qreal alto = 32.0,
            short spriteId = -1);
    virtual ~Entidad() = default;

    virtual void mover(qreal dx, qreal dy);
    virtual void siguienteFrame();

    QRectF cajaColision() const;
    bool colisionaCon(const Entidad* otra) const;

    virtual void actualizar(qreal dt) = 0;

    qreal getPosX() const;
    qreal getPosY() const;
    qreal getVelX() const;
    qreal getVelY() const;
    qreal getAncho() const;
    qreal getAlto() const;
    short getSpriteId() const;
    short getFrame() const;
    bool estaActiva() const;

    void setPosicion(qreal x, qreal y);
    void setVelocidad(qreal vx, qreal vy);
    void setSpriteId(short id);
    void setActiva(bool estado);
};

#endif
