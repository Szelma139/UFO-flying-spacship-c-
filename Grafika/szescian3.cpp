/*
     Prosty studencki program graficzny 
	 kodowany w jezyku C z uzyciem OpenGL 
*/
#include "szescian3.h"
#include "RESOURCE.H"

#include <AntTweakBar.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include<ctime>
#include <cstdlib>
#include "gl/glut.h"
#include <time.h>
#include <cstdio>
#include <cmath>
using namespace std;

#define BITMAP_ID 0x4D42		// identyfikator formatu BMP
//TwBar *myBar = TwNewBar("OGLDEV");
TwBar *myBar;

// Opis tekstury
BITMAPINFOHEADER	bitmapInfoHeader;	// nag³ówek obrazu
unsigned char*		bitmapData;			// dane tekstury
unsigned int		texture[10];			// obiekt tekstury
										// Set Pixel Format function - forward declaration
void SetDCPixelFormat(HDC hDC);
double kat = 0;									// Color Palette handle
HPALETTE hPalette = NULL;
int l = 0;  // KLAWISZ - zmienna przesuwajaca w lewo	
int k = 0;   //KLAWISZ - zmienna przesuwam w prawo
int k1 = 0;   //KLAWISZ - zmienna przesuwam w gora
int l1 = 0;   //KLAWISZ - zmienna przesuwam w dol
int k2 = 0;   //KLAWISZ - zmienna przesuwam w w zecie gora
int l2 = 0;   //KLAWISZ - zmienna przesuwam w w zecie dol
float rot[3] = { 0,0,0 };
int schowaj = 0;
float sunrev = 0.0;        // the amount of revolution of the sun
float delsunrev = 0.0;  // the amount of change in the revolution (rotation) per frame of animation
float delang = 0.01;   // the amo
LONG WINAPI WndProc( HWND, UINT, WPARAM, LPARAM );
HGLRC SetUpOpenGL( HWND hWnd );
float kat_obrotu = 0;
// Wartosci poczatkowe
#define	DEFAULT_Z_DIST		25
#define DEFAULT_PIVOT_VERT_ANGLE	0
#define DEFAULT_PIVOT_HORIZ_ANGLE	0
#define DEFAULT_PIVOT_X				0
#define DEFAULT_PIVOT_Y				0
bool kolizja = FALSE;
////////////////////////////////////////////////////////////////////
//TWEAKBAR
// set a variable 'step' parameter
float vstep = 0.1f;
// set arrow color of a direction variable
// fold a group
int opened = 0;
int color[3] = { 255, 255, 128 };
// set a bar values width
int width = 160; // pixels
// set a key shortcut
char keysc[] = "ALT+a";
char align[] = "horizontal";
GLfloat postx = 0;
GLfloat posty = 0;


/////


#define    DEFAULT_Z_DIST        25
#define DEFAULT_PIVOT_VERT_ANGLE    0
#define DEFAULT_PIVOT_HORIZ_ANGLE    0
#define DEFAULT_PIVOT_X                0
#define DEFAULT_PIVOT_Y                0
#define PI 3.14159265359
#define GL_PI 3.1416
#define r 10
#define false 0
#define true 1
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS





////


int isShown = true;
GLfloat pozycjaXYZ2[3] = { 0.f, 0.f, 0.f };
GLfloat pozycjaXYZ[3] = { 20.f, 0.f, 0.f }; // pozycja początkowa niektórych figur
//double PI = 3.14159265359;
//char figura = VK_F1;
GLfloat xRuch;
GLfloat yRuch;
GLfloat zRuch;
GLfloat szybkosc_kamery = 0.1;
GLfloat xKamera = 0;
GLfloat yKamera = 1;
GLfloat zKamera = -20;
GLfloat xlKamera = 0;
GLfloat ylKamera = 0;
GLfloat zlKamera = 0;
GLfloat CamX;
GLfloat xRuch2;
GLfloat vek_x = 0;
GLfloat vek_y =-1;
GLfloat vek_z = 0;
//GLfloat pozycjastatkux[2] = { 0.0f, 0.0f, 0.0f };
GLint timer;
/////
float z_dist=DEFAULT_Z_DIST;						// INSERT, PAGE UP
float pivot_vert_angle=DEFAULT_PIVOT_VERT_ANGLE;	// UP, DOWN
float pivot_horiz_angle=DEFAULT_PIVOT_HORIZ_ANGLE;	// LEFT, RIGHT
float pivot_x=DEFAULT_PIVOT_X;						// DELETE, PAGE DOWN
float pivot_y=DEFAULT_PIVOT_Y;						// HOME, END
float gl_przesun_x = 0;
float gl_przesun_y = 0;
float gl_przesun_z = 0;





// DEKLARACJE MGLY
bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool	light;				// Lighting ON/OFF
bool	lp;					// L Pressed?
bool	fp;					// F Pressed?
bool	gp;					// G Pressed? ( NEW )

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };
GLuint	filter;				// Which Filter To Use
GLuint	fogMode[] = {  GL_EXP2 };	// typy mgly   //GL_EXP, GL_EXP2, GL_LINEAR 
GLuint	fogfilter = 0;								// Which Fog Mode To Use 
GLfloat	fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };


/// KONIEC DEKLARACJI MGLY
// ************ Deklaracje funkcji ************************

void DrawOpenGLScene( void );  // glowna funkcja rysujaca

//   Skladowe funkcje obiektu graficznego

//void szescian(void);

void SetupRC()
{
	// Light values and coordinates
	//GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	//GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat	 lightPos[] = { 0.0f, 150.0f, 150.0f, 1.0f };
	//GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };


	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
								//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

								// Enable lighting
								//glEnable(GL_LIGHTING);

								// Setup and enable light 0
								//glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
								//glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
								//glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
								//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
								//glEnable(GL_LIGHT0);

								// Enable color tracking
								//glEnable(GL_COLOR_MATERIAL);

								// Set Material properties to follow glColor values
								//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

								// All materials hereafter have full specular reflectivity
								// with a high shine
								//glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
								//glMateriali(GL_FRONT,GL_SHININESS,128);


								// White background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Black brush
	glColor3f(0.0, 0.0, 0.0);
}



// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC)
{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange, GreenRange, BlueRange;
	// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if (!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

								   // Build mask of all 1's.  This creates a number represented by having
								   // the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
								   // pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) - 1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) - 1;

	// Loop through all the palette entries
	for (i = 0; i < nColors; i++)
	{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double)pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char)NULL;
	}


	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC, hRetPal, FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}


// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC)
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
		1,                                                              // Version of this structure    
		PFD_DRAW_TO_WINDOW |                    // Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |					// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,                       // Double buffered
		PFD_TYPE_RGBA,                          // RGBA Color mode
		24,                                     // Want 24bit color 
		0,0,0,0,0,0,                            // Not used to select mode
		0,0,                                    // Not used to select mode
		0,0,0,0,0,                              // Not used to select mode
		32,                                     // Size of depth buffer
		0,                                      // Not used to select mode
		0,                                      // Not used to select mode
		PFD_MAIN_PLANE,                         // Draw in main plane
		0,                                      // Not used to select mode
		0,0,0 };                                // Not used to select mode

												// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}



