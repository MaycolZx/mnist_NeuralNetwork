#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>

#define widthS 500
#define higthS 500

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

std::vector<std::pair<double, double>> cursorPositions;
bool drawAreaEnabled = true;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
  cursorPositions.push_back({xpos, ypos});
  std::cout << "Posición del cursor: (" << xpos << ", " << ypos << ")"
            << std::endl;
}
void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    glfwSetCursorPosCallback(window, cursor_position_callback);
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    glfwSetCursorPosCallback(window, nullptr);
  }
}

void drawPixel(GLFWwindow *window, int x, int y) {
  glColor3f(0.0, 0.0, 0.0);
  float px = -1.0 + ((x * 2.0) / 28.0); // Escala horizontalmente
  float py = 1.0 - ((y * 2.0) / 28.0);  // Escala verticalmente
  glBegin(GL_QUADS);
  glVertex2f(px, py);
  glVertex2f(px + (2.0 / 28.0), py);
  glVertex2f(px + (2.0 / 28.0), py - (2.0 / 28.0));
  glVertex2f(px, py - (2.0 / 28.0));
  glEnd();
}

// void drawNumber(GLFWwindow *window) {
//   glClear(GL_COLOR_BUFFER_BIT);
//   glColor3f(0.0, 0.0, 0.0);
//   for (int i = 0; i < sizeof(mnist_data) / sizeof(float); ++i) {
//     double x = -1.0 + (i % 28) * (2.0 / 28);
//     double y = 1.0 - (i / 28) * (2.0 / 28);
//     if (mnist_data[i] > 0.5) {
//       glBegin(GL_QUADS);
//       glVertex2f(x, y);
//       glVertex2f(x + (2.0 / 28), y);
//       glVertex2f(x + (2.0 / 28), y - (2.0 / 28));
//       glVertex2f(x, y - (2.0 / 28));
//       glEnd();
//     }
//   }
//   glColor3f(0.0, 0.0, 0.0);
//   for (const auto &pos : cursorPositions) {
//     float x = -1.0 + (pos.first / 800) * 2.0;
//     float y = 1.0 - (pos.second / 800) * 2.0;
//     glBegin(GL_QUADS);
//     glVertex2f(x - 0.02, y - 0.02);
//     glVertex2f(x + 0.02, y - 0.02);
//     glVertex2f(x + 0.02, y + 0.02);
//     glVertex2f(x - 0.02, y + 0.02);
//     glEnd();
//   }
// }

void drawNumber(GLFWwindow *window) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  for (int i = 0; i < sizeof(mnist_data) / sizeof(float); ++i) {
    if (mnist_data[i] > 0.5) {
      int x = i % 28;
      int y = i / 28;
      drawPixel(window, x, y);
    }
  }
  for (const auto &pos : cursorPositions) {
    float x = pos.first / higthS * 28.0f;
    float y = pos.second / widthS * 28.0f;
    drawPixel(window, x, y);
  }
}

// void drawNumber(GLFWwindow *window) {
//   glClear(GL_COLOR_BUFFER_BIT);
//   glColor3f(0.0, 0.0, 0.0);
//
//   for (int i = 0; i < sizeof(mnist_data) / sizeof(float); ++i) {
//     double x = -1.0 + (i % 28) * (2.0 / 28);
//     double y = 1.0 - (i / 28) * (2.0 / 28);
//     if (mnist_data[i] > 0.5) {
//       glBegin(GL_QUADS);
//       glVertex2f(x, y);
//       glVertex2f(x + (2.0 / 28), y);
//       glVertex2f(x + (2.0 / 28), y - (2.0 / 28));
//       glVertex2f(x, y - (2.0 / 28));
//       glEnd();
//     }
//   }
//
//   glColor3f(0.0, 0.0, 0.0);
//   for (const auto &pos : cursorPositions) {
//     float x = -1.0 + (pos.first / 800) * 2.0;
//     float y = 1.0 - (pos.second / 800) * 2.0;
//     int gridX = static_cast<int>((x + 1.0) / (2.0 / 28));
//     int gridY = static_cast<int>((1.0 - y) / (2.0 / 28));
//     int dataIndex = gridY * 28 + gridX;
//     if (dataIndex >= 0 && dataIndex < sizeof(mnist_data) / sizeof(float)) {
//       if (mnist_data[dataIndex] > 0.5) {
//         glBegin(GL_QUADS);
//         glVertex2f(x, y);
//         glVertex2f(x + (2.0 / 28), y);
//         glVertex2f(x + (2.0 / 28), y - (2.0 / 28));
//         glVertex2f(x, y - (2.0 / 28));
//         glEnd();
//       }
//     }
//   }
// }
void drawDrawArea(GLFWwindow *window) {
  if (drawAreaEnabled) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.50, 1.0);
    glVertex2f(0.0, 1.0);
    glVertex2f(0.0, -0.50);
    glVertex2f(-0.50, -0.50);
    glEnd();
  }
}

int main() {
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
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    drawNumber(window);
    drawDrawArea(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
