/*!*************************************************************************
****
\file HazardFire.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the hazard fire state

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class HazardFire : public IStates
	{
	public:
		HazardFire(StateMachine* stateMachine);
		virtual ~HazardFire() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;

		vec2D mCurrTrans;
		vec2D mCurrScale;
	};
}