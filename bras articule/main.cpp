
/*********************************************************/
/*        TP3: Bras articulé                             */
/*********************************************************/
/*													     */
/*       ESGI: Algorithmiques pour l'infographies		 */
/*													     */
/*********************************************************/
/*													     */
/*  Objectif: Comporendre comment faire des rotations plus complexe  */
/*													     */
/*********************************************************/


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include<stdlib.h>
#include<stdio.h>




float angle, angle2 = 0.0;
float cameraAngle = 10.0;

/* prototypes de fonctions */
void initRendering();                           // Initialisation du rendu
void display();                             	// modélisation
void reshape(int w,int h);                      // visualisation
void update(int value);                         // mise à jour: appelle Timer pour l'animation de la sc�ne
void keyboard(unsigned char key, int x, int y); // fonction clavier

void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(10 ,update, 0);
}


/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
		  char **argv){  // argv: tableau de chaines de caract�res, argv[0] contient le nom du programme lanc� (plus un �ventuel chemin)


	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(500, 500);                // dimension fen�tre
	glutInitWindowPosition (100, 100);           // position coin haut gauche
	glutCreateWindow("TP1: formes 2D et transformation");  // nom

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appel�es par glut */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(200, update, 0);

	/* rq: le callback de fonction (fonction de rappel) est une fonction qui est pass�e en argument � une
	autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en m�me temps)
	alors qu'il ne les conna�t pas par avance.*/


	/* Entr�e dans la boucle principale de glut, traitement des �v�nements */
    glutMainLoop();         // lancement de la boucle de r�ception des �v�nements
    return 0;               // pour finir
}


/* Initialisation d'OpenGL pour le rendu de la sc�ne */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* d�finit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  d�finit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Création de la scène */
void display(){

	/* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
	rq: buffer: m�moire tampon, c'est donc une surface en memoire utilis�e pour stocker une image*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* la mat de visualisation-mod�lisation est modifiable par d�faut */
	glMatrixMode(GL_MODELVIEW);

	/* on charge l'identit� dans la matrice de mod�lisation-visualisation*/
	glLoadIdentity();


	/* Permet de créer un point de vue. Définit une matrice de mod�lisation-visualisation et la multiplie
	à droite de lma matrice active, ici l'identité*/
	gluLookAt(0.0, 0.0, 8.0,      // position caméra
		      0.0, 0.0, 0.0,      // point de mire
			  0.0, 1.0, 0.0);     // vecteur d'orientation cam�ra

	// glPushMatrix();
	// 	glTranslatef(-0.5,-0.5,0.5);
	// 	glColor3f(0.2, 0.4, 0.7);glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
	// 	glBegin(GL_TRIANGLES);
	// 		glVertex3f(0.5, -0.5, 0.0);
	// 		glVertex3f(0.0, 0.5, 0.0);
	// 		glVertex3f(-0.5, -0.5, 0.0);
	// 	glEnd();
	// glPopMatrix();

	glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.0);
        glRotatef(angle, 0.0, 0.0, 1.0);
        glTranslatef(1.0, 0.0, 0.0);
	    glPushMatrix();
			/* 1st object */
            glScalef(2.0, 1.0 ,1.0);
            glutWireCube(1.0);
	    glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0, 0.0, 0.0);
			glRotatef(angle2, 0.0, 0.0, 1.0);
			glTranslatef(-1.0, 0.0, 0.0);

			/* Avant bras */
			glScalef(2.0, 1.0 ,1.0);
			glutWireCube(1.0);
		glPopMatrix();

	glPopMatrix();



	/* On swap (échange) les buffers, càd, on fait passer l'image calcul�e et dessin�e
	dans le back buffer au buffer qui va l'afficher: le front buffer (en g�n�ral), c'est le bouble buffering
	Cela �vite une image animée sacadée, si elle était directement trac�e dans le front buffer*/
	glutSwapBuffers();

	/* On force l'affichage */
	glFlush(); // nettoie les fenétres précédentes
}


/*  Mise en forme de la sc�ne pour l'affichage */
void reshape(int w,  // w: largeur fenêtre
			 int h)  // h: hauteur fenêtre
{
	/* Viewport: cadrage. Sp�cifie la r�gion (position et taille en px) que l'image observ�e de la sc�ne occupe
	� l'�cran => r�duction et agrandissement de l'image possible*/
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);

	/* Sp�cifie que la matrice de projection va �tre modifi�e  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();             // matrice courante: l'identit�
	//glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	/* Perspective avec point de fuite */
	gluPerspective(60.0,                       // angle d'ouverture vertical cam�ra
				   (GLfloat) w / (GLfloat) h,  // ratio largeur-hauteur
				   1.0,						   // plan proche z=1
				   200.0);                     // plan �loign� z=200


}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key,       // Touche qui a �t� press�e
                    int x, int y) {    // Coordonn�es courante de la souris

		switch (key){

			case 'p':   /* affichage du carré plein*/
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				glutPostRedisplay();
				break;

			case 'f':   /* affichage en mode fil de fer*/
				angle2 += 1.0;
				if (angle2 > 45) {
					angle2 = 45;
				}
				glutPostRedisplay();
				break;

			case 'F':   /* affichage en mode fil de fer*/
				angle2 -= 1.0;
				if (angle2 < 0) {
					angle2 = 0;
				}
				glutPostRedisplay();
				break;

			case 'z':   /* affichage en mode fil de fer*/
				angle += 1.0;
				glutPostRedisplay();
				break;

			case 'Z':   /* affichage en mode fil de fer*/
				angle -= 1.0;
				glutPostRedisplay();
				break;

			case 's':   /* affichage en mode sommets seuls*/
				glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
				glutPostRedisplay();
				break;

			case 'q':   /* Quitter le programme */
				exit(0);
		}
}
