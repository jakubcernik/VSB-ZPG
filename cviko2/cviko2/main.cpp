#include "Application.h"

int main(void)
{
	Application app;
	
	app.initialization();

	app.createShaders();
	app.createModels();
	app.run();
}