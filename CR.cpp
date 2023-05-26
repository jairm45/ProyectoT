#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

struct corredor {
    char nombre[20];
    int camisa;
    float tiempo ;
    int recor;
    int promedio;
    int total;
    int altura;
    corredor* derecha;
    corredor* izquierdo;
};

corredor* Raiz = NULL; // Puntero a la raiz del arbol
corredor* aux = NULL; // Puntero auxiliar para insertar un nuevo corredor
corredor* aux1 = NULL; // Puntero auxiliar para insertar un nuevo corredor


//obtiener la altura de un nodo en el arbol
int obtenerAltura(corredor* nodo) {
    if (nodo == NULL) {
        return -1;
    } else {
        int alturaIzq = obtenerAltura(nodo->izquierdo);
        int alturaDer = obtenerAltura(nodo->derecha);
        return 1 + max(alturaIzq, alturaDer);
    }
}

void actualizarAltura(corredor* nodo) {
    nodo->altura = obtenerAltura(nodo);
}

// esto es para la rotacion para balancear el arbol, esta en mood humilde
corredor* rotacionSimpleIzquierda(corredor* nodo) {
    corredor* aux = nodo->izquierdo;
    nodo->izquierdo = aux->derecha;
    aux->derecha = nodo;
    actualizarAltura(nodo);
    actualizarAltura(aux);
    return aux;
}

corredor* rotacionSimpleDerecha(corredor* nodo) {
    corredor* aux = nodo->derecha;
    nodo->derecha = aux->izquierdo;
    aux->izquierdo = nodo;
    actualizarAltura(nodo);
    actualizarAltura(aux);
    return aux;
}

corredor* rotacionDobleIzquierda(corredor* nodo) {
    nodo->izquierdo = rotacionSimpleDerecha(nodo->izquierdo);
    return rotacionSimpleIzquierda(nodo);
}

corredor* rotacionDobleDerecha(corredor* nodo) {
    nodo->derecha = rotacionSimpleIzquierda(nodo->derecha);
    return rotacionSimpleDerecha(nodo);
}

corredor* balancearNodo(corredor* nodo) {
    if (nodo == NULL) {
        return NULL;
    }

    actualizarAltura(nodo);

    int balance = obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecha);

    if (balance > 1) {
        if (obtenerAltura(nodo->izquierdo->izquierdo) >= obtenerAltura(nodo->izquierdo->derecha)) {
            return rotacionSimpleIzquierda(nodo);
        } else {
            return rotacionDobleIzquierda(nodo);
        }
    } else if (balance < -1) {
        if (obtenerAltura(nodo->derecha->derecha) >= obtenerAltura(nodo->derecha->izquierdo)) {
            return rotacionSimpleDerecha(nodo);
        } else {
            return rotacionDobleDerecha(nodo);
        }
    }

    return nodo;
}

void insertarAtleta(corredor* nodo, corredor* nuevoCorredor) {
    if (nuevoCorredor->camisa < nodo->camisa) {
        if (nodo->izquierdo == NULL) {
            nodo->izquierdo = nuevoCorredor;
        } else {
            insertarAtleta(nodo->izquierdo, nuevoCorredor);
        }
    } else if (nuevoCorredor->camisa > nodo->camisa) {
        if (nodo->derecha == NULL) {
            nodo->derecha = nuevoCorredor;
        } else {
            insertarAtleta(nodo->derecha, nuevoCorredor);
        }
    }

    nodo = balancearNodo(nodo);
}

int preorden(corredor* aux2) {
    cout << "Numero de camisa: " << aux2->camisa << " "
         << "Nombre del Corredor: " << aux2->nombre << " "
         << "Tiempo: " << aux2->tiempo << endl;

    if (aux2->izquierdo != NULL) {
        preorden(aux2->izquierdo);
    }
    if (aux2->derecha != NULL) {
        preorden(aux2->derecha);
    }
    return 0;
}

int Registrart(corredor* nodo) {
    int camisa;
    bool encontrado = false;

    cout << "Registrar el numero del corredor: ";
    cin >> camisa;
    cout << "\n";

    corredor* encontradoNodo = NULL;
    corredor* actual = nodo;

    while (actual != NULL) {
        if (actual->camisa == camisa) {
            encontrado = true;
            actual->recor++;

            cout << "Nombre del Corredor: " << actual->nombre << endl;
            cout << "Tiempo incluido: " << actual->tiempo << endl;
            cout << "Ultima vuelta: " << actual->recor << endl;
            cout << "\n";
            cout << "Registre el tiempo de la ultima vuelta:" << endl;
            cin >> actual->tiempo;
            actual->total += actual->tiempo;
            actual->promedio = actual->total / actual->recor;

            break;
        } else if (camisa < actual->camisa) {
            actual = actual->izquierdo;
        } else {
            actual = actual->derecha;
        }
    }

    if (!encontrado) {
        cout << "No esta el corredor en la competencia" << endl;
    }

    return 0;
}

int Posicionar() {
    if (aux->camisa < aux1->camisa) {
        if (aux1->izquierdo != NULL) {
            aux1 = aux1->izquierdo;
            Posicionar();
        } else {
            aux1->izquierdo = aux;
        }
    } else if (aux->camisa > aux1->camisa) {
        if (aux1->derecha != NULL) {
            aux1 = aux1->derecha;
            Posicionar();
        } else {
            aux1->derecha = aux;
        }
    }

    Raiz = balancearNodo(Raiz);  // Balancear el arbol después de la insercion

    return 0;
}

int Registro() {
    aux = (struct corredor*)malloc(sizeof(struct corredor));
    cout << "Ingrese el nombre del corredor" << endl;
    cin >> aux->nombre;
    cout << "Ingresar el numero del corredor: " << endl;
    cin >> aux->camisa;
    aux->derecha = NULL;
    aux->izquierdo = NULL;

    if (Raiz == NULL) {
        Raiz = aux;
        aux = NULL;
        free(aux);
    } else {
        aux1 = Raiz;
        Posicionar();
    }
    return 0;
}

// para calcular el promedio en el arbol 
void calcularPromedio(corredor* nodo) {
    if (nodo != NULL) {
        calcularPromedio(nodo->izquierdo);

        if (nodo->recor > 0) {
            nodo->promedio = nodo->total / nodo->recor;
        }

        calcularPromedio(nodo->derecha);
    }
}

void preordenI(corredor* nodo) {
    if (nodo != NULL) {
        preorden(nodo->izquierdo);

        cout << "Numero de camisa: " << nodo->camisa << ", "
             << "Nombre del corredor: " << nodo->nombre << ", "
             << "Promedio: " << nodo->promedio << endl;

        preorden(nodo->derecha);
    }
}


int main() {
    int datos = 0;
    do {
        cout << "===BIENVENIDO===" << endl;
        cout << "1. Registrar Corredor" << endl;
        cout << "2. Registrar tiempo" << endl;
        cout << "3. Mostrar Corredores" << endl;
        cout << "4. Promedio de los corredores" << endl;
        cout << "5. Abandonar el programa" << endl;
        cin >> datos;

        switch (datos) {
            case 1:
                Registro();
                break;
            case 2:
                Registrart(Raiz);
                break;
            case 3:
                preorden(Raiz);
                break;
                case 4:
                calcularPromedio(Raiz);
                cout << "Se han calculado los promedios de los corredores" << endl;
                cout << "Mostrando promedios en orden ascendente:" << endl;
                preordenI(Raiz);
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    } while (datos != 5);

    return 0;
}