// LoadBitmapFile
// opis: ³aduje mapê bitow¹ z pliku i zwraca jej adres.
//       Wype³nia strukturê nag³ówka.
//	 Nie obs³uguje map 8-bitowych.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// wskaŸnik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag³ówek pliku
	unsigned char		*bitmapImage;			// dane obrazu
	int					imageIdx = 0;		// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych

												// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// wczytuje nag³ówek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje nag³ówek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaŸnik pozycji pliku na pocz¹tku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiêæ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// sprawdza, czy uda³o siê przydzieliæ pamiêæ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// sprawdza, czy dane zosta³y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// zamienia miejscami sk³adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}


// ..............................

//******** Fukcje skladowe ********************************



double radiany(int x)
{
	return x*(PI / 180);
}


void sleepcp(int milliseconds) // cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}
void szescian(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		// Parametry wierzcholkow

		GLfloat sa[3] = { 0.0f, 0.0f, 1.0f };
		GLfloat sb[3] = { 1.0f, 0.0f, 1.0f };
		GLfloat sc[3] = { 1.0f, 1.0f, 1.0f };
		GLfloat sd[3] = { 0.0f, 1.0f, 1.0f };
		GLfloat se[3] = { 0.0f, 0.0f, 0.0f };
		GLfloat sf[3] = { 1.0f, 0.0f, 0.0f };
		GLfloat sg[3] = { 1.0f, 1.0f, 0.0f };
		GLfloat sh[3] = { 0.0f, 1.0f, 0.0f };
		GLfloat si[3] = { 0.0f, 2.0f, 1.0f };
		GLfloat sj[3] = { 1.0f, 2.0f, 1.0f };

		// Sciany skladowe
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);//glVertex3fv(si);
		glVertex3fv(sb);// glVertex3fv(sj);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
		glEnd();

		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
		glEnd();

		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glEnd();

		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
		glEnd();
	}
}
void drawCube(float size)
{
	float difamb[] = { 1.0, 0.5, 0.3, 1.0 };
	glBegin(GL_QUADS);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);

	
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);

	
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);


	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);

	
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);

	
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
}

void drawSkybox(float size)
{
	bool b1 = glIsEnabled(GL_TEXTURE_2D);     //new, we left the textures turned on, if it was turned on
	glDisable(GL_LIGHTING); //turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);       //turn off depth texting
	glEnable(GL_TEXTURE_2D);        //and turn on texturing
	glBindTexture(GL_TEXTURE_2D, texture[7]);  //use the texture we want
	glBegin(GL_QUADS);      //and draw a face
	//back face
	glTexCoord2f(0, 0);      //use the correct texture coordinate
	glVertex3f(size / 2, size / 2, size / 2);       //and a vertex
	glTexCoord2f(1, 0);      //and repeat it...
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//left face
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//front face
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//right face
	glTexCoord2f(0, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);                      //top face
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, size / 2, -size / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	//bottom face
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glEnable(GL_LIGHTING);  //turn everything back, which we turned on, and turn everything off, which we have turned on.
	glEnable(GL_DEPTH_TEST);
	if (!b1)
		glDisable(GL_TEXTURE_2D);
}



void szescian6(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		// Parametry wierzcholkow

		GLfloat x, y, kat;
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f, 0.0f, 0.0f);
		for (kat = 0.0f; kat<(2.0f*GL_PI); kat += (GL_PI / 32.0f))
		{
			x = 1.5f*sin(kat);
			y = 1.5f*cos(kat);
			glVertex3f(x, y, 0);

		}
		glEnd();
	}
}




void walec2(float h, float r1, float r2, int krok)
{
	int i = 0;
	GLfloat xi, yi, xii, yii, rad;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FRONT_AND_BACK);  //, GL_LINE)
	{
		for (i = 0; i <= 360; i += krok)
		{
			glColor3f(0.0f, 0.3f, 0.3f);
			glBegin(GL_POLYGON);
			rad = i*(3.1415926 / 180);
			xi = r1*sin(rad);
			yi = r1*cos(rad);
			rad = (i + krok)*(3.1415926 / 180);
			xii = r1*sin(rad);
			yii = r1*cos(rad);

			glVertex3f(xi, yi, 0);
			glVertex3f(xi, yi, h);
			glVertex3f(xii, yii, h);
			glVertex3f(xii, yii, 0);
			glEnd();
	
		}
		
	}
	
}

void buduj(GLfloat x, GLfloat y, GLfloat z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	{
		// Parametry wierzcholkow

		GLfloat sa[3] = { x, y, z };
		GLfloat sb[3] = { x + 1, y, z };
		GLfloat sc[3] = { x + 1, y + 1, z };
		GLfloat sd[3] = { x, y + 1, z };
		GLfloat se[3] = { x, y, z + 1 };
		GLfloat sf[3] = { x + 1, y, z + 1 };
		GLfloat sg[3] = { x + 1, y + 1, z + 1 };
		GLfloat sh[3] = { x, y + 1, z + 1 };

		// Sciany skladowe
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
		glEnd();

		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
		glEnd();

		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glEnd();

		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
		glEnd();
	}
}





void uklad_xyz()
{
	glBegin(GL_LINES);

	// uklad kartezjanski os dla z ZIELONA
	glColor3f(0.0f, 255.0f, 0.0f);
	glLineWidth(5044);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 20000.0);
	glEnd();
	//glLineLength(5044);
	glBegin(GL_LINES);

	// uklad kartezjanski X NIEBIESKA
	glColor3f(0.0, 0.0f, 255.0f);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100000.0, 0.0, 0.0);
	glEnd();



	glBegin(GL_LINES);

	// uklad kartezjanski   OS DLA Y ;) CZERWONA
	glColor3f(255.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1000000.0, 0.0);
	glEnd();

}

void wachlarz()
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(-0.5f, 10.0f, 0.0f);

	glEnd();

}

