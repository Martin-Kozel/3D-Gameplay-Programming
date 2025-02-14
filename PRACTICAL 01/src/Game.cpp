#include <./include/Game.h>

bool updatable = false;

gpp::Vector3 v3;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Bottom Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(v3.getX(), 1.0f, -5.0f); // top right
		glVertex3f(-1.0f, 1.0f, -5.0f); // top left
		glVertex3f(-1.0f, -1.0f, -5.0f); // bottom left
		glVertex3f(1.0f, -1.0f, -5.0f); // bottom right

		//Top Face
		glColor3f(5.0f, 1.0f, 0.0f); 
		glVertex3f(1.0f, 1.0f, -15.0f); // top right
		glVertex3f(-1.0f, 1.0f, -15.0f); // top left
		glVertex3f(-1.0f, -1.0f, -15.0f); // bottom left
		glVertex3f(1.0f, -1.0f, -15.0f); // bottom right

		glColor3f(1.0f, 0.5f, 1.0f);
		glVertex3f(1.0f, 1.0f, -5.0f);
		glVertex3f(1.0f, 1.0f, -15.0f); 
		glVertex3f(1.0f, -1.0f, -15.0f);
		glVertex3f(1.0f, -1.0f, -5.0f); 

		glColor3f(0.5f, 0.5f, 1.0f);
		glVertex3f(1.0f, -1.0f, -15.0f);
		glVertex3f(-1.0f, -1.0f, -15.0f); 
		glVertex3f(-1.0f, -1.0f, -5.0f);
		glVertex3f(1.0f, -1.0f, -5.0f); 

		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-1.0f, 1.0f, -15.0f);
		glVertex3f(-1.0f, 1.0f, -5.0f); 
		glVertex3f(-1.0f, -1.0f, -5.0f);
		glVertex3f(-1.0f, -1.0f, -15.0f);

		glColor3f(1.0f, 0.5f, 0.5f);
		glVertex3f(1.0f, 1.0f, -5.0f);
		glVertex3f(1.0f, 1.0f, -15.0f); 
		glVertex3f(-1.0f, 1.0f, -15.0f);
		glVertex3f(-1.0f, 1.0f, -5.0f);  

		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	if (updatable)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
	
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	glLoadIdentity();
	glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Z Axis

	glCallList(1);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

