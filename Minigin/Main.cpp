#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RotatorComponent.h"
#include "Components/LevelComponent.h"
#include "Components/HealthComponent.h"
#include "Components/LivesDisplayComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "InputManager.h"
#include "Input/MoveCommand.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;


static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	//fonts
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontGame = dae::ResourceManager::GetInstance().LoadFont("Retro Gaming.otf", 26);

	// BG
	auto go = std::make_unique<dae::GameObject>();
	go->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(358, 180);
	scene.Add(std::move(go));


	auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	to->SetColor({ 255, 255, 0, 255 });
	to->SetPosition(292, 20);
	scene.Add(std::move(to));

	//FPSCounter
	auto fpsGO = std::make_unique<dae::GameObject>();
	auto fpsTO = std::make_shared<dae::TextObject>("0.0", font, SDL_Color{ 255, 255, 0, 255 });
	fpsTO->SetPosition(20, 20);

	auto textComponent = std::make_unique<TextComponent>(fpsTO);
	TextComponent* pTextComponent = textComponent.get();
	fpsGO->AddComponent(std::move(textComponent));

	auto fpsComponent = std::make_unique<FPSComponent>(pTextComponent);
	fpsGO->AddComponent(std::move(fpsComponent));

	scene.Add(std::move(fpsGO));

	// Game
	// Level1 BG
	auto levelGO = std::make_unique<dae::GameObject>(); //empty go as level container
	levelGO->AddComponent(std::make_unique<LevelComponent>("level1.lvl"));
	scene.Add(std::move(levelGO));
	//

	//Character1
	auto character1 = std::make_unique<dae::GameObject>();
	character1->SetTexture("bomberman.png");
	character1->SetLocalPosition({ 320.f, 240.f, 0.f });
	//character1->AddComponent(std::make_unique<RotatorComponent>(100.f, 1.f, glm::vec3{ 390.f, 240.f, 0.f }));
	dae::GameObject* pCharacter1 = character1.get();

		// health and score component
	auto healthComp1 = std::make_unique<HealthComponent>(3);
	HealthComponent* pHealth1 = healthComp1.get();
	character1->AddComponent(std::move(healthComp1));

	auto scoreComp1 = std::make_unique<ScoreComponent>();
	ScoreComponent* pScore1 = scoreComp1.get();
	character1->AddComponent(std::move(scoreComp1));

	scene.Add(std::move(character1));

		// UI
	auto livesGO1 = std::make_unique<dae::GameObject>();
	auto livesTO1 = std::make_shared<dae::TextObject>("Lives: 3", fontGame, SDL_Color{ 255, 255, 255, 255 });
	livesTO1->SetPosition(10, 70);
	
	auto livesText1 = std::make_unique<TextComponent>(livesTO1);
	TextComponent* pLivesText1 = livesText1.get();
	livesGO1->AddComponent(std::move(livesText1));
	livesGO1->AddComponent(std::make_unique<LivesDisplayComponent>(pHealth1, pLivesText1));
	scene.Add(std::move(livesGO1));

	auto scoreGO1 = std::make_unique<dae::GameObject>();
	auto scoreTO1 = std::make_shared<dae::TextObject>("Score: 0", fontGame, SDL_Color{ 255, 255, 255, 255 });
	scoreTO1->SetPosition(10, 90);

	auto scoreText1 = std::make_unique<TextComponent>(scoreTO1);
	TextComponent* pScoreText1 = scoreText1.get();
	scoreGO1->AddComponent(std::move(scoreText1));
	scoreGO1->AddComponent(std::make_unique<ScoreDisplayComponent>(pScore1, pScoreText1));
	scene.Add(std::move(scoreGO1));

		// keybindings
	auto& input = dae::InputManager::GetInstance();

	input.BindKeyboardCommand(SDL_SCANCODE_W, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(pCharacter1, glm::vec3{ 0, -1, 0 }, 10.f));
	input.BindKeyboardCommand(SDL_SCANCODE_S, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(pCharacter1, glm::vec3{ 0, 1, 0 }, 10.f));
	input.BindKeyboardCommand(SDL_SCANCODE_A, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(pCharacter1, glm::vec3{ -1, 0, 0 }, 10.f));
	input.BindKeyboardCommand(SDL_SCANCODE_D, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(pCharacter1, glm::vec3{ 1, 0, 0 }, 10.f));

	//Character2
	auto character2 = std::make_unique<dae::GameObject>();
	character2->SetTexture("bomberman.png");
	character2->AddComponent(std::make_unique<RotatorComponent>(100.f, -2.f));
	character2->SetParent(pCharacter1, false);
	scene.Add(std::move(character2));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