void szescian_radka(void )
{




	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{

		GLfloat x1[3] = { 0.0f, 0.0f, 0.0f };
		GLfloat x2[3] = { 1.0f, 0.0f, 0.0f };
		GLfloat x3[3] = { 0.0f, 1.0f, 0.0f };
		GLfloat x4[3] = { 0.0f, 0.0f, 1.0f };
		GLfloat x5[3] = { 1.0f, 1.0f, 0.0f };
		GLfloat x6[3] = { 1.0f, 0.0f, 1.0f };
		GLfloat x7[3] = { 0.0f, 1.0f, 1.0f };
		GLfloat x8[3] = { 1.0f, 1.0f, 1.0f };
		//glColor3f(1, 1, 1);

		//		glColor3f(.0f, 255.0f, 0.0f);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex3fv(x1);

		glTexCoord2f(0, 1);
		glVertex3fv(x2);        // ZIELONY OD 0
		glTexCoord2f(1, 1);
		glVertex3fv(x5);
		glTexCoord2f(1, 0);
		glVertex3fv(x3);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D);
		glColor3f(.0f, 0.0f, 250.0f);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex3fv(x1);
		glTexCoord2f(0, 1);
		glVertex3fv(x4);
		glTexCoord2f(1, 1);
		glVertex3fv(x6);
		glTexCoord2f(1, 1);
		glVertex3fv(x2);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glColor3f(78.0f, 120.0f, 250.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(x3);
		glVertex3fv(x7);
		glVertex3fv(x8);   //BIALY jedynki wszedzie na y czyli w srodku
		glVertex3fv(x5);
		glEnd();

		glColor3f(124.0f, 255.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(x4);
		glVertex3fv(x6);        // Nowy
		glVertex3fv(x8);
		glVertex3fv(x7);
		glEnd();



		glColor3f(0.0f, 22.0f, 153.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(x1);
		glVertex3fv(x3);        // Nowy dla szerokosci UWAGA SZEROKOSC TO ZIELONA LINIA A NIE NIEBIESKA (NIEBIESKA TO X)
		glVertex3fv(x7);
		glVertex3fv(x4);
		glEnd();


		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex3fv(x2);
		glVertex3fv(x5);        // Nowy dla szerokosci UWAGA SZEROKOSC TO ZIELONA LINIA A NIE NIEBIESKA (NIEBIESKA TO X)
		glVertex3fv(x8);
		glVertex3fv(x6);
		glEnd();



	}

}





/////////////////ladownik koszmiczny radku robimy
void kolo(int podstawa, int promien, int iletrojkatow) {

	double x;
	double y;

	//glFrontFace(GL_STRONA); // słuzy tylko do określenia która strona koła się rysuje, a która nie
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(pozycjaXYZ2[0], pozycjaXYZ2[1], pozycjaXYZ2[2]);
	for (double kat = 0.f; kat <= iletrojkatow; kat++) {
		//	for (double kat = 0.f; kat <= 2 * GL_PI + 0.04; kat += 2 * GL_PI / (float)podstawa) {
		x = promien*cos(kat / 4);
		y = promien*sin(kat / 4);
		glVertex3f(pozycjaXYZ2[0] + x, pozycjaXYZ2[1] + y, pozycjaXYZ2[2]);
	}

	glEnd();

}


void kolo2(GLfloat zaczx, GLfloat zaczy, GLfloat zaczz, int promien, int stopnie, int iletrojkatow) {

	double x;
	double y;


	//glFrontFace(GL_STRONA); // słuzy tylko do określenia która strona koła się rysuje, a która nie
	glColor3f(1.0f, 80.0f, 0.0f);
	GLfloat pozycjaXYZ1[3] = { zaczx, zaczy, zaczz };
	GLfloat pozycjaXYZ11[3] = { 0.f, 0.f, 0.f };
	glBegin(GL_TRIANGLE_FAN);
	//glVertex3f(0.0f,0.0f,0.0f);`
	//glVertex3f(pozycjaXYZ[0], pozycjaXYZ[1], pozycjaXYZ[2]);
	//for (int i = 1; i <= iletrojkatow; i++)
	//{

	for (double kat = 0; kat <= iletrojkatow; kat++) {
		//	for (double kat = 0.f; kat <= 2 * GL_PI + 0.04; kat += 2 * GL_PI / (float)podstawa) {

		x = promien*cos(kat);
		y = promien*sin(kat);

		glVertex3f(pozycjaXYZ1[0] + x, pozycjaXYZ1[1] + y, pozycjaXYZ1[2]);
		//glVertex3f(pozycjaXYZ11[0] + y, pozycjaXYZ11[1] + y, pozycjaXYZ11[2]);
	}
	//}
	glEnd();

}

void noga(GLfloat pozycjax, GLfloat pozycjay, GLfloat pozycjaz, int promien, float wysokosc, int wypelnienie)
{


	double x, x2;
	double y, y2;
	glColor3f(1.f, 0.f, 0.f);
	glColor3f(0.f, 0.f, 1.f);


	glColor3f(0.f, 1.f, 0.f);

	for (double kat = 0; kat <= 2 * GL_PI + 0.04; kat += 2 * GL_PI / (double)wypelnienie) {
		x = promien*cos(kat) / 4;
		y = promien*sin(kat) / 4;
		x2 = promien*cos(kat + (2 * GL_PI / wypelnienie)) / 4;
		y2 = promien*sin(kat + (2 * GL_PI / wypelnienie)) / 4;
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(+x, y, pozycjaXYZ[2]);
		glVertex3f(x2, y2, pozycjaXYZ[2]);
		glVertex3f(x, y, pozycjaXYZ[2] + wysokosc);
		glVertex3f(x2, y2, pozycjaXYZ[2] + wysokosc);
		glEnd();
	}

}

//void walec(GLfloat *pozycjaXYZ, int promien, float wysokosc, int wypelnienie) {
//	double x, x2;
//	double y, y2;
//	GLfloat drugie_kolo[3] = { pozycjaXYZ[0], pozycjaXYZ[1], pozycjaXYZ[2] + wysokosc };
//	glColor3f(1.f, 0.f, 0.f);
//	kolo(pozycjaXYZ, wypelnienie, promien, GL_CW);
//	glColor3f(0.f, 0.f, 1.f);
//	kolo(drugie_kolo, wypelnienie, promien, GL_CCW);
//
//
//	glColor3f(0.f, 1.f, 0.f);
//
//	for (double kat = 0; kat <= 2 * GL_PI + 0.04; kat += 2 * GL_PI / (double)wypelnienie) {
//		x = promien*cos(kat);
//		y = promien*sin(kat);
//		x2 = promien*cos(kat + (2 * GL_PI / wypelnienie));
//		y2 = promien*sin(kat + (2 * GL_PI / wypelnienie));
//		glBegin(GL_TRIANGLE_STRIP);
//		glVertex3f(pozycjaXYZ[0] + x, pozycjaXYZ[1] + y, pozycjaXYZ[2]);
//		glVertex3f(pozycjaXYZ[0] + x2, pozycjaXYZ[1] + y2, pozycjaXYZ[2]);
//		glVertex3f(pozycjaXYZ[0] + x, pozycjaXYZ[1] + y, pozycjaXYZ[2] + wysokosc);
//		glVertex3f(pozycjaXYZ[0] + x2, pozycjaXYZ[1] + y2, pozycjaXYZ[2] + wysokosc);
//		glEnd();
//	}









//}
//TODO: funkcja rysujaca walec- 2 parametry: ilosc paskow w scianie bocznej, ilosc iteracji w kole sciana boczna TRIANGLE_STRIP, podstawa TRIANGLE_FAN





void sfera(double t, int lats, int longs)
{
	

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	
	int i, j;
	int halfLats = lats / 2;
	for (i = 0; i <= halfLats; i++)
	{
		//glColor3f(0, 0, 25);
		double lat0 = GL_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = GL_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);

		for (j = 0; j <= longs; j++)
		{
			double lng = 2 * GL_PI * (double)(j - 1) / longs;
			double x = cos(lng) * 4;
			double y = sin(lng) * 4;

		//	glTexCoord3f(x * zr0, y * zr0, z0);
		
			glNormal3f(x * zr0, y * zr0, z0);
			glTexCoord2f(1, 0);
			glVertex3f(x * zr0, y * zr0, z0);
			
			// glTexCoordf()
			glNormal3f(x * zr1, y * zr1, z1);
			glTexCoord2f(0	, 1);
			glVertex3f(x * zr1, y * zr1, z1);
		
		}
		glEnd();
	}
//	glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);
	//glDisable(GL_TEXTURE_GEN_R);
	//glDisable(GL_TEXTURE_GEN_Q);
}





void moja_kula()
{

























	//glEnable(GL_TEXTURE_2D);
	sfera(15, 15, 15);
	{
		glRotatef(-90, 2, 0, 0);
		sfera(15, 15, 15);
	}
	//glDisable(GL_TEXTURE_2D);
}



void moja_sfera(double t, int lats, int longs, float h)
{
	int i, j;
	int halfLats = lats / 2;

	for (i = 0; i <= halfLats; i++)
	{
		//glColor3f(0, 0, 25);
		double lat0 = GL_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = GL_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++)
		{
			double lng = 2 * GL_PI * (double)(j - 1) / longs;
			double x = cos(lng) * h;
			double y = sin(lng) * h;

			glTexCoord2f(1, 0);
			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);

			glTexCoord2f(1, 1);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
		
	}
}
void prostokat()
{
	GLfloat a[] = { 0, 0, 0 };
	GLfloat b[] = { 0, 0, 4 };
	GLfloat c[] = { 0, 1, 4 };
	GLfloat d[] = { 0, 1, 0 };

	int i = 0;
	GLfloat x1, y1, x11, y11, x2, y2, x22, y22, rad;
	int krok = 3;
	int h = 1;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		for (i = 0; i <= 360; i += krok)
		{
			glBegin(GL_POLYGON);

			//Dolna podstawa
			x1 = sin(radiany(i));
			y1 = cos(radiany(i));
			x11 = sin(radiany(i + krok));
			y11 = cos(radiany(i + krok));

			//Górna podstawa
			x2 = sin(radiany(i));
			y2 = cos(radiany(i));
			x22 = sin(radiany(i + krok));
			y22 = cos(radiany(i + krok));

			glVertex3f(x1, y1, 0.0);
			glVertex3f(x11, y11, 0.0);
			glVertex3f(x22, y22, 0.0 + h);
			glVertex3f(x2, y2, 0.0 + h);

			glEnd();

		}





		{
			kolo2(0, 0, 0, 1, 1, 360);
			kolo2(0, 0, 1, 1, 1, 360);
		}

	}
	glTranslatef(0, 0, 0);
	sfera(5, 12, 15);
	{	glRotated(50, 1, 0, 0);
	glTranslatef(0, -0.2, 0);
	noga(0, 0, 0, 1, 2.5, 10);
	}
	{	glRotated(240, 1, 0, 0);
	glTranslatef(0, -0.2, 0);
	noga(0, 0, 0, 1, 2.5, 10);
	}

}




