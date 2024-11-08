#include <freeglut.h>

// Variabel global untuk posisi dan rotasi Mario
float posX = 0.0f;
float posY = 0.0f;
float angle = 0.0f; // Sudut rotasi, default 0 derajat

// Variabel untuk lompatan
bool isJumping = false;      // Apakah Mario sedang melompat
float jumpSpeed = 0.0f;      // Kecepatan lompatan Mario
float gravity = -0.1f;       // Gravitasi yang menarik Mario turun

void drawPixel(float x, float y, float r, float g, float b) {
    glColor3f(r, g, b); // Set color
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1.0f, y);
    glVertex2f(x + 1.0f, y + 1.0f);
    glVertex2f(x, y + 1.0f);
    glEnd();
}

void drawMario() {
    int mario[16][16] = {
        {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,0,0,3,3,3,2,2,2,4,2,0,0,0,0},
        {0,0,0,3,2,3,2,2,2,2,4,2,2,2,0,0},
        {0,0,0,3,2,3,3,2,2,2,2,4,2,2,2,0},
        {0,0,0,0,3,2,2,2,2,2,4,4,4,4,0,0},
        {0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0},
        {0,0,0,0,1,1,5,1,1,1,1,0,0,0,0,0},
        {0,0,0,1,1,1,5,1,1,5,1,1,1,0,0,0},
        {0,0,1,1,1,1,5,5,5,5,1,1,1,1,0,0},
        {0,0,2,2,1,5,6,5,5,6,5,1,2,2,0,0},
        {0,0,2,2,2,5,5,5,5,5,5,2,2,2,0,0},
        {0,0,2,2,5,5,5,5,5,5,5,5,2,2,0,0},
        {0,0,0,0,5,5,5,0,0,5,5,5,0,0,0,0},
        {0,0,0,3,3,3,0,0,0,0,3,3,3,0,0,0},
        {0,0,3,3,3,3,0,0,0,0,3,3,3,3,0,0},
    };

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            float x = j - 8; // Centering the art
            float y = 8 - i; // Invert y for OpenGL's coordinate system
            if (mario[i][j] == 1) drawPixel(x, y, 1.0f, 0.0f, 0.0f); // Red
            else if (mario[i][j] == 2) drawPixel(x, y, 1.0f, 0.647f, 0.0f); // Orange
            else if (mario[i][j] == 3) drawPixel(x, y, 0.545f, 0.271f, 0.075f); // Brown
            else if (mario[i][j] == 4) drawPixel(x, y, 0.0f, 0.0f, 0.0f); // Black
            else if (mario[i][j] == 5) drawPixel(x, y, 0.0f, 0.0f, 1.0f); // Blue
            else if (mario[i][j] == 6) drawPixel(x, y, 1.0f, 1.0f, 0.0f); // Yellow
        }
    }
}

void updateJump() {
    if (isJumping) {
        posY += jumpSpeed;   // Tambahkan kecepatan ke posisi Y
        jumpSpeed += gravity; // Tambahkan gravitasi ke kecepatan

        if (posY <= 0.0f) {   // Jika menyentuh tanah
            posY = 0.0f;      // Reset ke posisi awal
            isJumping = false; // Tidak sedang melompat
            jumpSpeed = 0.0f;  // Reset kecepatan lompatan
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    if (angle == 180.0f) {
        glScalef(-1.0f, 1.0f, 1.0f); // Mirror di sumbu X saat menghadap kiri
    }

    drawMario();
    glPopMatrix();

    updateJump(); // Perbarui posisi lompatan setiap frame

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': posY += 1.0f; break; // Pindah ke atas
    case 's': posY -= 1.0f; break; // Pindah ke bawah
    case 'a':
        posX -= 1.0f; // Pindah ke kiri
        angle = 180.0f; // Tandai bahwa Mario menghadap kiri
        break;
    case 'd':
        posX += 1.0f; // Pindah ke kanan
        angle = 0.0f; // Tandai bahwa Mario menghadap kanan
        break;
    case ' ': // Tombol spasi untuk melompat
        if (!isJumping) {     // Mulai lompatan jika tidak sedang melompat
            isJumping = true; // Tandai bahwa Mario sedang melompat
            jumpSpeed = 2.0f; // Set kecepatan awal lompatan
        }
        break;
    default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Mario Pixel Art Movement with Jumping");

    glClearColor(135.0 / 255.0f, 206.0 / 255.0f, 235.0 / 255.0f, 1.0f);
    gluOrtho2D(-40, 40, -40, 40);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Daftarkan fungsi input keyboard
    glutIdleFunc(display);      // Render ulang saat idle untuk update lompatan
    glutMainLoop();
    return 0;
}
