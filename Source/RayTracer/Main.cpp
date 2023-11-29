#include <iostream>
#include "Renderer.h"
#include "Ray.h"
#include "Random.h"
#include "Canvas.h"

using namespace std;

int main(int argc, char* argv[])
{
	//std::cout << sizeof(ray_t);

	std::cout << "Hello World!";
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray-Tracing", 400, 300);

	Canvas canvas(400, 300, renderer);

	bool quit = false;
	while (!quit)
	{
		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 10000; i++)
		{
			canvas.DrawPoint({ random(0, canvas.GetSize().x), random(0, canvas.GetSize().y) }, { random01(), random01(), random01(), 1 });

		}
		canvas.Update();
		renderer.PresentCanvas(canvas);

		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}

		
	}
	renderer.Shutdown();

	return 0;
}