void moje_kolo(GLfloat a, GLfloat b, GLfloat c, float R)
{
	double x, y, z;


	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (float i = 0; i <= 200 * GL_PI*R; i++)
	{

		x = R*cos(i);
		z = R*sin(i);

		glVertex3f(x, 0, z);
	}
	glEnd();

}







void krazownik(void)
{
	//glPolygonMode(GL_FILL, GL_LINES);
	glBegin(GL_TRIANGLE_STRIP);
	GLfloat s[] = { 0, 0, 0 };
	GLfloat b[] = { 0, 1, 0 };
	GLfloat c[] = { 1.0f, 1.0f, 0 };
	GLfloat d[] = { 1.0f, -1.0f, 0 };
	glColor3f(255.0f, 0.0f, 0.0f);
	//GLfloat punktA[] = { 0, 0, 0 };

	for (int i = 0; i <= 20; ++i)
		for (int j = 0; j < 23; j++)
		{
			glFrontFace(GL_CW);


			glVertex2f(s[0] + i, s[1] + i + j);
			glVertex2f(b[1] + j, b[1] + j);
			glVertex2f(c[1] + i + j, c[1] + j);
			glEnd();
		}


	//walec2(6, 2, 1, 3);
	//czesc(4, 4, 5, 6);
	//	czesc(0.3, 0.5, 2, 8);

	//glVertex3fv(0, 0, 0);
}

void rotacja(void)
{
	glTranslatef(5, 5, 5);
	glRotatef(90, 1, 0, 0);
	szescian_radka();

}

void tlo(void)
{

	glBegin(GL_QUADS);

	glTexCoord3f(0, 0, 0);
	glVertex3f(0,0,0);
	

	glTexCoord2f(0, 1);
	glVertex3f(1000, 0,0);
	
	
	glTexCoord3f(1, 1,0);
	glVertex3f(1000, 0,0);
	
	glTexCoord3f(1, 0,0);
	glVertex3f(0, 1000,1000);
	
	glEnd();

}
void prostokatZTrojkatow(void) {
	GLfloat sa[2] = { 0.0f, 0.0f };
	GLfloat sb[2] = { 0.0f, 10.0f };
	GLfloat sc[2] = { 0.0f, 0.0f };
	GLfloat sd[2] = { 0.0f, 10.0f };


	//GLfloat sa[2] = { 0.0f, 0.0f };
	//GLfloat sb[2] = { 0.0f, 10.0f };
	//GLfloat sc[2] = { 10.0f, 0.0f };
	//GLfloat sd[2] = { 10.0f, 10.0f };

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //, GL_LINE)
	{
		glFrontFace(GL_CW);
		for (int y = 0; y < 20; y += 10) {
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(255.f, 0.f, 0.f);
			for (int x = 0; x < 30; x += 10) {

				glVertex2f(sa[0] + x, sa[1] + y);
				glVertex2f(sb[0] + x, sb[1] + y);
				glVertex2f(sc[0] + x, sc[1] + y);
				glVertex2f(sd[0] + x, sd[1] + y);

			}
			glEnd();
		}

	}
}





void szescian4(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		// Parametry wierzcholkow
		double alfa = GL_PI / 4;
		GLfloat sa[3] = { 0.0f, 0.0f, 0.0f };
		GLfloat sb[3] = { 10.0f, 0.0f, 0.0f };
		GLfloat sc[3] = { 10.0f, 10.0f, 0.0f };
		GLfloat sd[3] = { 0.0f, 10.0f, 0.0f };
		GLfloat se[3] = { 0.0f, 0.0f, -10.0f };
		GLfloat sf[3] = { 10.0f, 0.0f, -10.0f };
		GLfloat sg[3] = { 10.0f, 10.0f, -10.0f };
		GLfloat sh[3] = { 0.0f, 10.0f, -10.0f };

		GLfloat na[3] = { 0.0f, 10.0f, 0.0f };
		GLfloat nb[3] = { 10.0f, 10.0f, 0.0f };
		GLfloat nc[3] = { 10.f, 10 + 10 * sin(alfa), -10 * cos(alfa) };
		GLfloat nd[3] = { 0.f, 10 + 10 * sin(alfa), -10 * cos(alfa) };


		// Sciany skladowe
		glColor3f(1.0f, 0.0f, 0.0f);



		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
		glEnd();

		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
		glEnd();


		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(na);
		glVertex3fv(nb);
		glVertex3fv(nc);
		glVertex3fv(nd);
		glEnd();

	}
}


void noga2(int ACC, GLfloat wysokosc)
{



	float a, p, q;
	int i;

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= ACC; i++)
	{
		a = i*PI * 2 / ACC;
		p = cos(a);
		q = sin(a);
		glNormal3f(p, q, 0.4);
		glVertex3f(0.7*p, 0.7*q, 0.8);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0.7*p, 0.7*q, wysokosc);
	}
	glEnd();
}

void tabletka()
{

	walec2(3, 3, 3, 3);
	sfera(4, 3, 10);

}


void budujSzescian(int i)
{
	int x, y, z;

	for (z = 0; z<i; z++)
	{
		for (y = 0; y<i; y++)
		{
			for (x = 0; x<i; x++) buduj(x, y, z);
		}
	}
}
void kolo_goscia(float h)
{

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 300; i++){
		double angle = 2 * PI * i / 300;
		double x = cos(angle)*h;
		double y = sin(angle)*h;


		glVertex2d(x, y);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	glDisable(GL_TEXTURE_2D);
	glEnd();
	
}
void Disk(GLdouble innerRadius, GLdouble outerRadius)
{
	GLUquadricObj* obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluDisk(obj, innerRadius, outerRadius, 25, 25);
}

