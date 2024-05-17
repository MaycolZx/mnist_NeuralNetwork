#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int numeroValidA = 0;

// Función para escribir un vector<vector<float>> en un archivo CSV
void escribirCSV(const vector<vector<float>> &datos,
                 const string &nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (archivo.is_open()) {
    for (const auto &fila : datos) {
      for (size_t i = 0; i < fila.size(); ++i) {
        archivo << fila[i];
        if (i != fila.size() - 1)
          archivo << ",";
      }
      archivo << endl;
    }
    archivo.close();
    cout << "Datos guardados en " << nombreArchivo << endl;
  } else {
    cout << "No se pudo abrir el archivo " << nombreArchivo
         << " para escritura." << endl;
  }
}

// Función para leer valores flotantes desde un archivo CSV
vector<vector<float>> leerCSV(const string &nombreArchivo) {
  vector<vector<float>> datos;
  ifstream archivo(nombreArchivo);
  if (archivo.is_open()) {
    string linea;
    while (getline(archivo, linea)) {
      stringstream ss(linea);
      vector<float> fila;
      string valor;
      while (getline(ss, valor, ',')) {
        fila.push_back(stof(valor));
      }
      datos.push_back(fila);
    }
    archivo.close();
    // cout << "Datos leídos desde " << nombreArchivo << endl;
  } else {
    cout << "No se pudo abrir el archivo " << nombreArchivo << " para lectura."
         << endl;
  }
  return datos;
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
  return pesosRandom;
}

float sigmoide(float x) { return 1.0f / (1.0f + std::exp(-x)); }

// bool reLU(int valor) { return valor > 0; }
// float reLU(float x) { return (x > 0) ? x : 0; }
float reLU(float x) {
  if (x > 14000) {
    return 1;
  } else {
    return 0;
  }
}

float precisionEntrenamiento(float numeroCorrecto, float numeroTotal) {
  float precisionE = numeroCorrecto / numeroTotal;
  return precisionE;
}

vector<int> recalculandoPesos(vector<vector<float>> &matxPesos,
                              vector<vector<float>> &inputN,
                              vector<vector<float>> &resulFunct) {
  // Peso = peso + n(t-o)*xi
  int valorTivo = inputN[0][0];
  cout << "Valor objetivo: " << valorTivo << endl;
  float tazaAp = 0.5;
  vector<int> indexSearch = {};
  // cout << "Tamano index: " << indexSearch.size() << endl;
  for (int i = 0; i < resulFunct.size(); i++) {
    float valActivation = reLU(resulFunct[i][0]);
    cout << "#" << i << "-valor de Act: " << valActivation << endl;
    // if ((valorTivo == i && valActivation == 0) ||
    //     (valActivation == 1 && i != valorTivo)) {
    //   indexSearch.push_back(i);
    // }
    if (valorTivo == i && valActivation == 0) {
      indexSearch.push_back(i);
    }
    if (valActivation == 1 && i != valorTivo) {
      indexSearch.push_back(i);
    }
  }
  // cout << "Tamano index-Segundo: " << indexSearch.size() << endl;
  // system("clear");
  // int valorWaobt = 0;
  // if (!indexSearch.empty()) {
  // for (int i = 0; i < indexSearch.size(); i++) {
  //   cout << "Valor del index: " << indexSearch[i] << endl;
  //   if (indexSearch[i] == valorTivo) {
  //     valorWaobt = 1;
  //   } else {
  //     valorWaobt = 0;
  //   }
  //   float valActivation = reLU(resulFunct[indexSearch[i]][0]);
  //   for (int k = 0; k < matxPesos[i].size(); k++) {
  //     matxPesos[indexSearch[i]][k] =
  //         matxPesos[indexSearch[i]][k] +
  //         (tazaAp * (valorWaobt - valActivation) * inputN[k + 1][0]);
  //   }
  // }
  // }
  return indexSearch;
}

// Función para multiplicar dos matrices representadas como vectores de vectores
int multiplicarMatrices(std::vector<std::vector<float>> &matriz1,
                        std::vector<std::vector<float>> &matriz2) {
  float biasV = 1;
  int filas_matriz1 = matriz1.size();
  int columnas_matriz1 = matriz1[0].size();
  int filas_matriz2 = matriz2.size() - 1;
  int columnas_matriz2 = matriz2[0].size();
  cout << "Matriz 01 es : " << filas_matriz1 << " x " << columnas_matriz1
       << endl;
  cout << "Matriz 02 es: " << filas_matriz2 << " x " << columnas_matriz2
       << endl;

  if (columnas_matriz1 != filas_matriz2) {
    std::cerr << "Error: Las matrices no son compatibles para multiplicación."
              << std::endl;
    // return std::vector<std::vector<float>>();
    return 0;
  }

  // Crear la matriz resultado inicializada con ceros
  float opResult = 0.0f;

  int epocIndex = 0;
  std::vector<std::vector<float>> resultado(
      filas_matriz1, std::vector<float>(columnas_matriz2, 0.0f));

  // while (true) {
  // Realizar la multiplicación de matrices
  for (int i = 0; i < filas_matriz1; ++i) {
    for (int j = 0; j < columnas_matriz2; ++j) {
      resultado[i][j] = 0.0f;
    }
  }

  for (int i = 0; i < filas_matriz1; ++i) {
    for (int j = 0; j < columnas_matriz2; ++j) {
      for (int k = 0; k < columnas_matriz1; ++k) {
        resultado[i][j] += matriz1[i][k] * matriz2[k + 1][j];
      }
      resultado[i][j] += biasV;
      // cout << "Un resultado es: " << resultado[i][j] << endl;
      // cout << "#-" << i << " " << fixed << setprecision(8) <<
      // resultado[i][j]
      //      << endl;
    }
  }
  vector<int> rCond = recalculandoPesos(matriz1, matriz2, resultado);
  if (rCond.size() == 0) {
    numeroValidA++;
    // break;
  }
  // epocIndex++;
  // }

  // string nombreArchivo = "datosPesos.csv";
  // escribirCSV(matriz1, nombreArchivo);
  // vector<vector<float>> datosLeidos = leerCSV(nombreArchivo);
  // Imprimir los datos leídos
  // for (const auto &fila : datosLeidos) {
  //   for (const auto &valor : fila) {
  //     cout << valor << " ";
  //   }
  //   cout << endl;
  // }
  return 1;
}

