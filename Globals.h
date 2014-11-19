#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtGui>
#include <QtWidgets>

class MainWindow;

// macros
#define CEILING(A)	((A)==(int)(A) ? (int)(A) : (A)>0 ? (int)(A)+1:(int)(A))
#define CLIP(A,L,H)	((A)<=(L) ? (L) : (A)<=(H) ? (A) : (H))
#define MAX(A,B)	((A) > (B) ? (A) : (B))
#define MIN(A,B)	((A) < (B) ? (A) : (B))
#define cmTOin		(1.0/2.54)
#define inTOcm		2.54
#define DEGtoRAD	.01745328
#define	EPSILON		1E-8
#define EPSILON2	1E-12

// global variables
extern MainWindow	*g_mainWindow;

#endif // GLOBALS_H
