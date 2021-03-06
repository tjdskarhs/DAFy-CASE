// SelectingTool.Cpp
#include "SelectingTool.h"

#include "../Interface/DrawingPaper.h"
#include "../Interface/FlowChartEditor.h"
#include "../Interface/Scroll.h"
#include "../Observer/ScrollController.h"
#include "../Shapes/Shape.h"
#include "../Shapes/Symbols/Decision.h"
#include "../Shapes/Lines/Line.h"
#include "../Shapes/Lines/Arrow.h"
#include "../Paint/Zoom/Zoom.h"
#include "../Paint/Zoom/ZoomVisitor.h"
#include "../Paint/Coordinate/CoordinateConverter.h"

#include "../../Graphic Objects/Composite/Painter.h"

#include <windows.h>

SelectingTool* SelectingTool::instance = 0;

SelectingTool::SelectingTool() {
}

SelectingTool* SelectingTool::Instance() {
	if (instance == 0) {
		instance = new SelectingTool;
	}
	return instance;
}

void SelectingTool::Destroy() {
	if (instance != 0) {
		delete instance;
	}
	instance = 0;
}

void SelectingTool::OnLButtonDown(DrawingPaper *canvas, QPointF point) {
	bool isControlPressed;
	isControlPressed = ((::GetKeyState(VK_CONTROL) & 0x8000) != 0);
	if (!isControlPressed && canvas->label == NULL) {
		canvas->flowChart->UnSelectAll();
	}

	canvas->startX = point.x();
	canvas->startY = point.y();
	canvas->currentX = canvas->startX;
	canvas->currentY = canvas->startY;
}

void SelectingTool::OnMouseMove(DrawingPaper *canvas, QPointF point) {
	bool isMouseLButtonPressed;
	isMouseLButtonPressed = ((::GetKeyState(VK_LBUTTON) & 0x8000) != 0);
	
	/*
	if (isMouseLButtonPressed) { // 왼쪽 마우스 버튼이 눌려져있을때
		canvas->drawSelectingAreaFlag = true;
		canvas->update();
	}
	*/

	canvas->currentX = point.x();
	canvas->currentY = point.y();

	if (isMouseLButtonPressed) {
		canvas->drawSelectingAreaFlag = true;
		canvas->update();
	}
}

void SelectingTool::OnLButtonUp(DrawingPaper *canvas, QPointF point) {
	QRegion region;
	NShape *shape;
	Long i;
	Long it;
	Long index;

	Long positionX = 0;
	Long positionY = 0;
	if (canvas->scrollController != NULL) {
		positionX = canvas->scrollController->GetScroll(1)->value();
		positionY = canvas->scrollController->GetScroll(0)->value();
	}
	canvas->startX += positionX;
	canvas->startY += positionY;
	canvas->currentX += positionX;
	canvas->currentY += positionY;

	NShape *holdA4Paper = canvas->a4Paper->Clone();
	NShape *holdFlowChart = canvas->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(canvas->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	index = holdFlowChart->Find(canvas->currentX, canvas->currentY);
	if (canvas->startX == canvas->currentX && canvas->startY == canvas->currentY) {
		if (index > -1) {
			shape = canvas->flowChart->GetAt(index);
			(shape->IsSelected()) ? (shape->Select(false)) : (shape->Select(true));
			canvas->indexOfSelected = index;
		}
	}
	else {
		QRectF rect;
		float sX;
		float lX;
		if (canvas->startX < canvas->currentX) {
			sX = canvas->startX;
			lX = canvas->currentX;
		}
		else {
			sX = canvas->currentX;
			lX = canvas->startX;
		}
		float sY;
		float lY;
		if (canvas->startY < canvas->currentY) {
			sY = canvas->startY;
			lY = canvas->currentY;
		}
		else {
			sY = canvas->currentY;
			lY = canvas->startY;
		}
		rect.setCoords(sX, sY, lX, lY);

		i = 0;
		it = canvas->flowChart->GetLength();
		for (i = 0; i < it; i++) {
			shape = holdFlowChart->GetAt(i);
			region = shape->GetRegion();
			if (region.contains(rect.toRect()))
			{
				canvas->flowChart->GetAt(i)->Select(true);
			}
		}
	}

	if (holdFlowChart != 0) {
		delete holdFlowChart;
	}
	if (holdA4Paper != 0) {
		delete holdA4Paper;
	}
	if (zoomVisitor != 0) {
		delete zoomVisitor;
	}

	Long count;
	Long(*indexes);
	canvas->flowChart->GetSelecteds(&indexes, &count);

	if (count > 0) {
		canvas->mode = DrawingPaper::SELECT;
	}
	else {
		canvas->mode = DrawingPaper::IDLE;
	}

	if (indexes != 0) {
		delete[] indexes;
	}
}