#include <GL/glut.h>
#include <stdio.h>
int x1 = 10, x2 = 20, x3 = 20, x4 = 10, xc = 0;
int yy = 10, y2 = 10, y3 = 20, y4 = 20, yc = 0;
float angulo = 1.0;
float scale = 1.0f;

unsigned char mode = 'T';

int init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // define a cor de fundo

    glMatrixMode(GL_PROJECTION);        // carrega a matriz de projeção
    gluOrtho2D(0.0, 100.0, 0.0, 100.0); // define projeção ortogonal 2D
}

void desenha_quadrado(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity(); // desenha o fundo (limpa a janela)  
    // glTranslatef(0.0f, 0.0f, 0.0f);   // altera o atributo de cor
    glScalef(scale, scale, 1.0f);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);            // desenha uma linha
    glVertex2i(x1, yy);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glVertex2i(x4, y4);
    glEnd();
    // glLoadIdentity();
    glFlush(); // desenha os comandos não executados
}

void teclas_normais(unsigned char teclaNormal, int x, int y)
{ // Controla mode, rotação, transalação e escala
    if (teclaNormal == 'T')
    {
        mode = 'T';
    }

    if (teclaNormal == 'R')
    {
        mode = 'R';
    }

    if (teclaNormal == 'S')
    {
        mode = 'S';
    }
}

void teclas_especiais(int tecla, int x, int y)
{ // Controla as setas

    if (mode == 'T')
    { // Se o mode for T, as setas fazem a translação para o local desejado
        if (tecla == GLUT_KEY_RIGHT)
        {
            glTranslatef(1.0f, 0.0f, 0.0f);
            x1 += 1;
            x2 += 1;
            x3 += 1;
            x4 += 1;
        }

        if (tecla == GLUT_KEY_LEFT)
        {
            glTranslatef(-1.0f, 0.0f, 0.0f);
            x1 -= 1;
            x2 -= 1;
            x3 -= 1;
            x4 -= 1;
        }

        if (tecla == GLUT_KEY_UP)
        {
            glTranslatef(0.0f, 1.0f, 0.0f);
            yy += 1;
            y2 += 1;
            y3 += 1;
            y4 += 1;
        }

        if (tecla == GLUT_KEY_DOWN)
        {
            glTranslatef(0.0f, -1.0f, 0.0f);
            yy -= 1;
            y2 -= 1;
            y3 -= 1;
            y4 -= 1;
        }
    }

    if (mode == 'S')
    { // Se o mode for S, as setas para cima e para baixo relizam a escala
        if (tecla == GLUT_KEY_UP)
        {
            // x1 -= 1;
            // x4 -= 1;
            // x2 += 1;
            // x3 += 1;
            // yy -= 1;
            // y2 -= 1;
            // y3 += 1;
            // y4 += 1;

            // glScalef(1.1f, 1.1f, 0.0f);

            scale += 0.1f;
            // glScalef(scale, scale, 1.0f);
            
        }

        if (tecla == GLUT_KEY_DOWN)
        {
            // x1 += 1;
            // x4 += 1;
            // x2 -= 1;
            // x3 -= 1;
            // yy += 1;
            // y2 += 1;
            // y3 -= 1;
            // y4 -= 1;

            scale -= 0.1f;
        }

        glutPostRedisplay(); 
    }

    if (mode == 'R')
    { // Se o mode for R, as setas de esquerda e direira realizam a rotação
        if (tecla == GLUT_KEY_LEFT)
        {
            // glTranslatef(-x1,-yy,0);
            // printf("X Y %d %d ", x1, yy);
            // glRotatef(1.0f, 0.0, 0.0, 1.0);
            // glTranslatef(x1,yy,0);
            // printf("X Y %d %d ", x1, yy);

            // glMatrixMode(GL_MODELVIEW);
            // glLoadIdentity();
            // // do any camera stuff you want

            // glPushMatrix();
            // // update spin

            // // rotate
            // glRotatef(0.5, 0, 0, 1);

            // // now draw our square

            // glBegin(GL_QUADS);
            // desenha_quadrado();
            // glEnd();
            // glPopMatrix();

            // glFlush();
        }

        if (tecla == GLUT_KEY_RIGHT)
        {
            calcularCentroide(x1,yy,x2,y2,x3,y3,x4,y4);
            glTranslatef(-xc, -yc, 0);
            glRotatef(-angulo, xc, yc, 1.0);
            glTranslatef(xc, yc, 0);

            desenha_quadrado();
        }
    }

    glutPostRedisplay();
}

void calcularCentroide(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    float centroide_x = (x1 + x2 + x3 + x4) / 4;
    float centroide_y = (y1 + y2 + y3 + y4) / 4;
    xc = centroide_x;
    yc = centroide_y;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o quadrado
    desenha_quadrado();
    //angulo += 0.1;
    // Mostra o resultado na tela
    glutSwapBuffers();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);                       // inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // configura o modo de display
    glutInitWindowSize(500, 500);                // configura a largura e altura da janela de exibição
    glutInitWindowPosition(20, 200);
    glutCreateWindow("Os melhores do samba"); // cria a janela de exibição

    init(); // executa função de inicialização
    glutKeyboardFunc(teclas_normais);
    glutSpecialFunc(teclas_especiais);
    // glMatrixMode(GL_PROJECTION);
    // glPushMatrix;
    // glPopMatrix;
    glutDisplayFunc(display); // estabelece a função "display" como a função callback de exibição.
    glutMainLoop();           // mostre tudo e espere
    return 0;
}
