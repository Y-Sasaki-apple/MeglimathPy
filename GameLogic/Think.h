#pragma once
#include "Action.h"
#include<array>
/// <summary>
/// �G�[�W�F���g��l���̍s��
/// </summary>
struct Think
{
	Think(){}
	Think(Step s1, Step s2) :steps{ s1,s2 } {}
	std::array<Step,2> steps;
};