#include <iostream>
#include "Renderer.h"
#include "Ray.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

using namespace std;

int main(int argc, char* argv[])
{
	//std::cout << sizeof(ray_t);

	std::cout << "Hello World!";
	seedRandom((unsigned int)time(nullptr));

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray-Tracing", 1280, 720);

	Canvas canvas(1280, 720, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene(20); // sky color could be set with the top and bottom color

	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		//std::shared_ptr<Material> material = (<use rand() and %to randomly pick the material>) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-1, 1), random(-1, 1), random(-1, -5) }, random01(), material);
		scene.AddObject(std::move(sphere));
	}



	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, 10);
	canvas.Update();

	bool quit = false;
	while (!quit)
	{
		//canvas.Clear({ 0, 0, 0, 1 });
		//for (int i = 0; i < 10000; i++)
		//{
		//	canvas.DrawPoint({ random(0, canvas.GetSize().x), random(0, canvas.GetSize().y) }, { random01(), random01(), random01(), 1 });

		//}

		//canvas.Update();

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

		renderer.PresentCanvas(canvas);
	}
	renderer.Shutdown();

	return 0;
}