void kula(GLdouble zewn, GLfloat wewn, GLfloat czesci)
{
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, zewn, wewn, czesci);


}


void bezier()
{

	glBegin(GL_LINE_STRIP);
	glPointSize(10.0);
	glColor3f(1, 0, 0); //tu bedzie antenka
	glVertex3f(0.0f, 0.0f, -3.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);




	glEnd();

}


void kula3d()
{
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glEnable(GL_TEXTURE_2D);

	
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glEnable(GL_TEXTURE_2D);

	glColor3f(0, 0, 1);
	moja_sfera(30, 30, 30, 1);

	{
		////////////////////////////////////kula3d();
		glRotatef(180, 1, 0, 0);
		glTranslatef(0, 0, 0.02);
		moja_sfera(30, 30, 30, 1);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);

	}

	glDisable(GL_TEXTURE_2D);

}



//podwozie()
//{
//	walec2(2, 6, 6, 1);
//	glRotatef(90, 1, 0, 0);
//	moje_kolo(0, 0, 0, 5.5);
//	glTranslatef( 0, 0.2, 0.2);
//	moje_kolo(0, 0, 0, 6.5);
//
//}



//ufo()
//{
//	podwozie();
//}


void czesc(float r1, float r2, float h, int krok)
{
	
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glEnable(GL_TEXTURE_2D);
	int i = 0;
	GLfloat x1, y1, x11, y11, x2, y2, x22, y22, rad;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		for (i = 0; i <= 360; i += krok)
		{
			glBegin(GL_POLYGON);

			//Dolna podstawa
			x1 = r1*sin(radiany(i));
			y1 = r1*cos(radiany(i));
			x11 = r1*sin(radiany(i + krok));
			y11 = r1*cos(radiany(i + krok));

			//Górna podstawa
			x2 = r2*sin(radiany(i));
			y2 = r2*cos(radiany(i));
			x22 = r2*sin(radiany(i + krok));
			y22 = r2*cos(radiany(i + krok));

		//	glTexCoord3f(x1, y1, 0.0);
			glVertex3f(x1, y1, 0.0);

		//	glTexCoord3f(x11, y11, 0.0);
			glVertex3f(x11, y11, 0.0);

		//	glTexCoord3f(x22, y22, 0.0);
			glVertex3f(x22, y22, 0.0 + h);

		//	glTexCoord3f(x2, y2, 0.0);
			glVertex3f(x2, y2, 0.0 + h);

			glEnd();
		}
	
		
		glBegin(GL_POLYGON);
		for (i = 0; i <= 360; i += krok)
		{
			x1 = r1*sin(radiany(i));
			y1 = r1*cos(radiany(i));
		//	glTexCoord2f(x1, y1);
			glVertex3f(x1, y1, 0.0);
		
		}
		glEnd();

		glBegin(GL_POLYGON);
		for (i = 0; i <= 360; i += krok)
		{
			x2 = r2*sin(radiany(i));
			y2 = r2*cos(radiany(i));
		//	glVertex3f(x2, y2, 0.0 + h);
			glTexCoord2f(x2, y2);
		}
		glEnd();
	}
	
}



void rysuj_mgle()
{


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);          // ustawia kolor defaultowy jako kolor mgly

	glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode  GL_EXP, GL_EXP2, GL_LINEAR 
	glFogfv(GL_FOG_COLOR, fogColor);            // Kolor mgly
	glFogf(GL_FOG_DENSITY, 0.35f);              // Przezroczystosc
	glHint(GL_FOG_HINT, GL_DONT_CARE);          // czort
	glFogf(GL_FOG_START, 0.0f);             // start
	glFogf(GL_FOG_END, 1025.0f);               // koniec
	glEnable(GL_FOG);                   // wlacza mgle
}


void pen()
{
	//{0 0 0 
	//0  0 10
	//10 0 10
	//0 10 0
//	glRotatef(276, 1, 0, 1);
	//glEnable(GL_TEXTURE_2D);
	//szescian_radka();
	//glDisable(GL_TEXTURE_2D);
	glPushMatrix();


	glScalef(0.5, 0.5, 0.5);
	GLfloat light_ainbient[] = { 1.0, 1.0, 1.0, 1.0 };
	//glLightifv(GL_LIGHT7, GL_SPECULAR, light_aibient);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light_position1[] = { gl_przesun_x, gl_przesun_y, gl_przesun_z,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT7);
	glRotatef(180, 0, 0, 1);



	{
		glPushMatrix();
		glTranslatef(0, 2.5, -5);
		glRotatef(180, 1, 0, 1); //wielkie szyszko fidzace oko

		kolo_goscia(0.5);


		glPopMatrix();
	}

{
	glPushMatrix();
	glTranslatef(-2, 0, -3.5);
	//glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, texture[2]);

	kula3d();
	glTranslatef(2, 4, 0);
	kula3d();                    //- na y to w dol,
	glTranslatef(4, -2, 0);
	kula3d();
	glTranslatef(4, -1, 0);
	kula3d();
	glTranslatef(4, 3, 0);
	kula3d(); //dotoad ok
	glTranslatef(0, -5, 0);
	kula3d();
	glTranslatef(-2, 4, 0);
	kula3d();
	glTranslatef(-4, -2, 0);
	kula3d();
	glTranslatef(-4, 0, 0);
	kula3d();
	glTranslatef(-4, 4, 0);
	kula3d();
	//glDisable(GL_TEXTURE_2D);






	glPopMatrix();
}


//lądowanie na jakiejś planecie




	{
		glPushMatrix();
		glTranslatef(0, 0, -5);
		glTranslatef(5, 2.5, 0);
		glRotatef(180, 1, 0, 1);//wielkie szyszko fidzace oko
		kolo_goscia(0.5);
		glPopMatrix();
	}






	{

		glScalef(0.8, 0.8, 0.8);
		//	kula(10, 50,10);              //SKALOWANIE KAMERY
		glTranslatef(6, 2, -3);

	}



	{
		glPushMatrix();
		glTranslatef(0, 0, -5);

		glPopMatrix();
	}
	{	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
		walec2(1, 6, 10, 5);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		kula(5, 6, 12);     //dolny kadlub statku (podwozie)
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		walec2(0.5, 8, 12, 5);
		walec2(0.25, 10, 12, 5);
		walec2(0.15, 11, 13, 5);

		//1 6 4 5
	



		kolo_goscia(13);    //kolo pierwsze przykrywka do odwroconej miski
		kolo_goscia(6);     //kolejne kolka
		kolo_goscia(7);
		kolo_goscia(8);
		kolo_goscia(10);
		kolo_goscia(13);


		glDisable(GL_TEXTURE_2D);


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glPushMatrix();
		glTranslatef(0, 0, 0.75);
		glScalef(1.5, 1.5, 1.5);
		sfera(22, 26, 25);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

	}


	if (schowaj==1)
	{
		glPushMatrix();
		glScaled(0.5, 0.5, 0.5);
		glTranslatef(5, 0, 3);    ///7 0 3
		glRotatef(45, 1, 1, 0);      //noga 1
		nogaufo();
		kolo_goscia(3);
		glPopMatrix();

	}

	if (schowaj == 1)
	{
		glPushMatrix();

		glScaled(0.5, 0.5, 0.5);
		glTranslatef(-5, 0, 3);   //noga2
		glRotatef(-45, 1, 1, 0);
		nogaufo();
		kolo_goscia(3);
		glPopMatrix();
	}
	if (schowaj == 1)
	{
		glPushMatrix();

		glScaled(0.5, 0.5, 0.5);
		glTranslatef(-0, 5, 3);
		glRotatef(-45, 1, 0, 1);
		nogaufo();
		kolo_goscia(3);
		glPopMatrix();
	}




	if (schowaj == 1)
	{
		glPushMatrix();
		glScaled(0.5, 0.5, 0.5);
		glTranslatef(0, -5, 3);
		glRotatef(45, 1, 0, 1);
		nogaufo();  //nozka
		kolo_goscia(3); //kolo przy nozce
		glPopMatrix();
	}

	if (schowaj == 1)
	{
		glPushMatrix();

		glScaled(0.5, 0.5, 0.5);
		glTranslatef(-5, -5, 3);
		glRotatef(-45, 0, 1, 1);
		nogaufo();   //nozka
		kolo_goscia(3);  //kolo przy nozce
		glPopMatrix();
	}




	{
		//1 6 4 5
		kolo_goscia(6); //mozna wywalic niewidac
	
		glPushMatrix();
		glRotatef(180, 1, 1, 0);
		glScalef(1.5, 1.5, 1.5);
		glTranslatef(0, 0, -0.5);
		sfera(22, 26, 25);  //spod statku
		glPopMatrix();
		

	}

	{	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
	
		glColor3d(0, 1, 0);
		glPushMatrix();
		glScalef(3, 3, 3);
		sfera(30, 30, 30);   //sfera u gory 
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);



	}



	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glPushMatrix();
		glScalef(1.5, 1.5, 1.5);
		glTranslatef(0, 0, -2.5);
		glPushAttrib(GL_CURRENT_BIT);
		glColor3d(1, 0, 0);
		sfera(30, 30, 30);
		walec2(1, 4, 3, 1);
		glRotatef(180, 1, 0, 0);
		glPopAttrib();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	///daszek


	{

		glPushMatrix();
	//	glScalef(0.4, 0.4, 0.4);
		//glTranslatef(0, 0, -34);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glEnable(GL_TEXTURE_2D);
		czesc(1, 4, 0.8, 1);
		glPopMatrix();
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}






}



