#include <freeglut.h>
#include <cmath>


float backgroundOffsetX = 0.0f; // Offset untuk efek infinite scroll
float backgroundOffsetX2 = 0.0f;      // Offset untuk efek infinite scroll pada awan lapisan 2
float mountainOffsetX = 0.0f; // Offset untuk efek parallax gunung yang lebih lambat


// Variabel global untuk posisi dan rotasi Mario
float posX = -30.0f;
float posY = -11.0f;  // Ubah nilai posY sesuai dengan ground level
float groundLevelY = posY;  // Tambahkan groundLevelY untuk posisi awal Mario
float angle = 0.0f; // Sudut rotasi, default 0 derajat


// Variabel untuk lompatan
bool isJumping = false;      // Apakah Mario sedang melompat
float jumpSpeed = 0.0f;      // Kecepatan lompatan Mario
float gravity = -0.1f;       // Gravitasi yang menarik Mario turun

// Delta time variables
int lastTime = 0; // Waktu frame terakhir

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

// Fungsi menggambar awan
void drawCloud(float posX, float posY) {
    glColor3f(1.0f, 1.0f, 1.0f);
    float cloudRadius = 4.0f;

    // Lingkaran pertama
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX, posY);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(posX + cos(angle) * cloudRadius, posY + sin(angle) * cloudRadius);
    }
    glEnd();

    // Lingkaran kedua
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX + 5.0f, posY);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(posX + 5.0f + cos(angle) * cloudRadius, posY + sin(angle) * cloudRadius);
    }
    glEnd();

    // Lingkaran ketiga
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX + 2.5f, posY + 3.0f);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(posX + 2.5f + cos(angle) * cloudRadius, posY + 3.0f + sin(angle) * cloudRadius);
    }
    glEnd();
}

void drawCloudsWithParallax() {
    float cloudSpacing = 80.0f;
    float screenWidth = 80.0f;

    // Gambar awan di lapisan pertama dengan offset pertama
    for (float x = -screenWidth / 2 + fmod(backgroundOffsetX, cloudSpacing); x < screenWidth / 2; x += cloudSpacing) {
        drawCloud(x, 15.0f);
    }

    // Gambar awan di lapisan kedua dengan offset kedua dan posisi berbeda
    for (float x = -screenWidth / 2 + fmod(backgroundOffsetX2, cloudSpacing); x < screenWidth / 2; x += cloudSpacing) {
        drawCloud(x  , 30.0f);
    }
}



float brickWidth = 15.0f;  // Lebar background hitam (default 15.0f)
float brickHeight = 15.0f; // Tinggi background hitam (default 15.0f)

// Fungsi untuk mengubah ukuran background hitam
void setBrickSize(float newWidth, float newHeight) {
    brickWidth = newWidth;
    brickHeight = newHeight;
}

void drawBrick(float BrickHeight) {
    float gridSpacing = 17.0f; // Jarak antar grid, sesuaikan sesuai lebar grid
    float screenWidth = 80.0f; // Lebar layar (sesuaikan dengan pengaturan ortho)

    // Mulai dari posisi terjauh ke kiri yang masih di layar, lalu gambar grid hingga melampaui lebar layar
    for (float x = -screenWidth / 2 + fmod(backgroundOffsetX, gridSpacing); x < screenWidth / 2; x += gridSpacing) {
        // Menggambar persegi besar hitam sebagai latar belakang untuk setiap grid
        glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
        glBegin(GL_QUADS);
        glVertex2f(x - 0.5f, BrickHeight); // Posisi kiri bawah
        glVertex2f(x + brickWidth, BrickHeight); // Posisi kanan bawah
        glVertex2f(x + brickWidth, BrickHeight + brickHeight); // Posisi kanan atas
        glVertex2f(x - 0.5f, BrickHeight + brickHeight); // Posisi kiri atas
        glEnd();

        // Menggambar grid 3x3 kotak di atas persegi besar hitam
        float startX = x; // Posisi X awal dari setiap grid
        float startY = BrickHeight; // Posisi Y awal (menggunakan BrickHeight)
        float size = 5.0f; // Ukuran setiap kotak
        float spacing = 0.5f; // Jarak antar kotak

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                float cellX = startX + col * (size + spacing);
                float cellY = startY + row * (size + spacing);

                glColor3f(0.714f, 0.286f, 0.149f); // Warna coklat kemerahan
                glBegin(GL_QUADS);
                glVertex2f(cellX, cellY);
                glVertex2f(cellX + size, cellY);
                glVertex2f(cellX + size, cellY + size);
                glVertex2f(cellX, cellY + size);
                glEnd();
            }
        }
    }
}

