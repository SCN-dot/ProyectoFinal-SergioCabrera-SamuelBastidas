#ifndef MEMORIANIVEL_H
#define MEMORIANIVEL_H

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

#endif
