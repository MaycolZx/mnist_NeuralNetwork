#include "./codeTest.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <atomic>
#include <cmath>
#include <iostream>
#include <iterator>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

float boardClean[784] = {};

float mnist_data[] = {
    5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   3,   18,  18,  18,  126, 136, 175, 26,  166, 255, 247, 127,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  36,  94,
    154, 170, 253, 253, 253, 253, 253, 225, 172, 253, 242, 195, 64,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   49,  238, 253, 253, 253, 253,
    253, 253, 253, 253, 251, 93,  82,  82,  56,  39,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   18,  219, 253, 253, 253, 253, 253, 198,
    182, 247, 241, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   80,  156, 107, 253, 253, 205, 11,  0,   43,
    154, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   14,  1,   154, 253, 90,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   139, 253, 190, 2,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   11,  190, 253, 70,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   35,  241, 225, 160, 108, 1,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   81,  240, 253, 253, 119, 25,  0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    45,  186, 253, 253, 150, 27,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   16,
    93,  252, 253, 187, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   249,
    253, 249, 64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   46,  130, 183, 253, 253, 207,
    2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   39,  148, 229, 253, 253, 253, 250, 182, 0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   24,  114, 221, 253, 253, 253, 253, 201, 78,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   23,  66,  213,
    253, 253, 253, 253, 198, 81,  2,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   18,  171, 219, 253, 253, 253, 253,
    195, 80,  9,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   55,  172, 226, 253, 253, 253, 253, 244, 133, 11,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   136, 253, 253, 253, 212, 135, 132, 16,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0};

#define widthS 500
#define higthS 500

int opcionS = 0;
int indexSearchN = 0;
vector<vector<float>> vectA;

std::atomic<bool> running(true);
std::mutex mtx;

void selectOpt(int &opcionSelect, int &index, std::mutex &mtx) {
  // int opcionS = 0;
  codeTest valoresC;
  cout << "Ingrese una opcion:\n1. Seleccion data 10k de prueba.\n2. Dibujar a "
          "mano.\n*). Salir"
       << endl;
  while (true) {
    int valorOpcion;

    cout << "La opcion es: ";
    cin >> valorOpcion;
    opcionSelect = valorOpcion;
    if (valorOpcion == 1) {
      int algunValor;
      while (true) {
        cout << "Digite un numero entre 1 y 10000 como entrada: ";
        cin >> algunValor;
        if (algunValor == -1) {
          vectA.clear();
          break;
        }
        // int **p = &(**indexSearchN);
        index = algunValor;
        vectA = valoresC.selectIndexDC(algunValor);
        cout << "El numero objetivo es: " << vectA[0][0] << endl;
        // float valPr = precisionEntrenamiento(numeroValidA, 10000.0f);
        // multiplicarMatrices(valoresC.getPesos(), vectA);
      }
    }
    if (valorOpcion == 2) {
      cout << "Dibuje en la pantalla" << endl;
    }
    if (valorOpcion == -1) {
      cout << "Saliendo del programa ..." << endl;
      break;
    }
    if (valorOpcion <= 0 || valorOpcion >= 3) {
      cout << "Ingrese una opcion valida." << endl;
    }
  }
}

std::vector<std::pair<double, double>> cursorPositions;
bool drawAreaEnabled = true;
std::vector<int> grid(785, 0);

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
  cursorPositions.push_back({xpos, ypos});
  // std::cout << "tamano mnist_data: "
  //           << sizeof(mnist_data) / sizeof(mnist_data[0]) << std::endl;
  // std::cout << "Posición del cursor: (" << xpos << ", " << ypos << ")"
  //           << std::endl;
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    glfwSetCursorPosCallback(window, cursor_position_callback);
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    glfwSetCursorPosCallback(window, nullptr);
  }
}

void drawPixel(GLFWwindow *window, int x, int y, float colorPixel) {
  float valorC = 1 - (colorPixel / 255);
  glColor3f(valorC, valorC, valorC);
  // glColor3f(250 - colorPixel, 250 - colorPixel, 250 - colorPixel);
  float px = -1.0 + ((x * 2.0) / 28.0);
  float py = 1.0 - ((y * 2.0) / 28.0);
  glBegin(GL_QUADS);
  glVertex2f(px, py);
  glVertex2f(px + (2.0 / 28.0), py);
  glVertex2f(px + (2.0 / 28.0), py - (2.0 / 28.0));
  glVertex2f(px, py - (2.0 / 28.0));
  glEnd();
  // Calcula el índice en el array grid basado en las coordenadas x e y
  int index = y * 28 + x;
  // Marca el valor correspondiente en el array como 1 (pintado)
  grid[index] = 1;
}

void drawNumber(GLFWwindow *window, int &indexSE) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  // cout << "El primer valor de V: " << vectA[0][0] << endl;
  // Itera sobre los datos del MNIST para dibujar los cuadrados pintados
  // cout << "valor de index " << indexSE << endl;
  for (int i = 1; i < vectA.size(); ++i) {
    if (vectA[i][0] > 0.5) {
      int x = i % 28;
      int y = i / 28;
      drawPixel(window, x, y, vectA[i][0]);
    }
  }
  // Aqui habia un for
  //  Imprimir el array grid (opcional, para verificar)
  //  for (int i = 0; i < grid.size(); ++i) {
  //    std::cout << grid[i] << " ";
  //    if ((i + 1) % 28 == 0) {
  //      std::cout << std::endl;
  //    }
  //  }
}

// void drawDrawArea(GLFWwindow *window) {
//   if (drawAreaEnabled) {
//     glColor3f(0.0, 0.0, 0.0);
//     glLineWidth(5);
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(-0.90, 0.90);
//     glVertex2f(0.0, 0.90);
//     glVertex2f(0.0, -0.90);
//     glVertex2f(-0.90, -0.90);
//     glEnd();
//   }
// }

void realDrawArea(GLFWwindow *window) {
  // Itera sobre las posiciones del cursor para dibujar y actualizar el estado
  // de pintado
  for (const auto &pos : cursorPositions) {
    float x = pos.first / higthS * 28.0f;
    float y = pos.second / widthS * 28.0f;
    drawPixel(window, x, y, 255);
  }
  cursorPositions.clear();
}

int mainLoopDraw(std::mutex &mtx) {
  // GLFW
  GLFWwindow *window;

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  window = glfwCreateWindow(higthS, widthS, "MNIST Number", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

  while (!glfwWindowShouldClose(window)) {
    // GLFW
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    if (opcionS == 1) {
      drawNumber(window, indexSearchN);
    }
    if (opcionS == 2) {
      realDrawArea(window);
    }
    // drawDrawArea(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}

int drawGeneral() {

  std::thread hilo1(selectOpt, std::ref(opcionS), std::ref(indexSearchN),
                    std::ref(mtx));
  std::thread hilo2(mainLoopDraw, std::ref(mtx));

  hilo1.join();
  hilo2.join();

  return 0;
}
