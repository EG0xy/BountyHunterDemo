///-------------------------------------------------------------------------------------------------
/// File:	GS_INITIALIZED.cpp.
///
/// Summary:	Implements the 'INITIALIZED' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_INITIALIZED()
{
	// Create and initialize systems
	{
		if (ALLOW_CHEATS == true)
		{
		// CheatSystem
		CheatSystem*		CHEATS = ECS::ECS_Engine->GetSystemManager()->AddSystem<CheatSystem>();
		}

		// InputSystem
		InputSystem*		InS = ECS::ECS_Engine->GetSystemManager()->AddSystem<InputSystem>();
		
		// MenuSystem
		MenuSystem*			MeS = ECS::ECS_Engine->GetSystemManager()->AddSystem<MenuSystem>();

		// RenderSystem
		RenderSystem*		RdS = ECS::ECS_Engine->GetSystemManager()->AddSystem<RenderSystem>(this->m_Window);

		// ATTENTION: The order how the Physics and World System are added matters!
		// PhysicsSystem
		PhysicsSystem*		PyS = ECS::ECS_Engine->GetSystemManager()->AddSystem<PhysicsSystem>();

		// WorldSystem
		WorldSystem*		WoS = ECS::ECS_Engine->GetSystemManager()->AddSystem<WorldSystem>();

		// RespawnSystem
		RespawnSystem*		ReS = ECS::ECS_Engine->GetSystemManager()->AddSystem<RespawnSystem>();

		// LifetimeSystem
		LifetimeSystem*		LS = ECS::ECS_Engine->GetSystemManager()->AddSystem<LifetimeSystem>();

		// ControllerSystem
		ControllerSystem*	CoS = ECS::ECS_Engine->GetSystemManager()->AddSystem<ControllerSystem>();

		// PlayerSystem
		PlayerSystem*		PlS = ECS::ECS_Engine->GetSystemManager()->AddSystem<PlayerSystem>();

		// Change InputSystem's priority to high
		ECS::ECS_Engine->GetSystemManager()->SetSystemPriority<InputSystem>(ECS::HIGH_SYSTEM_PRIORITY);

		// Add system dependencies
		CoS->AddDependencies(InS);
		WoS->AddDependencies(InS);
		PyS->AddDependencies(InS, WoS);
		RdS->AddDependencies(PyS);
		LS->AddDependencies(ReS);
		
		ECS::ECS_Engine->GetSystemManager()->UpdateSystemWorkOrder();

		// create two system work state masks: one when runnign, one when game is paused
		
		// ingame system work state
		this->m_Ingame_SystemWSM = ECS::ECS_Engine->GetSystemManager()->GetSystemWorkState();

		// not ingame system work state (gameover, paused, ...)
		this->m_NotIngame_SystemWSM = ECS::ECS_Engine->GetSystemManager()->GenerateActiveSystemWorkState(MeS, PlS, RdS, InS);
	} 

	// put game to GameState 'RESTARTED'
	ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()
{
	// Initialize SDL
	InitializeSDL();

	// Initialize ECS
	InitializeECS();

	// broadcast initial window state
	ECS::ECS_Engine->SendEvent<WindowResizedEvent>(this->m_WindowWidth, this->m_WindowHeight);

	if (this->m_Fullscreen == false)
		ECS::ECS_Engine->SendEvent<EnterFullscreenModeEvent>();
	else
		ECS::ECS_Engine->SendEvent<EnterWindowModeEvent>();
}

void Game::GS_INITIALIZED_LEAVE()
{
	RegisterEventCallback(&Game::OnToggleFullscreen);

	// raise game initialized event
	ECS::ECS_Engine->SendEvent<GameInitializedEvent>();
}