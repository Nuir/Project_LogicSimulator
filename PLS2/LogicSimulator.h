#pragma once
#include "stdafx.h"

#define INDEX 300

#define LSINPUT 0
#define LSOUTPUT 1


//enum�����Դϴ�.
enum WhatGate { nothing, input, output, line };
enum WhereFixed { DEFAULT, SERO, GARO }; // �׸��׸� �� ���ΰ� �����Ǿ��� ���ΰ� �����Ǿ���?

class LogicSimulator
{

public:
//����ü�Դϴ�.
public: 

	struct PointInfo {

		//���� ����ΰ�
		int input = -1; //�Է�
		int output = -1; //���
		int and = -1;
		int or = -1;
		int xor = -1;
		int not = -1;
		int line = -1;


		BOOL gatein = FALSE; //����Ʈ�� �Է°����� ���Ǵ°�
		BOOL gateout = FALSE; //����Ʈ�� ��°����� ���Ǵ°�
	
		BOOL lineok = FALSE;
		WhatGate gate = nothing;
		BOOL usingpoint = FALSE;

		int* value = NULL;
	}pinfo;

	struct Input {
		int* value = NULL; // ������ ��.
		CString name;
		CPoint clicked{ -1, -1 }; // �簢���� ����.
		CPoint min; // �簢���� ���� ����
		CPoint max; // �簢���� ������ ����
		CPoint output[4];  // ���� ������ �� �ִ� ��.
	};

	struct Output {
		int* value = NULL; 
		CString name;
		CPoint clicked{ -1, -1 }; 
		CPoint min; 
		CPoint max;
		CPoint input[4];
		CPoint points[9] = { (clicked.x - 1, clicked.y - 1), (clicked.x, clicked.y - 1), (clicked.x + 1, clicked.y - 1),
							 (clicked.x - 1, clicked.y) ,    (clicked.x, clicked.y) ,    (clicked.x + 1, clicked.y) ,
							 (clicked.x - 1, clicked.y + 1), (clicked.x, clicked.y + 1), (clicked.x + 1, clicked.y + 1) };

	};

	struct TwoPt {

		CPoint firstPt;
		CPoint secondPt;
		TwoPt() {}
		TwoPt(CPoint a, CPoint b) {
			firstPt = a;
			secondPt = b;
		}
	};

//�����Դϴ�.
public:
	PointInfo pif[INDEX][INDEX];// 
	Input in[INDEX];
	Output out[INDEX];

	CPoint downPoint;
	CPoint upPoint;


	TwoPt GetTwoPt(CPoint a, CPoint b) {
		TwoPt *p;
		p = new TwoPt(a,b);
		return *p;
	}

	CArray<TwoPt, TwoPt&> line; // TwoPoint�� �迭.


	WhereFixed wherefixed = DEFAULT;
	WhatGate whatgate = nothing;

	int count_input = -1;
	int count_output = -1;
	int create = -1; // �� ���ڿ� ���� ������ ������ ���� ������.

//�Լ��Դϴ�.
public:
	LogicSimulator::LogicSimulator();
	void OnePointClear(PointInfo pif);
	void AllPointClear();
	void print(LogicSimulator ls);
	void create_input(Input* in, CPoint clicked);
	void create_output(Output* out, CPoint clicked);
	void SavePointOnTheLine(CPoint old_start, CPoint old_end, WhereFixed old_wherefixed);
};