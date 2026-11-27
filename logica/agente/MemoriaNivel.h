#ifndef MEMORIANIVEL_H
#define MEMORIANIVEL_H

/**
 * @brief Memoria acumulativa persistente del agente inteligente entre oleadas.
 * Almacena aciertos y fallos en arreglos dinámicos crudos de tamaño 3x4 = 12.
 * Índice = tipoDisparo * 4 + estadoKirby.
 */
class MemoriaNivel {
private:
    short* aciertos;
    short* fallos;
    short fallosPorSalto;
    bool tendenciaEvasion;

    int calcularIndice(short tipoDisparo, short estadoKirby) const;

public:
    MemoriaNivel();
    ~MemoriaNivel();

    // Se prohíbe la copia para garantizar la propiedad exclusiva de los arreglos dinámicos
    MemoriaNivel(const MemoriaNivel&) = delete;
    MemoriaNivel& operator=(const MemoriaNivel&) = delete;

    void registrarAcierto(short tipoDisparo, short estadoKirby);
    void registrarFallo(short tipoDisparo, short estadoKirby);

    short getAciertos(short tipoDisparo, short estadoKirby) const;
    short getFallos(short tipoDisparo, short estadoKirby) const;

    void incrementarFallosSalto();
    short getFallosPorSalto() const;
    bool hayTendenciaEvasion() const;
    void activarTendenciaEvasion(bool activar);
    void reiniciar();
};

#endif // MEMORIANIVEL_H