void vamosAcrearVector() {
  // std::ifstream archivo("E:\\DOWNLOAD\\mnist.csv");//Descomentar de estas en
  // window y cambiar de direccion
  // vector<vector<float>> valoresRpesos = vectoresRandomPesos();
  vector<vector<float>> valoresRpesos = leerCSV("./datosPesos.csv");

  // Imprimir los datos leídos
  // for (const auto &fila : datosLeidos) {
  //   for (const auto &valor : fila) {
  //     cout << valor << " ";
  //   }
  //   cout << endl;
  // }

  std::ifstream archivo("./mnist_test.csv");
  std::string linea;

  int contadorTMP = 0;
  while (std::getline(archivo, linea)) {
    // std::getline(archivo, linea);
    cout << "Data-#" << contadorTMP << " del CSV" << endl;
    vector<vector<float>> inputVector;
    vector<float> numeros;
    string numero_str;
    for (char caracter : linea) {
      if (caracter != ',') {
        numero_str += caracter;
      } else {
        numeros.push_back(std::stoi(numero_str));
        numero_str = "";
      }
    }
    numeros.push_back(std::stoi(numero_str));
    for (int numero : numeros) {
      vector<float> valoresIngresoM;
      valoresIngresoM.push_back(numero);
      inputVector.push_back(valoresIngresoM);
    }
    // for (int i = 0; i < inputVector.size(); i++) {
    //   for (int j = 0; j < inputVector[i].size(); j++) {
    //     cout << inputVector[i][j] << " ";
    //   }
    // }
    // cout << endl << "Este es el limite del primero " << endl;
    //
    cout << "El tamano del vector es: " << inputVector.size() << endl;
    multiplicarMatrices(valoresRpesos, inputVector);
    contadorTMP++;
    // if (contadorTMP == 3) {
    //   break;
    // }
  }

  float valPr = precisionEntrenamiento(numeroValidA, 10000.0f);
  cout << "La precision del entrenamiento es de: " << valPr << endl;
  archivo.close();
}

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

void agregarNumeroCSV(const std::string &nombreArchivo, float numero) {
  // Abrir el archivo en modo de añadir (append)
  std::ofstream archivo(nombreArchivo, std::ios::app);

  // Comprobar si el archivo se abrió correctamente
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo " << nombreArchivo << std::endl;
    return;
  }

  // Escribir el número en el archivo seguido de una nueva línea
  archivo << numero << std::endl;

  // Cerrar el archivo
  archivo.close();
}

void algunaF() {
  std::string nombreArchivo = "numeros.csv";
  float numero = 3.14159f;

  agregarNumeroCSV(nombreArchivo, numero);
}
class codeTest {
public:
  // codeTest();
  // ~codeTest();
  vector<vector<float>> getPesos();
  vector<vector<float>> selectIndexDC(int indexS);
  // void tazaDeAcertividad() { vamosAcrearVector(); }// No descomentar solo
  // para test

private:
  // Funciones de Debug
  void printPesos();
  vector<vector<float>> valoresRpesos = leerCSV("./datosPesos.csv");
};

// codeTest::codeTest() {}

// codeTest::~codeTest() {}

vector<vector<float>> codeTest::getPesos() { return valoresRpesos; }
vector<vector<float>> codeTest::selectIndexDC(int indexS) {
  std::ifstream archivo("./mnist_test.csv");
  std::string linea;
  vector<vector<float>> inputVector;
  int contadorTMP = 0;
  while (std::getline(archivo, linea)) {
    // std::getline(archivo, linea);
    // cout << "Data-#" << contadorTMP << " del CSV" << endl;
    inputVector.clear();
    vector<float> numeros;
    string numero_str;
    for (char caracter : linea) {
      if (caracter != ',') {
        numero_str += caracter;
      } else {
        numeros.push_back(std::stoi(numero_str));
        numero_str = "";
      }
    }
    numeros.push_back(std::stoi(numero_str));
    for (int numero : numeros) {
      vector<float> valoresIngresoM;
      valoresIngresoM.push_back(numero);
      inputVector.push_back(valoresIngresoM);
    }
    // for (int i = 0; i < inputVector.size(); i++) {
    //   for (int j = 0; j < inputVector[i].size(); j++) {
    //     cout << inputVector[i][j] << " ";
    //   }
    // }
    // cout << endl << "Este es el limite del primero " << endl;
    //
    // cout << "El tamano del vector es: " << inputVector.size() << endl;
    if (contadorTMP == indexS) {
      break;
    }
    contadorTMP++;
  }
  archivo.close();
  multiplicarMatrices(valoresRpesos, inputVector);
  // float valPr = precisionEntrenamiento(numeroValidA, 10000.0f);
  // cout << "La precision del entrenamiento es de: " << valPr << endl;
  return inputVector;
}

void codeTest::printPesos() {
  for (const auto &fila : valoresRpesos) {
    for (const auto &valor : fila) {
      cout << valor << " ";
    }
    cout << endl;
  }
}
