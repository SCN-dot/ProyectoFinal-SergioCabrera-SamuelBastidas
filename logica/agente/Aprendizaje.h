#ifndef APRENDIZAJE_H
#define APRENDIZAJE_H

class Percepcion;
class MemoriaNivel;
class Razonamiento;

class Aprendizaje {
private:
    short umbralFallos;

public:
    explicit Aprendizaje(short umbralFallos = 4);

    void evaluarYRegistrar(const Percepcion& percepcion,
                           short tipoDisparo,
                           short estadoObjetivo,
                           MemoriaNivel* memoria,
                           Razonamiento* razonamiento);

    void adaptar(Razonamiento* razonamiento);
    void setUmbralFallos(short umbral);
    short getUmbralFallos() const;
};

#endif
