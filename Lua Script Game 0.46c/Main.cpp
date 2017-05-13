#include <iostream>
//#include <string>
#include "SDL/SDL.h"
#include "RenderEngine.h"
#include "ScriptEngine.h"
#include "GameEngine.h"
#include "Camera.h"
#include "TextEngine.h"

using namespace std;

/*NOTES:
GameEngine Singleton
*/

int main ( int argc, char *argv[] )
{
    RenderEngine *render = NULL;
    Camera *camera = NULL;
    ScriptEngine *scripts = NULL;
    GameEngine *engine = NULL;
    TextEngine *text = NULL;


    render = RenderEngine::Instance();
    cout << "Render Engine Initialized\n";
    if( render == NULL ){
        cout << "ERROR WITH RENDER\n";
    }

    camera = Camera::Instance();
    camera->SetX(0);
    camera->SetY(0);
    camera->SetW(640);
    camera->SetH(480);

    cout << "Camera Initialized\n";
    if( camera == NULL ){
        cout << "ERROR WITH CAMERA\n";
    }

    text = TextEngine::Instance("times.ttf");
    cout << "Text Engine Initialized\n";
    if( text == NULL ){
        cout << "ERROR WITH TEXT\n";
    }

	scripts = ScriptEngine::Instance();
	cout << "Script Engine Initialized\n";
	if( scripts == NULL ){
        cout << "ERROR WITH SCRIPTS\n";
    }

	engine = GameEngine::Instance("config.txt");
    cout << "Game Engine Initialized\n";
    if( engine == NULL ){
        cout << "ERROR WITH ENGINE\n";
    }

	scripts->Register();
	cout << "Scripts Registered\n";

    //Setup scripts (currently not used)
    //scripts->RegisterScript("scripts\\objects\\inspect.lua");
	//scripts->RegisterScript("scripts\\engine.lua");

    Level *level = engine->LoadLevel("maps\\town.map");
    if( level == NULL ){
        cout << "ERROR WITH LEVEL\n";
    }
    Character *player = new Character("data\\characters\\ben.dat", 320, 288);
    if( player == NULL ){
        cout << "ERROR WITH PLAYER\n";
    }
    Character *npc1 = new Character("data\\characters\\joe.dat", 224, 192);
    if( player == NULL ){
        cout << "ERROR WITH NPC\n";
    }

    camera->SetChar( player );
    camera->SetMode( CAM_FOLLOW_CHARACTER );

    level->Draw(1);
    npc1->Draw();
    player->Draw();
    level->Draw(2);

    bool inspecting = false;

	//Main Game Loop
    while( GameEngine::Quit() == false )
    {
        engine->HandleInput();

        if( engine->KeyDown("return") && inspecting == false ){
            player->Action();
            inspecting = true;
        }else if( engine->KeyUp("return") && inspecting == true ){
            inspecting = false;
        }

        if( engine->KeyDown("esc") ){
            engine->SetQuit();
        }

        if( engine->KeyDown("up") ){
            player->Walk("up");
        }else if( engine->KeyDown("left") ){
            player->Walk("left");
        }else if( engine->KeyDown("down") ){
            player->Walk("down");
        }else if( engine->KeyDown("right") ){
            player->Walk("right");
        }else{
            player->Walk("stop");
        }

        engine->Update();
        npc1->Update();
        player->Update();
        camera->Update();

        level->Draw(1);
        npc1->Draw();
        player->Draw();
        level->Draw(2);
    }

	cout << "Terminating Application\n";
	delete text;
	text = NULL;
	delete camera;
	camera = NULL;
	delete engine;
	engine = NULL;
	delete scripts;
	scripts = NULL;
	delete render;
	render = NULL;

	return 0;
}