void rysuj(void)
{
	
	
		glPushMatrix();
		glTranslatef(gl_przesun_x, 0, 0);
		pen();
		glPopMatrix();
		
}

void ksionzyc(float radius)
{
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glEnable(GL_TEXTURE_2D);
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric, radius,30,30);






		//glDisable(GL_TEXTURE_GEN_S);
	//	glDisable(GL_TEXTURE_GEN_T);



	glDisable(GL_TEXTURE_2D);

}

void obsluga_klawiatury(unsigned char key,int x, int y)
{
	switch (key){
	case 'w':
		glTranslatef(1.0, 0.0, 0.0);
		pen();
		break;

	case 'r':
		glTranslatef(0.0, 1.0, 0.0);
		glClearColor(0.0, 1.0, 0.0, 0.0);
		break;

	default:
		break;
	}
	glutPostRedisplay(); //request display() call ASAP
}


void mgla(unsigned char key)
{

	if (keys['G'] && !gp)                   // Is The G Key Being Pressed?
	{
		gp = TRUE;                    // gp Is Set To TRUE
		fogfilter += 1;                   // Increase fogfilter By One
		if (fogfilter>2)             // Is fogfilter Greater Than 2?
		{
			fogfilter = 0;                // If So, Set fogfilter To Zero
		}
		glFogi(GL_FOG_MODE, fogMode[fogfilter]);   // Fog Mode
	}
	if (!keys['G'])                     // Has The G Key Been Released?
	{
		gp = FALSE;                   // If So, gp Is Set To FALSE
	}
}
void zmiana_kamery()
{
	if (xRuch)
	{
		xKamera += xRuch*szybkosc_kamery;
		xlKamera += xRuch*szybkosc_kamery;
	}

	if(yRuch)
	{
		yKamera += yRuch*szybkosc_kamery;
		ylKamera += yRuch*szybkosc_kamery;
	}

	if(xRuch)
	{
		zKamera += zRuch*szybkosc_kamery;
		zlKamera += zRuch*szybkosc_kamery;
	}

}

