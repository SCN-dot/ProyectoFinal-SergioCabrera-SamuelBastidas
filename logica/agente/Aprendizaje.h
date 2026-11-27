#ifndef APRENDIZAJE_H
#define APRENDIZAJE_H

class Percepcion;
class MemoriaNivel;
class Razonamiento;

/**
 * @brief Fase 4 del Agente Inteligente: Aprendizaje.
 * Evalúa si el último disparo acertó o falló, actualiza MemoriaNivel
 * y adapta los parámetros de Razonamiento al superar el umbral de fallos.
 */
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

#endif // APRENDIZAJE_H
