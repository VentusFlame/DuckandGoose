#include "empch.h"
#include "EnemyDamaged.h"
#include "EnemyDeath.h"
#include "EnemyChase.h"
#include "ExoEngine/Scripts/GateController.h"

namespace EM
{
	EnemyDamaged::EnemyDamaged(StateMachine* stateMachine) {}

	IStates* EnemyDamaged::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyDamaged::OnEnter(StateMachine* stateMachine)
	{
		std::cout << "Enemy Damaged\n";
		int pDmg = 0;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player") {
				pDmg = p_ecs.GetComponent<PlayerAttributes>(i).mDamage;
			}
		}
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth -= pDmg;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth = p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer = 0.5f;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer = 0.5f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Enemy_Damaged_Normal_Attack");

		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 1))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[1].should_play = true;
			std::cout << "Enemy Damaged" << std::endl;
		}
		/*if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
		{
			stateMachine->ChangeState(new EnemyDeath(stateMachine));
		}*/
	}
	void EnemyDamaged::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0) {
			if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
			{
				stateMachine->ChangeState(new EnemyDeath(stateMachine));
			}
			else
			{
				stateMachine->ChangeState(new EnemyChase(stateMachine));
			}
		}
	}
	void EnemyDamaged::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged = false;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer = 0.5f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}