void Camera()
{
	glPushMatrix();
	glTranslatef(k, 0, 0);
	pen();
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sprawdz(float i)
{
	if (i >= 359)
		i = 0;
}

void animacja(int a)
{
	
	GLfloat posx=0, posy=0, posz = 0;
	GLfloat delta=1;
	glPushMatrix();
	glTranslatef(posx, posy, posz);
	ksionzyc(15);
	//glPopMatrix();
	posx += delta;
	if (posx >= 100 || posx <= 0)
	{
		delta = -delta;
	}
	glutTimerFunc(25, animacja, 0);
}
void animacja2()
{
	unsigned int milisekunda=300;
	double kat = 0;
	if (double kat = 0)
	{

		for (float i = 0; i < 360; i++)
		{

			GLfloat x = 5*cos(i);
			GLfloat z = 5*sin(i);
			sleepcp(2000);
			glPushMatrix();
			glTranslatef(x, 0, z);
			ksionzyc(25);
			glPopMatrix();
			sprawdz(i);
	
		
				
		
		}
		
	}
}

float potega(float podstawa, float wykladnik)
{
	int wynik = 1;

	for (int i = 0; i<wykladnik; i++)
		wynik *= podstawa;

	return wynik;
}

void CheckRot()
{
	if (sunrev>360.0)
		sunrev -= 360.0;
	if (sunrev<0.0)
		sunrev += 360.0;
}


void animate(void)
{
	sunrev += delsunrev;
	CheckRot();
	glutPostRedisplay();
}
void wykrywanie_kolizji()
{
	float Ax=potega((30 - abs(gl_przesun_x)), 2);
	float Ay = potega((30 - abs(gl_przesun_y)), 2);
	float Az = potega((40 - abs(gl_przesun_z)), 2);
	float rad = pow((50 + 13), 2);
	if ((Ax + Ay + Az) < rad)
	{
		kolizja = TRUE;
	}
	if ((Ax + Ay + Az) > rad)
	{
		kolizja = FALSE;
	}
}
void TW_CALL Callback(void *clientData)
{
	// do something
}

void obliczpoz()
{
	if (kat_obrotu >= 360) kat_obrotu = 360;
	if (kat_obrotu <= 0) kat_obrotu = 0;
	postx =5* sin(kat_obrotu);
	posty =5* cos(kat_obrotu);
}
//void tweakbar()
//{
//	TwBar *myBar=TwNewBar("OGLDEV");
//	myBar = TwNewBar("NameOfMyTweakBar");
//	TwAddVarRW(myBar, "NameOfMyVariable", TW_TYPE_FLOAT, &gl_przesun_x, NULL);
//}
//******************************************************** 
//  Glowna funkcja WINDOWS
//******************************************************** 

int WINAPI WinMain (HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
                    LPSTR lpszCmdLine,
					int nCmdShow)
{
    static char szAppName[] = "OpenGL";                    
    static char szTitle[]=    "SZESCIAN"; // Nazwa okna
    WNDCLASS wc;   // zmienna klasy okna
    MSG      msg;  // zmienna komunikatu 
    HWND     hWnd; // uchwyt okna

    // wypelnianie klasy okna 

    wc.style         =
        CS_HREDRAW | CS_VREDRAW;// styl okna
    wc.lpfnWndProc   = 
        (WNDPROC)WndProc;       // procedura okna
    wc.cbClsExtra    = 0;       // dodatkowe dane
    wc.cbWndExtra    = 0;       
    wc.hInstance     =
        hInstance;              // instancja 
    wc.hIcon         = NULL;    // nazwa ikony 
    wc.hCursor       =
        LoadCursor(NULL, IDC_ARROW);// kursor
    wc.hbrBackground = 
        (HBRUSH)(COLOR_WINDOW+1);// domyslny kolor okna
    wc.lpszMenuName  = NULL;     
    wc.lpszClassName =
        szAppName;               // nazwa klasy

    // Rejestracja klasy okna

    RegisterClass( &wc );
  
    // Konstrukcja glownego okna 

    hWnd = CreateWindow(
                szAppName, // app name
                szTitle,   // Text for window title bar
                WS_OVERLAPPEDWINDOW// Window style 
                  // NEED THESE for OpenGL calls to work!
                 | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
                NULL,     // no parent window
                NULL,     // Use the window class menu.
                hInstance,// This instance owns this window
                NULL      // We don't use any extra data
        );

    // Jezeli okno nie zostanie utworzone, zwrot 0
    if ( !hWnd )
        {
        return( 0 );
        }

    
	ShowWindow( hWnd, nCmdShow );// Wyswietlanie okna
    UpdateWindow( hWnd );        // Aktualizacja okna

    // Uruchiomienie petli komunikatow
    while (GetMessage(&msg, NULL, 0, 0)) 
	{
        TranslateMessage( &msg ); // Przetwarzanie wiadomosci
        DispatchMessage( &msg );  // Zwolnienie wiadomosci
    }

    return( msg.wParam ); 
}


//******************************************************** 
//    Procedura okna
//******************************************************** 
 
LONG WINAPI WndProc(HWND hWnd,
					UINT msg,
                    WPARAM wParam,
					LPARAM lParam)
{
    HDC hDC;

    static HGLRC hRC; // Note this is STATIC!
    
	PAINTSTRUCT ps;

    GLdouble gldAspect;

    GLsizei glnWidth, glnHeight;

	float change;


    // Petla komunikatow 
	
	switch (msg)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);

		// Select the pixel format
		SetDCPixelFormat(hDC);

		// Create palette if needed
		hPalette = GetOpenGLPalette(hDC);

		// Create the rendering context and make it current
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		SetupRC();
		TwInit(TW_OPENGL, NULL);
		TwWindowSize(800,600);
		myBar = TwNewBar("Interfejs");
		
		TwAddVarRW(myBar, "gl_pozycja-x", TW_TYPE_FLOAT, &gl_przesun_x, "");
		TwAddVarRW(myBar, "gl_pozycja-y", TW_TYPE_FLOAT, &gl_przesun_y, "");
		TwAddVarRW(myBar, "gl_przesun-z", TW_TYPE_FLOAT, &gl_przesun_z, "");
		TwAddVarRW(myBar, "Kolizja", TW_TYPE_BOOLCPP, &kolizja, "");
		TwAddButton(myBar, "przycisk - W", Callback, NULL, " 'W' ");
	
	
		//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);          // ustawia kolor defaultowy jako kolor mgly

		glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
		glFogfv(GL_FOG_COLOR, fogColor);            // Kolor mgly
		glFogf(GL_FOG_DENSITY, 0.002f);              // Przezroczystosc
		glHint(GL_FOG_HINT, GL_DONT_CARE);          // jakas wartosc czort wie
		glFogf(GL_FOG_START, 0.0f);             // start
		glFogf(GL_FOG_END, 100.0f);               // koniec
	//glEnable(GL_FOG);                   // wlacza mgle
	//	return 0;
		glGenTextures(10, &texture[0]);                  // tworzy obiekt tekstury			

		// ³aduje pierwszy obraz tekstury:
		bitmapData = LoadBitmapFile("Bitmapy//szklo.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[0]);       // aktywuje obiekt tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);

		bitmapData = LoadBitmapFile("Bitmapy//v3k.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[1]);       // aktywuje obiekt tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);
		// ustalenie sposobu mieszania tekstury z t³em
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		bitmapData = LoadBitmapFile("Bitmapy//szklo.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[2]);       // aktywuje obiekt tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);

		bitmapData = LoadBitmapFile("Bitmapy//tek4.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[3]);       // aktywuje obiekt tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);

		bitmapData = LoadBitmapFile("Bitmapy//aaa.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[4]);       // aktywuje obiekt tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);


		bitmapData = LoadBitmapFile("Bitmapy//tex7.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[5]);       // aktywuje obiekt tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);


		bitmapData = LoadBitmapFile("Bitmapy//mipmap.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[6]);       // aktywuje obiekt tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    ///podspodem  lśnienie
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);



		bitmapData = LoadBitmapFile("Bitmapy//outer-space.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[7]);       //and use the texture, we have just generated
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //same if the image bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);      //we 

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);


		bitmapData = LoadBitmapFile("Bitmapy//right.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[8]);       //and use the texture, we have just generated
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //same if the image bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);      //we 

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);

		bitmapData = LoadBitmapFile("Bitmapy//mooon.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[9]);       //and use the texture, we have just generated
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //same if the image bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);      //we 

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		if (bitmapData)
			free(bitmapData);
		// ustalenie sposobu mieszania tekstury z t³em
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		//TwInit(TW_OPENGL_CORE, NULL);
		//TwWindowSize(glnWidth, glnHeight);
		return 0;
	case WM_SIZE:
		hDC = GetDC(hWnd);			// Kontekst urzadzenia
		wglMakeCurrent(hDC, hRC);

		// Usawienie rozmiarow okna graficznego

		glnWidth = (GLsizei)LOWORD(lParam);
		glnHeight = (GLsizei)HIWORD(lParam);

		// Aspekt DC
		gldAspect = (GLdouble)glnWidth / (GLdouble)glnHeight;

		glMatrixMode(GL_PROJECTION);// Ustawienie macierzy projekcji

		glLoadIdentity();

		// Rodzaj transformacji ekranowej
		gluPerspective(
			30.0,      // kat 
			gldAspect, // aspekt
			1.0,       // polozenie plaszczyzny blizszej
			1000.0);  // polozenie plaszczyzny dalszej

		glViewport(0, 0, glnWidth, glnHeight);

		// czyszczenie
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		glEnable(GL_COLOR_MATERIAL);
		wglMakeCurrent(NULL, NULL);
		ReleaseDC(hWnd, hDC);
		return 0;

	case WM_PAINT:
		// rysowanie sceny

		hDC = BeginPaint(hWnd, &ps);
		wglMakeCurrent(hDC, hRC);

		DrawOpenGLScene();

		SwapBuffers(hDC);

		wglMakeCurrent(NULL, NULL);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		// zamykanie 
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN: //************ OBSLUGA KLAWISZY ***********************
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
		
		change = 1.0f;
	
	}
			else
				change=0.1f;

		switch ((int)wParam)
		{
		case VK_SPACE:
			if (k == 1) k = 0;
			else if (k == 0) k = 1;
			PostMessage(hWnd, WM_PAINT, 0, 0); ///tylko po to aby wyrysowac ponownie okno xD
			break;

		case VK_NUMPAD0:
			pivot_vert_angle += 5;
			if (pivot_vert_angle >= 360)
				pivot_vert_angle -= 360;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case VK_NUMPAD1:
		{
			pivot_vert_angle -= 5;
			if (pivot_vert_angle < 0)
				pivot_vert_angle += 360;
			InvalidateRect(hWnd, NULL, FALSE);
		}break;
		case VK_UP:
		{
			wykrywanie_kolizji();

			if (kolizja != TRUE)
			{
				gl_przesun_y -= 1;
			}
			else
			{
				gl_przesun_y += 2;
			}

		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

		case VK_TAB:
			vek_x += 1;
			break;
		case VK_F2:
			vek_x -= 1;
			break;
		case VK_F3:
			vek_y += 1;
			break;
		case VK_F4:
			vek_y -= 1;
			break;
		case VK_F5:
			vek_z += 1;
			break;
		case VK_F6:
			vek_z -= 1;
			break;
		case VK_DOWN:
		{
			
				wykrywanie_kolizji();

				if (kolizja != TRUE)
				{
					gl_przesun_y += 1;
				}
				else
				{
					gl_przesun_y -= 2;
				}
			


			///-120, -30, 40
			//-120 to jest w dwie strony po 50 bo radius ma 50 -70<= >=-170
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;


		case  VK_RIGHT:
		{kat_obrotu -= 1;
			wykrywanie_kolizji();
			

				if (kolizja != TRUE)

				{
					gl_przesun_x -= 1;
				}
				else
					gl_przesun_x += 2;

			
		}

		InvalidateRect(hWnd, NULL, FALSE);


		break;


		case VK_LEFT:
		{kat_obrotu += 1;
			void TW_CALL Callback(void *clientData);

			if (kolizja != TRUE)
			{
				gl_przesun_x += 1;
			}
			else
			{

				gl_przesun_x -= 2;
			}
			

		}
		
			InvalidateRect(hWnd, NULL, FALSE);

		break;

		// obrot w poziomie
		case VK_F7:
			pivot_horiz_angle += 5;
			if (pivot_horiz_angle >= 360)
				pivot_horiz_angle -= 360;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case VK_F8:
			pivot_horiz_angle -= 5;
			if (pivot_horiz_angle < 0)
				pivot_horiz_angle += 360;
			InvalidateRect(hWnd, NULL, FALSE);
			break;

			// przesuniecia w poziomie



		case VK_CONTROL:
		{
			if (kolizja != TRUE)

			{
				gl_przesun_z -= 1;
			}
			else gl_przesun_z += 2;


		}

		InvalidateRect(hWnd, NULL, FALSE);


		break;

		case VK_SHIFT:
		{

			if (kolizja != TRUE)
				gl_przesun_z += 1;


		}

		InvalidateRect(hWnd, NULL, FALSE);


		break;


		case VK_NEXT:
			if ((pivot_x + change) < 400)
				pivot_x += change;
			InvalidateRect(hWnd, NULL, FALSE);

			break;
		case VK_DELETE:
			if ((pivot_x - change) > -400)
				pivot_x -= change;
			InvalidateRect(hWnd, NULL, FALSE);
			break;

			// przesuniecia w pionie
		case VK_F12:
			if (schowaj == 1) {schowaj = 0;
		}
		else schowaj = 1;
		break;
				case VK_HOME:
					if ((pivot_y+change)<400)
						pivot_y+=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case VK_END:
					if ((pivot_y-change)>-400)
						pivot_y-=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;

				// odleglosc
				case VK_INSERT:
					if ((z_dist+change)<600)
						z_dist+=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case VK_PRIOR:
					if ((z_dist-change)>1)
						z_dist-=change;
					InvalidateRect(hWnd, NULL, FALSE);
					break;

				// wyjscie z programu
				case VK_ESCAPE:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					return 0;
			}
        }

    
    return DefWindowProc( hWnd, msg, wParam, lParam );
}



//*******************************************************
//  Uruchomienie OpenGL w srodowisku Windows wymaga 
//  wlaczenie trybu pikselowego oraz ustawienia 
//  kontekstu renderowania
//*******************************************************

HGLRC SetUpOpenGL( HWND hWnd )
{
    static PIXELFORMATDESCRIPTOR pfd =
	{
        sizeof (PIXELFORMATDESCRIPTOR), // rozmiar struktury 
        1,                              // numer wersji
        PFD_DRAW_TO_WINDOW |            // flaga rysowania w oknie,
            PFD_SUPPORT_OPENGL |        // uzycie OpenGL
		    PFD_DOUBLEBUFFER,	        // uzycie podwojnego buforowania
        PFD_TYPE_RGBA,                  // model kolorow - RGBA 
        24,                             // kolor 24-bitowy
        0, 0, 0,                        
        0, 0, 0,                        // trezerwa
        0, 0,                           // brak bufora alpha 
        0, 0, 0, 0, 0,                  // brak bufora akumulacji
        32,                             // bufor glebokosci 32-bitowy
        0,                              // brak bufora szablonu
        0,                              // brak bufora pomocniczego
        PFD_MAIN_PLANE,					// warstwa
        0,                              // rezerwa - 0 
        0,                              // maska
        0,                              // maska widoczna
        0                               // maska bledow
    };

	// zmienne
    int nMyPixelFormatID;

    HDC hDC;
    
	HGLRC hRC;

    hDC = GetDC( hWnd );
    
	// Inicjalizacja trybu pikselowego 

	nMyPixelFormatID = ChoosePixelFormat( hDC, &pfd );
    SetPixelFormat( hDC, nMyPixelFormatID, &pfd );
	
	// Inicjalizacja kontekstu renderowania
    
	hRC = wglCreateContext( hDC );
    ReleaseDC( hWnd, hDC );

    return hRC;
}

void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  

	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  

	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}

//******************************************************** 
//  Glowna funkcja rysujaca.
//******************************************************** 

void DrawOpenGLScene( )
{
	GLfloat position[4]={10.0f, 10.0, 100.0f, 0.0f};
    
	// flagi czynnosci pomocniczych

    glEnable( GL_DEPTH_TEST );
    
	// czyszczenie buforow
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);

	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);
	
	// wlaczenie oswietlenia
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

    
    // transformacja obserwacji
    //normalnie jest     glMatrixMode( GL_MODELVIEW );
	glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //0 -1 0     //pos kamery -30 -20 -50
   gluLookAt(gl_przesun_x - 30, gl_przesun_y-20 , gl_przesun_z - 50, gl_przesun_x, gl_przesun_y, gl_przesun_z, vek_x, vek_y, vek_z);
  // glTranslatef(30, 0, -30);
   glRotatef(pivot_horiz_angle,1, 0, 0);
   animacja2();
  drawSkybox(500);



  glPushMatrix();
  glTranslatef(30, 30, 40);
  ksionzyc(50);

 glPopMatrix();

  
    // umiejscowienie kamery w odleglym miejscu
  //	glTranslatef( pivot_x, pivot_y, -z_dist );

  //tweakbar();
  
	//glPushMatrix();
	glRotatef(pivot_vert_angle, 1, 0, 0);
	glTranslatef(gl_przesun_x, gl_przesun_y, gl_przesun_z);
	glRotatef(270, 1, 0, 0);
	pen();


		//////tu rysujesz

//glViewport(1, 50, 1366, 768);
//	uklad_xyz();

//	rysuj();
	//rotacja();
	//glPopMatrix();
	//glTranslatef(gl_przesun_x,0,0);
	//pen();
//	rysuj_mgle();
	//animacja(4);
	TwDraw();


    glFlush ();

}
///glOtto();
//gluLookat();

// ZROBIC KAMERE I PORUSZANIE OBIEKTU WRAZ Z OPADANIEM TAK JAKBY MIAL JAKIES PALIWO KTORE SIE KONCZY I LADOWANIE NA PLANECIE.