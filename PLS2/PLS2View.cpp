
// PLS2View.cpp : CPLS2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PLS2.h"
#endif

#include "PLS2Doc.h"
#include "PLS2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPLS2View

IMPLEMENT_DYNCREATE(CPLS2View, CView)

BEGIN_MESSAGE_MAP(CPLS2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CPLS2View::Create_Input_BCLK)
	ON_COMMAND(ID_32772, &CPLS2View::Create_Output_BCLK)
END_MESSAGE_MAP()

// CPLS2View 생성/소멸

CPLS2View::CPLS2View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPLS2View::~CPLS2View()
{
}

BOOL CPLS2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPLS2View 그리기

CPoint CPLS2View::DividedByTen(CPoint point)
{
	CPoint currentPoint;
	if (point.x % 10 <= 4)
		currentPoint.x = point.x - point.x % 10;
	else
		currentPoint.x = point.x + (10 - (point.x % 10));

	if (point.y % 10 <= 4)
		currentPoint.y = point.y - point.y % 10;
	else
		currentPoint.y = point.y + (10 - (point.y % 10));

	return currentPoint;
}

void CPLS2View::OnDraw(CDC* pDC)
{
	CPLS2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i = 0;
	for (i = 0; i <= pDoc->ls.count_input; i++) {
		if (pDoc->ls.in[i].clicked.x != 0 && pDoc->ls.in[i].clicked.y != 0)
		{
			pDC->Rectangle(pDoc->ls.in[i].min.x*10, pDoc->ls.in[i].min.y*10, pDoc->ls.in[i].max.x*10, pDoc->ls.in[i].max.y*10);
		}
	}
	for (i = 0; i <= pDoc->ls.count_output; i++) {
		if (pDoc->ls.out[i].clicked.x != 0 && pDoc->ls.out[i].clicked.y != 0)
		{
			pDC->Ellipse(pDoc->ls.out[i].min.x * 10, pDoc->ls.out[i].min.y * 10, pDoc->ls.out[i].max.x * 10, pDoc->ls.out[i].max.y * 10);
		}
	}
}


// CPLS2View 인쇄

BOOL CPLS2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPLS2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPLS2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPLS2View 진단

#ifdef _DEBUG
void CPLS2View::AssertValid() const
{
	CView::AssertValid();
}

void CPLS2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPLS2Doc* CPLS2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPLS2Doc)));
	return (CPLS2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPLS2View 메시지 처리기


void CPLS2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	CPoint pointofpif{ p1.x / 10, p1.y / 10 };
	if (pDoc->ls.create >= 0) {
		switch (pDoc->ls.create) {
		case LSINPUT:
			pDoc->ls.create_input(&pDoc->ls.in[pDoc->ls.count_input], pointofpif);
			pDoc->ls.create = -1;
			Invalidate();
			break;
		case LSOUTPUT:
			pDoc->ls.create_output(&pDoc->ls.out[pDoc->ls.count_output], pointofpif);
			pDoc->ls.create = -1;
			Invalidate();
			break;
		}
	}
	else {
		if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == input) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.in[pDoc->ls.pif[p1.x / 10][p1.y / 10].input].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == output) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.out[pDoc->ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == line) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.out[pDoc->ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CPLS2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonUp(nFlags, point);
}


void CPLS2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CPoint p1 = DividedByTen(point);
	CPoint pointofpif{ p1.x / 10, p1.y / 10 };
	if (pDoc->ls.create >= 0) {
		switch (pDoc->ls.create) {
		case LSINPUT:
			if (point.x % 5 == 0 || point.y % 5 == 0) {
				Invalidate();
			}
			dc.Rectangle(p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10);
			break;
		case LSOUTPUT:
			if(point.x % 5 == 0 || point.y % 5 == 0) {
				Invalidate();
			}
			dc.Ellipse(p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10);
			break;
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CPLS2View::Create_Input_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_input++;
	pDoc->ls.create = LSINPUT;
}


void CPLS2View::Create_Output_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_output++;
	pDoc->ls.create = LSOUTPUT;
}
