#  include <iostream>
#  include <GL/glew.h>
#  include <GL/freeglut.h>
//#  include <GL/glext.h>
//#pragma comment(lib, "glew32.lib") 
#include <cstdlib>
#include<time.h>
#include <string>
using namespace std;



// Coordenadas del triangulo:
#define PUNTO_A_X 10.0 //vertice izq
#define PUNTO_A_Y 20.0 
#define PUNTO_B_X 60.0 //vertice der
#define PUNTO_B_Y 20.0
#define PUNTO_C_X 35.0//vertice superior
#define PUNTO_C_Y 70.0

// Variables generales (datos de entrada)
int numeroDatos = 5;
float datos[10] = {100.0,65.0,45.0,32.0,5.0};
string textoDatos[10] = {"Website Visit", "Download Page Visit", "Downloaded", 
                                 "Interested To Buy", "Purchased"};
float posLineasTextoEnY = 50.0;







// Generador de numeros aleatorios para el color de cada bloque
float numeroAleatorio(){
   float nf = ((1.0 - 0.0) * ((float)rand() / RAND_MAX)) + 0.0; 
   cout<<"n = "<< nf <<"\n";
    return nf;
}



// Calcula la altura de cada bloque/trapecio dentro de la piramide
float alturaCarta(float dato){
   float sumaDatos = 0.0;
   for(int i = 0; i < numeroDatos; i++){
      sumaDatos += datos[i];
   }
   return dato/(sumaDatos/50); // la altura (y).
}



void drawScene(){

    // Vertices superiores de cada bloque
    float verticeSupIzquierdoX = PUNTO_A_X;
    float verticeSupIzquierdoY = PUNTO_A_Y;    
    float verticeSupDerechoX = PUNTO_B_X;
    float verticeSupDerechoY = PUNTO_B_Y;
    // Color del bloque
    float r, g, b = 0.0;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < numeroDatos; i++){

        // Generar color aleatorio para cada bloque
        r = numeroAleatorio();
        g = numeroAleatorio();
        b = numeroAleatorio();


        //color del bloque/trapecio
        glColor3f(r, g , b);

        // Dibujado de cada bloque/trapecio
        glBegin(GL_POLYGON);
            glVertex3f(verticeSupIzquierdoX, verticeSupIzquierdoY, 0.0);
            glVertex3f(verticeSupDerechoX, verticeSupDerechoY, 0.0);         
            glVertex3f(verticeSupDerechoX-alturaCarta(datos[i])/2, verticeSupDerechoY+alturaCarta(datos[i]), 0.0); 
            glVertex3f(verticeSupIzquierdoX+alturaCarta(datos[i])/2, verticeSupIzquierdoY+alturaCarta(datos[i]), 0.0);
        glEnd();
        
        // Guarda los vertices superiores de cada bloque/trapecio.
        // - vertice superior derecho:
        verticeSupIzquierdoX += alturaCarta(datos[i])/2;
        verticeSupIzquierdoY += alturaCarta(datos[i]);
        // - vertice superior izquierdo:
        verticeSupDerechoX += -alturaCarta(datos[i])/2;
        verticeSupDerechoY += alturaCarta(datos[i]);    


    }
    
    glFlush();         

}



// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}



// OpenGL window reshape routine
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}



// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}



int main(int argc, char **argv) 
{
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
   glutInitWindowSize(900, 610);
   glutInitWindowPosition(100, 150); 
   glutCreateWindow("Pyramid Charts & Graphs");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}
