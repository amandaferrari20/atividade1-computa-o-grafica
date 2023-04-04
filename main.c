#include <GL/glut.h>
#include <stdio.h>

float xPos[4] = {10.0, 20.0, 20.0, 10.0};
float yPos[4] = {10.0, 10.0, 20.0, 20.0};
float centroid[2] = {5.0, 5.0};

float angulo = 5.0;
float scale = 1.1;

float angleRotated = 0.0;

unsigned char mode = 't';

void calcularCentroide(float *xPos, float *yPos);
void display(void);
int init(void);
void desenha_quadrado(void);
void teclas_normais(unsigned char tecla, int x, int y);
void teclas_especiais(int tecla, int x, int y);


int main(int argc, char **argv){
    glutInit(&argc, argv);                       // inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // configura o modo de display
    glutInitWindowSize(500, 500);                // configura a largura e altura da janela de exibição
    glutInitWindowPosition(20, 200);
    glutCreateWindow("Os melhores do samba"); // cria a janela de exibição

    init(); // executa função de inicialização
    glutKeyboardFunc(teclas_normais);
    glutSpecialFunc(teclas_especiais);
    glutDisplayFunc(display); // estabelece a função "display" como a função callback de exibição.
    glutMainLoop();           // mostre tudo e espere
    return 0;
}

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0); // define a cor de fundo
    glMatrixMode(GL_PROJECTION);        // carrega a matriz de projeção
    gluOrtho2D(0.0, 100.0, 0.0, 100.0); // define projeção ortogonal 2D
}

void display(void){
    desenha_quadrado();
}

void desenha_quadrado(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    for(int i = 0; i < 4; i++){
        glVertex2i(xPos[i], yPos[i]);
    }   
    glEnd();
    glFlush();
}

// Controla mode, rotação, transalação e escala
void teclas_normais(unsigned char tecla, int x, int y){ 
    switch (tecla){
        case 't': mode = 't'; break;
        case 'r': mode = 'r'; break;
        case 's': mode = 's'; break;
        default: break;
    }
}

// Controla as setas
void teclas_especiais(int tecla, int x, int y){ 
    // Se o mode for T, as setas fazem a translação para o local desejado
    if (mode == 't'){ 
        if (tecla == GLUT_KEY_RIGHT){   
            float new_angle = angleRotated * -1;
            glRotatef(angleRotated, 0.0, 0.0, 1.0);
            glTranslatef(1.0f, 0.0f, 0.0f);
            glRotatef(new_angle, 0.0, 0.0, 1.0);
            for(int i = 0; i < 4; i++){
                xPos[i] += 1;
            }
        }
        if (tecla == GLUT_KEY_LEFT){
            float new_angle = angleRotated * -1;
            glRotatef(angleRotated, 0.0, 0.0, 1.0);
            glTranslatef(-1.0f, 0.0f, 0.0f);
            glRotatef(new_angle, 0.0, 0.0, 1.0);
            for(int i = 0; i < 4; i++){
                xPos[i] -= 1;
            }
        }
        if (tecla == GLUT_KEY_UP){
            float new_angle = angleRotated * -1;
            glRotatef(angleRotated, 0.0, 0.0, 1.0);
            glTranslatef(0.0f, 1.0f, 0.0f);
            glRotatef(new_angle, 0.0, 0.0, 1.0);
            for(int i = 0; i < 4; i++){
                yPos[i] += 1;
            }
        }
        if (tecla == GLUT_KEY_DOWN){
            float new_angle = angleRotated * -1;
            glRotatef(angleRotated, 0.0, 0.0, 1.0);
            glTranslatef(0.0f, -1.0f, 0.0f);
            glRotatef(new_angle, 0.0, 0.0, 1.0);
            for(int i = 0; i < 4; i++){
                yPos[i] -= 1;
            }
        }
    }

    // Se o mode for S, as setas para cima e para baixo relizam a escala
    if (mode == 's'){ 
        if (tecla == GLUT_KEY_UP){
            calcularCentroide(xPos, yPos);
            glTranslatef(centroid[0], centroid[1], 0);
            glScalef(scale, scale, 1.0);
            glTranslatef(-centroid[0], -centroid[1], 0);
        }
        if (tecla == GLUT_KEY_DOWN){
            calcularCentroide(xPos, yPos);
            float new_scale = 0.9;
            glTranslatef(centroid[0], centroid[1], 0);
            glScalef(new_scale, new_scale, 1.0);
            glTranslatef(-centroid[0], -centroid[1], 0);
        }
    }

    // Se o mode for R, as setas de esquerda e direira realizam a rotação
    if (mode == 'r'){ 
        if (tecla == GLUT_KEY_LEFT){
            calcularCentroide(xPos, yPos);
            glTranslatef(centroid[0], centroid[1], 0);
            glRotatef(angulo, 0.0, 0.0, 1.0);
            glTranslatef(-centroid[0], -centroid[1], 0);
            angleRotated += angulo;
        }
        if (tecla == GLUT_KEY_RIGHT){
            calcularCentroide(xPos, yPos);
            glTranslatef(centroid[0], centroid[1], 0);
            glRotatef(-angulo, 0.0, 0.0, 1.0);
            glTranslatef(-centroid[0], -centroid[1], 0);
            angleRotated -= angulo;
        }
    }
    glutPostRedisplay();
}

void calcularCentroide(float *xPos, float *yPos) {
    int sumX = 0, sumY = 0;
    for(int i = 0; i < 4; i++){
        sumX += xPos[i];
        sumY += yPos[i];
    }
    centroid[0] = sumX/4;
    centroid[1] = sumY/4;
}
