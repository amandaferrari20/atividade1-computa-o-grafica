#include <GL/glut.h>
int x1 = 10, x2 = 20, x3 = 20, x4 = 10;
int y1 = 10, y2 = 10, y3 = 20, y4 = 20;
unsigned char mode = 'T';

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);     //define a cor de fundo

    glMatrixMode(GL_PROJECTION);          //carrega a matriz de projeção
    gluOrtho2D(0.0,100.0,0.0,100.0);      //define projeção ortogonal 2D

}

void desenha_quadrado(void){
    glClear(GL_COLOR_BUFFER_BIT);         //desenha o fundo (limpa a janela)
    glColor3f(1.0,0.0,0.0);               //altera o atributo de cor
    glBegin(GL_POLYGON);                    //desenha uma linha
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glVertex2i(x3,y3);
        glVertex2i(x4,y4);
    glEnd();

    glFlush();                            //desenha os comandos não executados
}

void tecla(int key, int x, int y);

void display(void){
    desenha_quadrado();
    glutSpecialFunc(tecla());
    teclas_especiais(tecla());

    // x1,x2,x3,x4 += 3;
}

void teclas_especiais(tecla){
    if(tecla == GLUT_KEY_RIGHT){    
        x1 += 10;
        x2 += 10;
        x3 += 10;
        x4 += 10;
    }
    
    // if(tecla == GLUT_KEY_LEFT){
        
    // }

    // if(tecla == GLUT_KEY_UP){
        
    // }

    // if(tecla == GLUT_KEY_DOWN){
        
    // }
}

int main(int argc, char** argv) {

    glutInit(&argc,argv);                                     //inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);               //configura o modo de display
    glutInitWindowSize(500,500);                              //configura a largura e altura da janela de exibição
    glutInitWindowPosition(20,200);
    glutCreateWindow("Os melhores do samba");           //cria a janela de exibição

    init();                          //executa função de inicialização
    glutDisplayFunc(display);        //estabelece a função "display" como a função callback de exibição.
    glutMainLoop();                  //mostre tudo e espere
    return 0;
}

