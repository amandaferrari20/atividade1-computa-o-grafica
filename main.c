#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

#define RES_X 500
#define RES_Y 500

#define SCREEN_RES_X 1920
#define SCREEN_RES_Y 1080

#define NUM_OF_EDGES 4

#define TRANSLATING 'T'
#define ROTATING_RIGHT 'R'
#define ROTATING_LEFT 'L'

#define ROTATING_MODE 'r'
#define TRANSLATING_MODE 't'
#define SCALING_MODE 's'

float xPos[NUM_OF_EDGES] = {10.0, 20.0, 20.0, 10.0};
float yPos[NUM_OF_EDGES] = {10.0, 10.0, 20.0, 20.0};
float centroid[2] = {5.0, 5.0};

float angleOffset = 5.0;
float scaleUp = 1.1;
float scaleDown = 0.9;

float angleRotated = 0.0;

unsigned char mode = TRANSLATING_MODE;

int init(void);
void display(void);
void output(int x, int y, float r, float g, float b, int font, char *string);
void normalKeys(unsigned char key, int x, int y);
void spetialKeys(int key, int x, int y);
void drawSquare(void);
void calcCentroid(float *xPos, float *yPos);
void doTranslateWithRotation(float angle, float x, float y);
void doRotate(float angle, char direction);
void doScale(float scale);


int main(int argc, char **argv){
    glutInit(&argc, argv);                       // inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // configura o modo de display
    glutInitWindowSize(RES_X, RES_Y);                // configura a largura e altura da janela de exibição
    glutInitWindowPosition((SCREEN_RES_X/2)-RES_X/2, (SCREEN_RES_Y/2)-RES_Y/2);
    glutCreateWindow("Os melhores do samba"); // cria a janela de exibição

    init(); // executa função de inicialização
    glutKeyboardFunc(normalKeys);
    glutSpecialFunc(spetialKeys);
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
    drawSquare();
}

void drawSquare(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        for(int i = 0; i < NUM_OF_EDGES; i++){
            glVertex2i(xPos[i], yPos[i]);
        }   
    glEnd();
    glFlush();
}

// Controla mode, rotação, transalação e escala
void normalKeys(unsigned char key, int x, int y){ 
    switch (key){
        case 't': mode = TRANSLATING_MODE; break;
        case 'r': mode = ROTATING_MODE; break;
        case 's': mode = SCALING_MODE; break;
        default: break;
    }
}

// Controla as setas
void spetialKeys(int key, int x, int y){ 
    // Se o mode for T, as setas fazem a translação para o local desejado
    if (mode == TRANSLATING_MODE){ 
        if (key == GLUT_KEY_RIGHT) 
            doTranslateWithRotation(angleRotated, 1.0, 0.0);
        if (key == GLUT_KEY_LEFT)
            doTranslateWithRotation(angleRotated, -1.0, 0.0);
        if (key == GLUT_KEY_UP)
            doTranslateWithRotation(angleRotated, 0.0, 1.0);
        if (key == GLUT_KEY_DOWN)
            doTranslateWithRotation(angleRotated, 0.0, -1.0);
    }

    // Se o mode for S, as setas para cima e para baixo relizam a escala
    if (mode == SCALING_MODE){ 
        if (key == GLUT_KEY_UP) doScale(scaleUp);
        if (key == GLUT_KEY_DOWN) doScale(scaleDown);
    }

    // Se o mode for R, as setas de esquerda e direira realizam a rotação
    if (mode == ROTATING_MODE){ 
        if (key == GLUT_KEY_LEFT) doRotate(angleOffset, ROTATING_LEFT);
        if (key == GLUT_KEY_RIGHT) doRotate(-angleOffset, ROTATING_RIGHT);
    }

    glutPostRedisplay();
}

void doTranslateWithRotation(float angle, float x, float y){
    if(angle != 0){
        doRotate(angle * -1, TRANSLATING);
        glTranslatef(x, y, 0.0f);
        doRotate(angle, TRANSLATING);
    } else {
        glTranslatef(x, y, 0.0f);
        for(int i = 0; i < NUM_OF_EDGES; i++){
            if(x > 0) xPos[i] += 1;
            if(x < 0) xPos[i] -= 1;
            if(y > 0) yPos[i] += 1;
            if(y < 0) yPos[i] -= 1;
        }
    }
}

void doScale(float scale){
    calcCentroid(xPos, yPos);
    glTranslatef(centroid[0], centroid[1], 0);
    glScalef(scale, scale, 1.0);
    glTranslatef(-centroid[0], -centroid[1], 0);
}

void doRotate(float angle, char direction){
    calcCentroid(xPos, yPos);
    glTranslatef(centroid[0], centroid[1], 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-centroid[0], -centroid[1], 0);

    if(direction != TRANSLATING){
        if(direction == ROTATING_RIGHT) {
            angleRotated -= (angle * (-1));
            if(angleRotated == -360.0) angleRotated = 0.0;
        }
        if(direction == ROTATING_LEFT) {
            angleRotated += angle; 
            if(angleRotated == 360.0) angleRotated = 0.0;
        }
    }
}

void calcCentroid(float *xPos, float *yPos) {
    int sumX = 0, sumY = 0;
    for(int i = 0; i < NUM_OF_EDGES; i++){
        sumX += xPos[i];
        sumY += yPos[i];
    }
    centroid[0] = sumX/NUM_OF_EDGES;
    centroid[1] = sumY/NUM_OF_EDGES;
}
