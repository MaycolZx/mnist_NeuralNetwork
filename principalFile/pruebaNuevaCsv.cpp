#pragma once
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <vector>
using namespace std;

vector<vector<float>> vamosAcrearVector(int indexV) {
    vector<vector<float>> inputVector;
    std::ifstream archivo("E:\\DOWNLOAD\\mnist.csv");
    std::string linea;

    // while (std::getline(archivo, linea)) {
    std::getline(archivo, linea);
    std::vector<float> numeros;
    std::string numero_str;
    for (char caracter : linea) {
        if (caracter != ',') {
            numero_str += caracter;
        }
        else {
            numeros.push_back(std::stoi(numero_str));
            numero_str = "";
        }
    }
    numeros.push_back(std::stoi(numero_str));
    // for (int numero : numeros) {
    //   std::cout << numero << " ";
    // }
    // std::cout << std::endl;
    for (int numero : numeros) {
        // std::cout << numero << " ";
        vector<float> valoresIngresoM;
        valoresIngresoM.push_back(numero);
        inputVector.push_back(valoresIngresoM);
    }
    std::cout << std::endl;

    archivo.close();
    return inputVector;
}

vector<vector<float>> vectoresRandomPesos(int limitNeurons = 10,
    int precision = 2) {
    vector<vector<float>> pesosRandom;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int j = 0; j < limitNeurons; j++) {
        vector<float> pesosVector;
        for (int i = 0; i < 784; i++) {
            float numero_aleatorio = dis(gen) * 100.0f / 100.0f;
            pesosVector.push_back(numero_aleatorio);
        }
        pesosRandom.push_back(pesosVector);
    }
    // Que pesos tiene :Print()
      //for (int i = 0; i < 10; i++) {
      //  for (int j = 0; j < 15; j++) {
      //    cout << std::fixed << std::setprecision(2) << pesosRandom[i][j] << "";
      //  }
      //  cout << endl;
      //}
    return pesosRandom;
}

float sigmoide(float x) { return 1.0f / (1.0f + std::exp(-x)); }

//bool reLU(int valor) { return valor > 0; }

float reLU(float x) {
    return (x > 0) ? x : 0;
}

float precisionEntrenamiento(float numeroCorrecto, float numeroTotal) {
    float precisionE = numeroCorrecto / numeroTotal;
    return precisionE;
}

vector<int> recalculandoPesos(const vector<vector<float>>& matxPesos, const vector<vector<float>>& inputN,const vector<vector<float>>& resulFunct) {
// Peso = peso + n(t-o)*xi 
    int valorTivo = inputN[0][0];
    float tazaAp = 0.5;
    vector <int> indexSearch = {};
    for (int i = 0; i < resulFunct.size(); i++) {
        float valActivation = reLU(resulFunct[i][0]);
        cout << "#" << i << "-valor de Act: " << valActivation << endl;
        if ((valorTivo == i && valActivation == 0) || (valActivation == 1 && i != valorTivo)) {
            indexSearch.push_back(i);
        }
    }
    if (!indexSearch.empty()) {
        for (int i = 0; i < indexSearch.size(); i++) {
            float valActivation = reLU(resulFunct[i][0]);
            vector<float> valorPesosIndex = matxPesos[i];
            for (int k = 0; k < valorPesosIndex.size(); k++) {
                valorPesosIndex[k] = valorPesosIndex[k] + (tazaAp * (0 - valActivation) * inputN[k + 1][0]);
            }
        }
    }
    return indexSearch;
}

// Función para multiplicar dos matrices representadas como vectores de vectores
std::vector<std::vector<float>>
multiplicarMatrices(const std::vector<std::vector<float>>& matriz1,
    const std::vector<std::vector<float>>& matriz2) {
    float biasV = 1;
    int filas_matriz1 = matriz1.size();
    int columnas_matriz1 = matriz1[0].size();
    int filas_matriz2 = matriz2.size() - 1;
    int columnas_matriz2 = matriz2[0].size();
    cout << "Matriz 01 es : " << filas_matriz1 << " x " << columnas_matriz1
        << endl;
    cout << "Matriz 02 es: " << filas_matriz2 << " x " << columnas_matriz2
        << endl;

    // Verificar que las matrices sean multiplicables
    if (columnas_matriz1 != filas_matriz2) {
        std::cerr << "Error: Las matrices no son compatibles para multiplicación."
            << std::endl;
        return std::vector<std::vector<float>>(); // Devolver matriz vacía en caso
        // de error
    }

    // Crear la matriz resultado inicializada con ceros
    std::vector<std::vector<float>> resultado(
        filas_matriz1, std::vector<float>(columnas_matriz2, 0.0f));
    float opResult = 0.0f;

    int epocIndex = 0;
    while (true) {
        // Realizar la multiplicación de matrices
        cout << "Epoca-#"  << epocIndex << endl;
        for (int i = 0; i < filas_matriz1; ++i) {
            for (int j = 0; j < columnas_matriz2; ++j) {
                for (int k = 1; k < columnas_matriz1; ++k) {
                    resultado[i][j] += matriz1[i][k] * matriz2[k][j];
                }
                resultado[i][j] += biasV;
                cout << "Un resultado es: " << resultado[i][j] << endl;
            }
            // resultado[i].push_back();
        }
        vector<int> rCond = recalculandoPesos(matriz1, matriz2, resultado);
        if (rCond.empty()) {
            break;
        }
        epocIndex++;
    }
    
    return resultado;
}

