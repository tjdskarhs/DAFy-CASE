#ifndef _FLOWCHARTEDITOR_H
#define _FLOWCHARTEDITOR_H

#include <QtWidgets/QFrame>
#include <qstring.h>
#include "ui_FlowChartEditor.h"
#include "../../Utilities/Array.h"
#include <iostream>
using namespace std;

#define INVALID_SPACE 5

class DrawingPaper;
class FlowChartTemplate;
class QMenuBar;
class QMenu;
class QAction;
class GObject;
class NShape;
class SheetManager;
class QStatusBar;
class QLabel;

class FlowChartEditor : public QFrame
{
	Q_OBJECT

public:
	FlowChartEditor(QWidget *parent = Q_NULLPTR);
private:
	FlowChartEditorUi::Ui::FlowChartEditorClass ui;

public:
	Array<QFrame*> windows;
	QMenuBar *menuBar;
	GObject *painter;
	SheetManager *sheetManager;
	NShape *windowClose;

	//===Status Bar
	QStatusBar *statusBar;
	QLabel *messageStatus;
	QLabel *modeStatus;
	QLabel *xStatus;
	QLabel *yStatus;
	QLabel *zoomStatus;
	QLabel *adStatus1;
	QLabel *adStatus2;
	//===Status Bar

	//===Menu Bar - checkable action
	QAction *drawingModeAction; //그리기 모드(M) Ctrl + D
	QAction *ruleKeepAction; //규칙 검사(K)
protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	bool eventFilter(QObject* o, QEvent* e);

	//메뉴
private slots:
	void CommandRange(string text);
	void UpdateEditMenu();
	void UpdateControlArchitectureMenu();

private:
	void CreateActions();
	void CreateMenus();

	QMenu *fileMenu; //파일(F)
	QAction *newAction; //새 파일(N) Ctrl + N
	QAction *openAction; //열기(O) Ctrl + O
	QAction *saveAction; //저장(S) Ctrl + S
	QAction *saveAsAction; //다른 이름으로 저장(A)... Ctrl + Alt + S
	QAction *saveAsImageAction; //이미지(JPG)로 저장(I)... Ctrl + Alt + I
	QAction *printAction; //인쇄(P)... Ctrl + P
	QAction *exitAction; //끝내기(X) Alt + F4

	QMenu *editMenu; //편집(E)
	QAction *undoAction; //실행 취소(U) Ctrl + Z
	QAction *redoAction; //다시 실행(R) Ctrl + Y
	QAction *copyAction; //복사하기(C) Ctrl + C
	QAction *pasteAction; //붙여넣기(P) Ctrl + V
	QAction *cutAction; //잘라내기(T) Ctrl + X
	QAction *deleteAction; //삭제(L) Del
	QAction *selectAllAction; //모두 선택(A) Ctrl + A
	QAction *positionAction; //기호 위치 같게(O)
	QAction *sizeAction; //기호 크기 같게(S)
	QAction *intervalAction; //기호 간격 같게(I)

	QMenu *formatMenu; //서식(O)
	QAction *fontSetAction; //글꼴(F)...
	QAction *pageSetAction; //페이지 설정(U)...

	QMenu *addMenu; //삽입(A)
	QAction *startTerminalSymbolAction; //시작 단말 기호(S)
	QAction *preparationSymbolAction; //준비 기호(P)
	QAction *inputSymbolAction; //입력 기호(I)
	QAction *processSymbolAction; //처리 기호(R)
	QAction *decisionSymbolAction; //판단 기호(D)
	QAction *outputSymbolAction; //출력 기호(O)
	QAction *stopTerminalSymbolAction; //종료 단말 기호(T)

	QMenu *controlArchitectureMenu; //제어구조(C)
	QAction *sequenceArchitectureAction; //순차구조(S)
	QAction *iterationArchitectureAction; //반복구조(I)
	QAction *selectionArchitectureAction; //선택구조(E)

	QMenu *helpMenu; //도움말(H)
	QAction *helpAction; //도움말(H)

	void CreateStatusBar();
};

#endif _FLOWCHARTEDITOR_H