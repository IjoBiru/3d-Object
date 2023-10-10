#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>


using namespace std;

float _angle = 0.05f;  //mengatur sudut awal rotasi

void initRendering() {
    glEnable(GL_DEPTH_TEST);  //mengaktifkan ketebalan 
    glEnable(GL_COLOR_MATERIAL);  //mengaktifkan penggunaan warna
    glEnable(GL_LIGHTING);  //mengaktifkan pencahayaan
    glEnable(GL_LIGHT0);  //mengaktifkan sumber cahaya
    glEnable(GL_NORMALIZE);  //mengaktifkan normalisasi
    glShadeModel(GL_SMOOTH);  //mengatur model shading menjadi GL_SMOOTH (halus)
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);  //mengatur ukuran viewport sesuai dengan ukuran jendela
    glMatrixMode(GL_PROJECTION);  //mode matriks proyeksi
    glLoadIdentity();  //reset matriks proyeksi
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);  //mengatur perspektif
}

void drawTable() {
    glColor3f(0.0f, 1.0f, 1.0f);  //mengatur warna menjadi cyan

    glPushMatrix();//untuk menyimpan keaadan matriks
    glScalef(10.0f, 2.5f, 5.0f);  //mengatur skala balok (panjang, lebar, tinggi)
    glTranslatef(0.0, 0.0, 0.0);  //untuk mengatur koordinat bidang
    glutSolidCube(1.0);  //gambar kubus solid
    glPopMatrix(); //mengembalikkan matriks ke keadaan sebelumnya

    glColor3f(1.0f, 1.0f, 1.0f);  //mengatur warna menjadi putih 
    glPushMatrix();  //untuk menyimpan keaadan matriks
    glScalef(9.5f, 1.0f, 4.5f);  //atur skala balok (panjang, lebar, tinggi)
    glTranslatef(0.0, 1.75, 0.0);  //untuk mengatur koordinat bidang
    glutSolidCube(1.0);  //gambar kubus solid
    glPopMatrix();   //mengembalikkan matriks ke keadaan sebelumnya
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //membersihkan buffer warna 

    glMatrixMode(GL_MODELVIEW);  //untuk melakukan transformasi pada objek
    glLoadIdentity();  //untuk mengatur ulang matriks 

    glTranslatef(0.0f, 0.0f, -14.0f);  //geser ke posisi pandangan kamera
    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };  //warna ambien
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);  //mengatur warna ambien

    GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f };  //warna cahaya
    GLfloat lightPos0[] = { 0.0f, -8.0f, 8.0f, 1.0f };  //posisi cahaya
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);  //untuk mengatur warna cahaya difus
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);  //untuk mengatur posisi dari sumber cahaya GL_LIGHT0.

    glRotatef(10, 1.0f, 0.0f, 0.0f);  //memutar objek di sekitar sumbu x
    glRotatef(-10, 0.0f, 0.0f, 1.0f);  //memutar objek di sekitar sumbu z
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);  //memutar objek di sekitar sumbu y

    drawTable();  //menggambar balok

    glutSwapBuffers();  //untuk menukar dua buah buffer tampilan
}

void update(int value) {
    _angle += 1.5f;  //tingkat rotasi
    if (_angle > 360) {
        _angle -= 360;  //reset sudut rotasi setelah melebihi 360 derajat
    }

    glutPostRedisplay();   //untuk meminta tampilan ulang(redraw) jendela atau scene secara manual.
    glutTimerFunc(25, update, 0);  //digunakan untuk mengatur timer yang akan memicu pemanggilan fungsi secara berkala
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  //inisialisasi GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //mode tampilan
    glutInitWindowSize(600, 600);

    glutCreateWindow("Penghapus papan tulis");  //buat jendela dengan judul "Penghapus papan tulis"
    initRendering();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);

    update(0);  //memulai pembaruan sudut rotasi
    glutMainLoop();  //memulai loop utama GLUT

    return 0;
}