#ifndef EDITOR_H
#define EDITOR_H
#include "Scene.h"
#include "FPSHandler.h"
#include "InputHandler.h"

namespace System
{
	class Dummy
	{
	public:
		Dummy()
			: move_speed(5.0f), turn_speed(1.0f)
		{
			std::function<void(void)> member_func = [this]() { this->AdjustForward(); };
			Input::InputHandler<Input::FPSInputActions>::GetInstance().SubscribeTo(Input::FPSInputActions::ACTION_MOVE_FORWARD, Events::Delegate(member_func, &Dummy::AdjustForward, this));
			member_func = [this]() { this->AdjustBackward(); };
			Input::InputHandler<Input::FPSInputActions>::GetInstance().SubscribeTo(Input::FPSInputActions::ACTION_MOVE_BACKWARD, Events::Delegate(member_func, &Dummy::AdjustBackward, this));
			member_func = [this]() { this->AdjustRight(); };
			Input::InputHandler<Input::FPSInputActions>::GetInstance().SubscribeTo(Input::FPSInputActions::ACTION_MOVE_RIGHT, Events::Delegate(member_func, &Dummy::AdjustRight, this));
			member_func = [this]() { this->AdjustLeft(); };
			Input::InputHandler<Input::FPSInputActions>::GetInstance().SubscribeTo(Input::FPSInputActions::ACTION_MOVE_LEFT, Events::Delegate(member_func, &Dummy::AdjustLeft, this));
			member_func = [this]() { this->AdjustUp(); };
			Input::InputHandler<Input::FPSInputActions>::GetInstance().SubscribeTo(Input::FPSInputActions::ACTION_MOVE_UP, Events::Delegate(member_func, &Dummy::AdjustUp, this));
			member_func = [this]() { this->AdjustDown(); };
			Input::InputHandler<Input::FPSInputActions>::GetInstance().SubscribeTo(Input::FPSInputActions::ACTION_MOVE_DOWN, Events::Delegate(member_func, &Dummy::AdjustDown, this));
		}

		void AttachActor(std::shared_ptr<Graphics::Actor> actor)
		{
			this->actor = actor;
		}

		void AdjustForward()
		{
			if (auto act = actor.lock())
			{
				act->AdjustForward(move_speed);
			}
		}

		void AdjustBackward()
		{
			if (auto act = actor.lock())
			{
				act->AdjustBackward(move_speed);
			}
		}

		void AdjustRight()
		{
			if (auto act = actor.lock())
			{
				act->AdjustRight(move_speed);
			}
		}

		void AdjustLeft()
		{
			if (auto act = actor.lock())
			{
				act->AdjustLeft(move_speed);
			}
		}

		void AdjustUp()
		{
			if (auto act = actor.lock())
			{
				act->AdjustUp(move_speed);
			}
		}

		void AdjustDown()
		{
			if (auto act = actor.lock())
			{
				act->AdjustDown(move_speed);
			}
		}

	private:
		float move_speed, turn_speed;

		std::weak_ptr<Graphics::Actor> actor;

	};

	static Dummy dummy;

	void AttachActors(Graphics::Actor* actor, Graphics::Actor* target)
	{
		std::function<void(float)> member_func = [target](float speed) { return target->AdjustForward(speed); };
		target->SubscribeTo(Graphics::ActorMovements::ACTOR_ADJUSTED_FORWARD, Events::Delegate(member_func, &Graphics::Actor::AdjustForward, target));
		member_func = [target](float speed) { return target->AdjustBackward(speed); };
		target->SubscribeTo(Graphics::ActorMovements::ACTOR_ADJUSTED_BACKWARD, Events::Delegate(member_func, &Graphics::Actor::AdjustBackward, target));
		member_func = [target](float speed) { return target->AdjustRight(speed); };
		target->SubscribeTo(Graphics::ActorMovements::ACTOR_ADJUSTED_RIGHT, Events::Delegate(member_func, &Graphics::Actor::AdjustRight, target));
		member_func = [target](float speed) { return target->AdjustLeft(speed); };
		target->SubscribeTo(Graphics::ActorMovements::ACTOR_ADJUSTED_LEFT, Events::Delegate(member_func, &Graphics::Actor::AdjustLeft, target));
		member_func = [target](float speed) { return target->AdjustUp(speed); };
		target->SubscribeTo(Graphics::ActorMovements::ACTOR_ADJUSTED_UP, Events::Delegate(member_func, &Graphics::Actor::AdjustUp, target));
		member_func = [target](float speed) { return target->AdjustDown(speed); };
		target->SubscribeTo(Graphics::ActorMovements::ACTOR_ADJUSTED_DOWN, Events::Delegate(member_func, &Graphics::Actor::AdjustDown, target));
	}

	void CreateTest()
	{
		std::shared_ptr<Graphics::PawnActor> p_actor = std::make_shared<Graphics::PawnActor>(Graphics::Position(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
		std::shared_ptr<Graphics::CameraActor> c_actor = std::make_shared<Graphics::CameraActor>(Graphics::Position(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 45.0f, 0.1f, 100.0f);
		std::shared_ptr<Graphics::Shader> shader = std::make_shared<Graphics::Shader>("Shaders/test_vertex_shader.shr", "Shaders/test_fragment_shader.shr");
		p_actor->AssignShader(shader);
		p_actor->LoadModel("Resources/Models/Nanosuit/nanosuit.obj");
		AttachActors(p_actor.get(), c_actor.get());
		dummy.AttachActor(p_actor);
		Graphics::Scene::GetInstance().AddActor(p_actor);
		Graphics::Scene::GetInstance().AddActor(c_actor);
		Graphics::Scene::GetInstance().AddShader(shader);
	}
}

#endif
