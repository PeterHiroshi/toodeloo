#include "../common.hpp"

namespace Toodeloo
{
	namespace States
	{
		Gameplay::Gameplay(Engine& engine)
			: Toodeloo::States::State(engine),
			  _player(Toodeloo::Player(*this)),
			  _map(*this, "map.txt"),
			  _heightmap("heightmap.png")
		{
			cpInitChipmunk();
			_space.gravity(cpv(0, -5));
			_space.elasticIterations(10);
		}

		void
			Gameplay::update()
			{
				_player.update();
				_map.update();

				_space.update();
			}

		void
			Gameplay::handleInput(const SDL_Event& event)
			{
				//	uint8_t* keys = SDL_GetKeyState(NULL);

				if(event.type == SDL_KEYDOWN)
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_LEFT:
							_player.goLeft();
							break;
						case SDLK_RIGHT:
							_player.goRight();
							break;
						case SDLK_UP:
							_player.jump();
							break;
						case SDLK_ESCAPE:
							_engine.quit();
							break;
						default:
							break;
					}
				}
			}

		void
			Gameplay::draw()
			{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(30.0, 800/600.0, 0.1, 1000.0);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				gluLookAt(
						0.0, 0.0, 0.0,
						20.0, 0.0, 10.0,
						0.0, 0.0, 1.0
						);
				_heightmap.draw();

				/*
				   glMatrixMode(GL_PROJECTION);
				   glLoadIdentity();
				   glOrtho(-320.0, 320.0, -240.0, 240.0, -1.0, 1.0);

				   glMatrixMode(GL_MODELVIEW);
				   glLoadIdentity();
				   glPushMatrix();
				   glTranslatef(-_player.position().x, -_player.position().y, 0.0);
				   _space.draw();
				   _player.draw();
				   glPopMatrix();
				   */
			}
	}
}