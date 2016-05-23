

#include "stdafx.h"
#include "LogicSimulator.h"

LogicSimulator::LogicSimulator() 
{

}

void LogicSimulator::OnePointClear(PointInfo pif)
{
	pif.input = -1;
	pif.output = -1;
	pif. and = -1;
	pif. or = -1;
	pif. xor = -1;
	pif. not = -1;
	pif.line = -1;


	pif.gatein = FALSE;
	pif.gateout = FALSE;
	
	pif.lineok = FALSE;
	pif.gate = nothing;
	pif.usingpoint = FALSE;
	pif.value = 0;
}

void LogicSimulator::AllPointClear()
{
	for (int i = 0; i < INDEX; i++)
		for (int j = 0; j < INDEX; j++)
			OnePointClear(pif[i][j]);
}

void LogicSimulator::print(LogicSimulator ls)
{
}

void LogicSimulator::create_input(Input *in, CPoint clicked)
{
	int a = 0;
	in->value = &a;
	in->clicked = clicked; // 마우스가 눌린 위치.
	//사각형을 그리기 위한 left와 right
	in->min = { clicked.x - 1, clicked.y - 1 };
	in->max = { clicked.x + 1, clicked.y + 1 };
	//값을 내보낼 수 있는 점.
	in->output[0] = { clicked.x, clicked.y - 1 };
	in->output[1] = { clicked.x - 1, clicked.y };
	in->output[2] = { clicked.x + 1, clicked.y };
	in->output[3] = { clicked.x, clicked.y + 1 };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			pif[in->min.x + i][in->min.y + j].usingpoint = TRUE;
	for (int i = 0; i < 4; i++) {
		pif[in->output[i].x][in->output[i].y].lineok = TRUE;
		pif[in->output[i].x][in->output[i].y].value = pif[clicked.x][clicked.y].value;
	}
}

void LogicSimulator::create_output(Output *out, CPoint clicked)
{
	int a = 0;
	out->value = &a;
	out->clicked = clicked;
	out->min = { clicked.x - 1, clicked.y - 1 };
	out->max = { clicked.x + 1, clicked.y + 1 };
	out->input[0] = { clicked.x, clicked.y - 1 };
	out->input[1] = { clicked.x - 1, clicked.y };
	out->input[2] = { clicked.x + 1, clicked.y };
	out->input[3] = { clicked.x, clicked.y + 1 };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			pif[out->min.x + i][out->min.y + j].usingpoint = TRUE;
	for (int i = 0; i < 4; i++) {
		pif[out->input[i].x][out->input[i].y].lineok = TRUE;
		pif[out->input[i].x][out->input[i].y].value = pif[clicked.x][clicked.y].value;
	}
}

void LogicSimulator::SavePointOnTheLine(CPoint old_start, CPoint old_end, WhereFixed old_wherefixed) { // 그려진 선에 대한 점을 저장한다.

	CPoint tempP;

	if (old_start == old_end)
		return;

	if (old_wherefixed == GARO)
		if (old_start.y == old_end.y) { // 1줄만 그리는경우.
			 line.Add( GetTwoPt(old_start, old_end));
		}

		else {//두줄을 그려줘야 하는 경우.
			tempP.x = old_end.x;
			tempP.y = old_start.y;
			 line.Add( GetTwoPt(old_start, tempP));

			tempP.x = old_end.x;
			tempP.y = old_start.y;
			 line.Add( GetTwoPt(tempP, old_end));
		}
	else if (old_wherefixed == SERO) {
		if (old_start.x == old_end.x) { // 1줄만 그리는경우.
			 line.Add( GetTwoPt(old_start, old_end));
		}
		else {//두줄을 그려줘야 하는 경우.
			tempP.x = old_start.x;
			tempP.y = old_end.y;
			 line.Add( GetTwoPt(old_start, tempP));

			tempP.x = old_start.x;
			tempP.y = old_end.y;
			 line.Add( GetTwoPt(tempP, old_end));
		}
	}
}


