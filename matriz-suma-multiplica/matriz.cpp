#include <iostream>
#include <fstream>

#define TAM_MATRIZ 20
#define TAM_ARR 2

#define ARCHIVO "matrices.txt"

using namespace std;

typedef struct{
    int datos[TAM_ARR][TAM_ARR];
} Matriz;

void mostrarMenu()
{
    cout << "------------------------------" << endl;
    cout << " Menu " << endl;
    cout << "------------------------------" << endl;
    cout << "1. Agregar matriz." << endl;
    cout << "2. Mostrar todas las matrices." << endl;
    cout << "3. Modificar matriz." << endl;
    cout << "4. Buscar matriz." << endl;
    cout << "5. Borrar matriz." << endl;
    cout << "6. Sumar matrices." << endl;
    cout << "7. Multiplicar matrices." << endl;
    cout << "8. Salir." << endl;
}

int seleccionarOpcion()
{
    int opt;
    cout << "Selecionar opcion: ";
    cin >> opt;

    return opt;
}

void guardarMatriz(std::ofstream &escribirArchivo, Matriz matriz)
{
    escribirArchivo << 2 << "\n";
    escribirArchivo << matriz.datos[1][0] << " " << matriz.datos[1][1] << "\n";
    escribirArchivo << matriz.datos[0][0] << " " << matriz.datos[0][1] << "\n";
}

void mostrarMatriz(Matriz matriz)
{
    for (int i = 0; i < TAM_ARR; i++)
    {
        cout << "| ";
        for (int j = 0; j < TAM_ARR; j++)
        {
            cout << matriz.datos[i][j] << " | ";
        }
        cout << endl;
        cout << "----+----" << endl;
    }
    cout << endl;
}

Matriz crearMatriz()
{
    Matriz matriz;
    cout << "ingresa valores para la matriz." << endl;
    cout << "Fila 1: ";    cin >> matriz.datos[0][0] >> matriz.datos[0][1];
    cout << "Fila 2: "; cin >> matriz.datos[1][0] >> matriz.datos[1][1];

    return matriz;
}

int agregarMatriz(Matriz matrices[], int size)
{
    Matriz matriz;
    matriz = crearMatriz();
    matrices[size++] = matriz;

    return size;
}

void mostrarMatrices(Matriz matrices[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "[ matriz: " << i + 1 << " ]" << endl;
        mostrarMatriz(matrices[i]);
    }
}

int cargarMatrices(Matriz matrices[])
{
    int tam_arr, size = 0, dato;
    // Abrimos archivo matriz.txt
    ifstream archivoCargado(ARCHIVO);

    while (archivoCargado >> tam_arr)
    {
        Matriz matriz;
        for (int i = 0; i < TAM_ARR; i++)
        {
            for(int j = 0; j < TAM_ARR; j++)
            {
                archivoCargado >> dato;
                matriz.datos[i][j] = dato;
            }
        }
        matrices[size++] = matriz;
    }

    archivoCargado.close();

    return size;
}

void guardarMatrices(Matriz matrices[], int size)
{
    ofstream escribirArchivo(ARCHIVO, std::ios::out);
    for (int i = 0; i < size; i++)
    {
        guardarMatriz(escribirArchivo, matrices[i]);
    }
    escribirArchivo.close();
}

void buscarMatriz(Matriz matrices[], int size)
{
    Matriz matriz;
    matriz = crearMatriz();

    for (int i = 0; i < size; i++)
    {
        if ( matrices[i].datos[0][0] == matriz.datos[0][0] &&
             matrices[i].datos[0][1] == matriz.datos[0][1] &&
             matrices[i].datos[1][0] == matriz.datos[1][0] &&
             matrices[i].datos[1][1] == matriz.datos[1][1] )
        {
            cout << "La matriz se encuentra en la posición: " << i+1 << endl;
            return;
        }
    }
    cout << "No se encontró la matriz." << endl;
}

void modificarMatriz(Matriz matrices[], int size)
{
    int indice;
    Matriz matriz;

    mostrarMatrices(matrices, size);

    cout << "Seleccione el indice de la matriz a editar." << endl;
    cout << "indice: "; cin >> indice;

    matriz = crearMatriz();
    matrices[indice - 1] = matriz;
}

int eliminarMatriz(Matriz matrices[], int size)
{
    int indice = 0;
    mostrarMatrices(matrices, size);

    cout << "Ingresa el indice de la matriz a borrar: "; cin >> indice;

    for (int i = indice - 1; i < size; i++)
    {
        matrices[i] = matrices[i + 1];
    }

    return size - 1;
}

void sumarMatrices(Matriz A, Matriz B)
{
    Matriz matriz;

    matriz.datos[0][0]  = A.datos[0][0] + B.datos[0][0];
    matriz.datos[0][1]  = A.datos[0][1] + B.datos[0][1];
    matriz.datos[1][0]  = A.datos[1][0] + B.datos[1][0];
    matriz.datos[1][1]  = A.datos[1][1] + B.datos[1][1];

    cout << "La suma de las matrices es: " << endl;
    mostrarMatriz(matriz);
}

void multiplicarMatrices(Matriz A, Matriz B)
{
    Matriz matriz;

    matriz.datos[0][0]  = A.datos[0][0] * B.datos[0][0];
    matriz.datos[0][1]  = A.datos[0][1] * B.datos[0][1];
    matriz.datos[1][0]  = A.datos[1][0] * B.datos[1][0];
    matriz.datos[1][1]  = A.datos[1][1] * B.datos[1][1];

    cout << "El producto de las matrices es: " << endl;
    mostrarMatriz(matriz);
}

int main()
{
    int opcion = 0;
    int size = 0;
    Matriz matrices[TAM_MATRIZ];

    size = cargarMatrices(matrices);

    int indice_a, indice_b;
    do{
        mostrarMenu();
        opcion = seleccionarOpcion();

        switch(opcion)
        {
            case 1:
                size = agregarMatriz(matrices, size);
                guardarMatrices(matrices, size);
                break;
            case 2:
                mostrarMatrices(matrices, size);
                break;
            case 3:
                modificarMatriz(matrices, size);
                guardarMatrices(matrices,size);
                break;
            case 4:
                buscarMatriz(matrices, size);
                break;
            case 5:
                size = eliminarMatriz(matrices, size);
                guardarMatrices(matrices, size);
                break;
            case 6:
                mostrarMatrices(matrices, size);
                cout << "Indice primera matriz: "; cin >> indice_a;
                cout << "indice segunda matriz: "; cin >> indice_b;
                sumarMatrices(matrices[indice_a - 1], matrices[indice_b - 1]);
                break;
            case 7:
                mostrarMatrices(matrices, size);
                cout << "Indice primera matriz: "; cin >> indice_a;
                cout << "indice segunda matriz: "; cin >> indice_b;
                multiplicarMatrices(matrices[indice_a - 1], matrices[indice_b - 1]);
                break;
        }

    }while(opcion >= 1 && opcion < 8);

    return 0;
}