// Función para sumar dos matrices representadas como vectores de vectores
// std::vector<std::vector<float>>
// sumarMatrices(const std::vector<std::vector<float>> &matriz1,
//               const std::vector<std::vector<float>> &matriz2) {
//   int filas = matriz1.size();
//   int columnas = matriz1[0].size();
//
//   // Verificar que las matrices tengan las mismas dimensiones
//   if (filas != matriz2.size() || columnas != matriz2[0].size()) {
//     std::cerr << "Error: Las matrices tienen dimensiones diferentes."
//               << std::endl;
//     return std::vector<std::vector<float>>(); // Devolver matriz vacía en
//     caso
//                                               // de error
//   }
//
//   // Crear la matriz resultado inicializada con ceros
//   std::vector<std::vector<float>> resultado(filas,
//                                             std::vector<float>(columnas,
//                                             0.0f));
//
//   // Realizar la suma de matrices
//   for (int i = 0; i < filas; ++i) {
//     for (int j = 0; j < columnas; ++j) {
//       resultado[i][j] = matriz1[i][j] + matriz2[i][j];
//     }
//   }
//
//   return resultado;
// }

float costDif(int valorDeseado) {
    float wave02[10] = {};
    float resultadoCost = 0;
    for (int i = 0; i < 10; i++) {
        if (i == valorDeseado) {
            resultadoCost += pow(wave02[i] - 1, 2);
            continue;
        }
        resultadoCost += wave02[i];
    }
    return resultadoCost;
}

int main() {
    vector<vector<float>> valoresRpesos = vectoresRandomPesos();
    float functionZ[10] = {};
    vector<vector<float>> numerosInput;
    int indexCsv = 0;
    numerosInput = vamosAcrearVector(indexCsv);
    cout << "El tamano del vector es: " << numerosInput.size() << endl;

    std::vector<std::vector<float>> resultado =
        multiplicarMatrices(valoresRpesos, numerosInput);
    return 0;
}

// otherFunction
// std::vector<std::vector<float>>
// multiplicarMatrices(const std::vector<std::vector<float>> &matriz1,
//                     const std::vector<std::vector<float>> &matriz2) {
//   float biasV = 1;
//   int filas_matriz1 = matriz1.size();
//   int columnas_matriz1 = matriz1[0].size();
//   int filas_matriz2 = matriz2.size() - 1;
//   int columnas_matriz2 = matriz2[0].size();
//   cout << "Matriz 01 es : " << filas_matriz1 << " x " << columnas_matriz1
//        << endl;
//   cout << "Matriz 02 es: " << filas_matriz2 << " x " << columnas_matriz2
//        << endl;
//
//   // Verificar que las matrices sean multiplicables
//   if (columnas_matriz1 != filas_matriz2) {
//     std::cerr << "Error: Las matrices no son compatibles para
//     multiplicación."
//               << std::endl;
//     return std::vector<std::vector<float>>(); // Devolver matriz vacía en
//     caso
//                                               // de error
//   }
//
//   // Crear la matriz resultado inicializada con ceros
//   std::vector<std::vector<float>> resultado(
//       filas_matriz1, std::vector<float>(columnas_matriz2, 0.0f));
//   float opResult = 0.0f;
//   // std::vector<std::vector<float>> resultadoTMP;
//   std::vector<std::vector<double>> resultadoTMP(
//       filas_matriz1, std::vector<double>(columnas_matriz2, 0.0));
//
//   // Realizar la multiplicación de matrices
//   for (int i = 0; i < filas_matriz1; ++i) {
//     for (int j = 0; j < columnas_matriz2; ++j) {
//       opResult = 0.0f;
//       double temp = 0.0f;
//       for (int k = 0; k < columnas_matriz1; ++k) {
//         // resultado[i][j] += matriz1[i][k] * matriz2[k][j + 1];
//         temp = matriz1[i][k] * matriz2[k][j + 1];
//         opResult += temp;
//       }
//       // resultado[i][j] += biasV;
//       cout << "Un resultado es: " << resultado[i][j] << endl;
//       cout << "Un es: " << opResult << endl;
//       // vector<float> vectAdd = {opResult};
//       // resultadoTMP.push_back(vectAdd);
//       resultadoTMP[i][j] = opResult;
//     }
//     // resultado[i].push_back();
//   }
//
//   for (int i = 0; i < resultado.size(); i++) {
//     for (int j = 0; j < resultado[i].size(); j++) {
//       // cout << resultado[i][j] << endl;
//       cout << fixed << setprecision(8) << resultadoTMP[i][j] << endl;
//     }
//   }
//
//   return resultado;
// }