void updateJump(float deltaTime) {
    if (isJumping) {
        posY += jumpSpeed * deltaTime;   // Tambahkan kecepatan ke posisi Y
        jumpSpeed += gravity * deltaTime; // Tambahkan gravitasi ke kecepatan

        if (posY <= groundLevelY) {  // Gunakan groundLevelY sebagai level tanah
            posY = groundLevelY;      // Reset ke posisi awal di groundLevelY
            isJumping = false;        // Tidak sedang melompat
            jumpSpeed = 0.0f;         // Reset kecepatan lompatan
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        if (posX > -30.0f) {
            posX -= 1.0f;
        }
        else if (backgroundOffsetX < 0.0f) {
            backgroundOffsetX += 1.5f;
            backgroundOffsetX2 += 1.0f; // Parallax yang lebih lambat untuk awan lapisan kedua
            mountainOffsetX += 0.5f;
        }
        angle = 180.0f;
        break;
    case 'd':
        if (posX < 0.0f) {
            posX += 1.0f;
        }
        else {
            backgroundOffsetX -= 1.5f;
            backgroundOffsetX2 -= 1.0f; // Parallax yang lebih lambat untuk awan lapisan kedua
            mountainOffsetX -= 0.5f;
        }
        angle = 0.0f;
        break;
    case ' ':
        if (!isJumping) {
            isJumping = true;
            jumpSpeed = 2.0f;
        }
        break;
    default: break;
    }
    glutPostRedisplay();
}

float mountainScale = 4.0f; // Variabel untuk mengatur ukuran gunung (1.0f adalah ukuran default)
float mountainPosY = -17.0f; // Variabel untuk mengatur posisi Y gunung
float mountainSpacing = 50.0f; // Jarak antar gunung

// Fungsi menggambar gunung dengan efek parallaxing
void drawMountain(float posX) {
    glColor3f(0.5f, 0.5f, 0.5f);

    // Gunung pertama (segitiga besar)
    glBegin(GL_TRIANGLES);
    glVertex2f(posX, -17.0f);
    glVertex2f(posX + 15.0f * 4.0f, -17.0f);
    glVertex2f(posX + 7.5f * 4.0f, 20.0f); 
    glEnd();

    // Gunung kedua (segitiga lebih kecil)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(posX + 5.0f * 4.0f, -17.0f);
    glVertex2f(posX + 10.0f * 4.0f, -17.0f);
    glVertex2f(posX + 7.5f * 4.0f, 0.0f);  
    glEnd();
}

// Fungsi untuk menggambar semua gunung dengan posisi bergeser menggunakan parallax
void drawMountainsWithParallax() {
    float mountainSpacing = 80.0f;
    float screenWidth = 80.0f;

    // Posisi X gunung berdasarkan offset parallax
    for (float x = -screenWidth / 2 + fmod(mountainOffsetX, mountainSpacing); x < screenWidth / 2; x += mountainSpacing) {
        drawMountain(x);
    }
}

void display() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 10.0f; // Konversi ke detik
    lastTime = currentTime;

    glClear(GL_COLOR_BUFFER_BIT);

    // Gambar Gunung dengan ukuran dan posisi Y yang dapat diatur
    drawMountainsWithParallax();
    drawCloudsWithParallax();



    // Gambar awan tanpa batas dengan wrap-around posisi X
    float cloudSpacing = 80.0f; // Jarak antar awan
    float screenWidth = 80.0f; // Lebar layar (atur sesuai pengaturan ortho)

    // Mulai dari posisi terjauh ke kiri yang masih di layar, lalu gambar awan hingga melampaui lebar layar
    for (float x = -screenWidth / 2 + fmod(backgroundOffsetX, cloudSpacing); x < screenWidth / 2; x += cloudSpacing) {
        drawCloud(x, 15.0f);  // Y dapat disesuaikan sesuai tinggi awan yang diinginkan
        drawCloud(x + 20.0f, 25.0f);  // Y dapat disesuaikan sesuai tinggi awan yang diinginkan
        drawCloud(x + 40.0f, 15.0f);  // Y dapat disesuaikan sesuai tinggi awan yang diinginkan
        drawCloud(x + 70.0f, 25.0f);  // Y dapat disesuaikan sesuai tinggi awan yang diinginkan
    }

    // Loop untuk menggambar grid beberapa kali
    drawBrick(-49.5f);
    drawBrick(-33.0f);
    setBrickSize(19.0f, 16.0f);

 

    // Gambar Mario
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    if (angle == 180.0f) {
        glScalef(-1.0f, 1.0f, 1.0f); // Mirror di sumbu X saat menghadap kiri
    }
    drawMario();
    glPopMatrix();

    updateJump(deltaTime); // Perbarui posisi lompatan dengan delta time

    glutSwapBuffers();
}







int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Mario Pixel Art Movement with Jumping");

    glClearColor(135.0 / 255.0f, 206.0 / 255.0f, 235.0 / 255.0f, 1.0f);
    gluOrtho2D(-40, 40, -40, 40);

    lastTime = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}