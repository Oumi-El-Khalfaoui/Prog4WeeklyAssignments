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
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;


static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	go->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(358, 180);
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
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

	//Character1
	auto character1 = std::make_unique<dae::GameObject>();
	character1->SetTexture("pou.png");
	character1->SetLocalPosition({ 320.f, 240.f, 0.f });
	character1->AddComponent(std::make_unique<RotatorComponent>(100.f, 1.f, glm::vec3{ 390.f, 240.f, 0.f }));
	dae::GameObject* pCharacter1 = character1.get();
	scene.Add(std::move(character1));

	//Character2
	auto character2 = std::make_unique<dae::GameObject>();
	character2->SetTexture("pou2.png");
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
