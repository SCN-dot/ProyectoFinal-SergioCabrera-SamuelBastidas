#ifndef RAZONAMIENTO_H
#define RAZONAMIENTO_H

#include <QtGlobal>

class Percepcion;
class MemoriaNivel;

/**
 * @brief Fase 2 del Agente Inteligente: Razonamiento.
 * Selecciona el tipo de disparo según heurística y calcula la velocidad inicial v0
 * mediante balística inversa.
 */
class Razonamiento {
private:
    short tipoDisparoSeleccionado;
    short tipoProyectilSeleccionado;
    qreal anguloBajoGrados;
    qreal anguloAltoGrados;
    qreal anguloPreventivoGrados;
    bool modoPreventivo;

    qreal calcularVelocidadBalistica(qreal d, qreal deltaY, qreal thetaRad, qreal g) const;

public:
    Razonamiento();

    void decidir(const Percepcion& percepcion, const MemoriaNivel* memoria,
                 qreal& outV0, qreal& outThetaRad, short& outTipoProyectil);

    void activarModoPreventivo(bool activar);
    void reajustarAngulos(qreal nuevoBajo, qreal nuevoAlto, qreal nuevoPreventivo);

    short getTipoDisparoSeleccionado() const;
    short getTipoProyectilSeleccionado() const;
    bool estaEnModoPreventivo() const;
};

#endif // RAZONAMIENTO_H
