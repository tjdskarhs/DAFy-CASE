/******************************************************************
* 파일 이름 : Shape.cpp
* 기능 : 도형(기호,선)의 추상화 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
* 수정 : Qt - 20.02.12
*******************************************************************/


#include "Shape.h"

#include "Symbols/InputOutput.h"
#include "Symbols/Preparation.h"
#include "Symbols/Terminal.h"
#include "Symbols/Process.h"
#include "Symbols/Decision.h"
#include "Lines/Arrow.h"
#include "Lines/LeftDown.h"
#include "Lines/RightDown.h"
#include "Lines/Join.h"
#include "Lines/RepeatTrue.h"
#include "Lines/RepeatFalse.h"
#include "Lines/RightDownJoin.h"
#include "../Observer/ScrollController.h"
#include "../Interface/Scroll.h"

#include "../../Graphic Objects/Composite/Painter.h"
#include "../../Graphic Objects/Factory/Qt/QtGObjectFactory.h"

Attribute::Attribute() {
	this->vertexIn = ' ';
	this->vertexOut = ' ';
	this->vertexTrue = ' ';
	this->vertexFalse = ' ';

	QPointF initPoint(0.0F, 0.0F);
	this->pointIn = initPoint;
	this->pointOut = initPoint;
	this->pointTrue = initPoint;
	this->pointFalse = initPoint;
}

Attribute::~Attribute() {
}

Attribute::Attribute(const Attribute& source) {
	this->vertexIn = source.vertexIn;
	this->vertexOut = source.vertexOut;
	this->vertexTrue = source.vertexTrue;
	this->vertexFalse = source.vertexFalse;

	this->pointIn = source.pointIn;
	this->pointOut = source.pointOut;
	this->pointTrue = source.pointTrue;
	this->pointFalse = source.pointFalse;
}

Attribute& Attribute::operator = (const Attribute& source) {
	this->vertexIn = source.vertexIn;
	this->vertexOut = source.vertexOut;
	this->vertexTrue = source.vertexTrue;
	this->vertexFalse = source.vertexFalse;

	this->pointIn = source.pointIn;
	this->pointOut = source.pointOut;
	this->pointTrue = source.pointTrue;
	this->pointFalse = source.pointFalse;

	return *this;
}

bool Attribute::IsEqual(const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn == other.vertexIn &&
		this->vertexOut == other.vertexOut &&
		this->vertexTrue == other.vertexTrue &&
		this->vertexFalse == other.vertexFalse &&
		this->pointIn.x() == other.pointIn.x() &&
		this->pointIn.y() == other.pointIn.y() &&
		this->pointOut.x() == other.pointOut.x() &&
		this->pointOut.y() == other.pointOut.y() &&
		this->pointTrue.x() == other.pointTrue.x() &&
		this->pointTrue.y() == other.pointTrue.y() &&
		this->pointFalse.x() == other.pointFalse.x() &&
		this->pointFalse.y() == other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::IsNotEqual(const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn != other.vertexIn ||
		this->vertexOut != other.vertexOut ||
		this->vertexTrue != other.vertexTrue ||
		this->vertexFalse != other.vertexFalse ||
		this->pointIn.x() != other.pointIn.x() ||
		this->pointIn.y() != other.pointIn.y() ||
		this->pointOut.x() != other.pointOut.x() ||
		this->pointOut.y() != other.pointOut.y() ||
		this->pointTrue.x() != other.pointTrue.x() ||
		this->pointTrue.y() != other.pointTrue.y() ||
		this->pointFalse.x() != other.pointFalse.x() ||
		this->pointFalse.y() != other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::operator == (const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn == other.vertexIn &&
		this->vertexOut == other.vertexOut &&
		this->vertexTrue == other.vertexTrue &&
		this->vertexFalse == other.vertexFalse &&
		this->pointIn.x() == other.pointIn.x() &&
		this->pointIn.y() == other.pointIn.y() &&
		this->pointOut.x() == other.pointOut.x() &&
		this->pointOut.y() == other.pointOut.y() &&
		this->pointTrue.x() == other.pointTrue.x() &&
		this->pointTrue.y() == other.pointTrue.y() &&
		this->pointFalse.x() == other.pointFalse.x() &&
		this->pointFalse.y() == other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::operator != (const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn != other.vertexIn ||
		this->vertexOut != other.vertexOut ||
		this->vertexTrue != other.vertexTrue ||
		this->vertexFalse != other.vertexFalse ||
		this->pointIn.x() != other.pointIn.x() ||
		this->pointIn.y() != other.pointIn.y() ||
		this->pointOut.x() != other.pointOut.x() ||
		this->pointOut.y() != other.pointOut.y() ||
		this->pointTrue.x() != other.pointTrue.x() ||
		this->pointTrue.y() != other.pointTrue.y() ||
		this->pointFalse.x() != other.pointFalse.x() ||
		this->pointFalse.y() != other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

NShape::NShape()
	: backGroundColor(QColor(255, 255, 255)),
	borderColor(QColor(0, 0, 0))
	{
	this->x = 0.0F;
	this->y = 0.0F;
	this->width = 0.0F;
	this->height = 0.0F;
	this->borderLine = Qt::SolidLine;
	this->isSelected = false;
	this->registrationNumber = 0;
}

NShape::NShape(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: backGroundColor(backGroundColor),
	borderColor(borderColor),
	contents(contents) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->borderLine = borderLine;
	this->isSelected = false;
	this->registrationNumber = 0;
}

NShape::~NShape() {}

NShape::NShape(const NShape& source)
	: backGroundColor(source.backGroundColor),
	borderColor(source.borderColor),
	contents(source.contents) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->borderLine = source.borderLine;
	this->isSelected = source.isSelected;
	this->registrationNumber = source.registrationNumber;
}

NShape& NShape::operator=(const NShape& source)
{
	this->x = source.x;
	this->y = source.y;

	this->width = source.width;
	this->height = source.height;

	this->backGroundColor = source.backGroundColor;

	this->borderLine = source.borderLine;
	this->borderColor = source.borderColor;

	this->contents = source.contents;

	this->isSelected = source.isSelected;

	this->registrationNumber = source.registrationNumber;

	return *this;
}

bool NShape::IsEqual(const NShape& other) {
	bool retVo = false;

	if (this->x == other.x &&
		this->y == other.y &&
		this->width == other.width &&
		this->height == other.height &&
		this->backGroundColor == other.backGroundColor &&
		this->borderLine == other.borderLine &&
		this->borderColor == other.borderColor &&
		this->contents == other.contents) {
		retVo = true;
	}
	return retVo;
}

bool NShape::IsNotEqual(const NShape& other) {
	bool retVo = false;

	if (this->x != other.x ||
		this->y != other.y ||
		this->width != other.width ||
		this->height != other.height ||
		this->backGroundColor != other.backGroundColor ||
		this->borderLine != other.borderLine ||
		this->borderColor != other.borderColor ||
		this->contents != other.contents) {
		retVo = true;
	}
	return retVo;
}

Long NShape::IsUpperThan(const NShape& other) {
	Long retVo;

	if (this->y < other.y)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long NShape::IsDownThan(const NShape& other) {
	Long retVo;

	if (this->y > other.y)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long NShape::IsFrontThan(const NShape& other) {
	Long retVo;

	if (this->x < other.x)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long NShape::IsRearThan(const NShape& other) {
	Long retVo;

	if (this->x > other.x)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

bool NShape::operator ==(const NShape& other) {
	bool retVo = false;

	if (this->x == other.x &&
		this->y == other.y &&
		this->width == other.width &&
		this->height == other.height &&
		this->backGroundColor == other.backGroundColor &&
		this->borderLine == other.borderLine &&
		this->borderColor == other.borderColor &&
		this->contents == other.contents) {
		retVo = true;
	}
	return retVo;
}
bool NShape::operator !=(const NShape& other) {
	bool retVo = false;

	if (this->x != other.x ||
		this->y != other.y ||
		this->width != other.width ||
		this->height != other.height ||
		this->backGroundColor != other.backGroundColor ||
		this->borderLine != other.borderLine ||
		this->borderColor != other.borderColor ||
		this->contents != other.contents) {
		retVo = true;
	}
	return retVo;
}

void NShape::Move(float x, float y) {
	this->x = x;
	this->y = y;
}

void NShape::ReSize(float width, float height) {
	this->width = width;
	this->height = height;
}

void NShape::Paint(QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor) {
	this->backGroundColor = backGroundColor;
	this->borderLine = borderLine;
	this->borderColor = borderColor;
}


void NShape::DrawActiveShape(GObject *painter) {
	QPointF points[BOXVERTECIES];
	points[0] = QPointF(this->x - LINETHICKNESS, this->y - LINETHICKNESS);
	points[1] = QPointF(this->x + this->width + LINETHICKNESS, this->y - LINETHICKNESS);
	points[2] = QPointF(this->x + this->width + LINETHICKNESS, this->y + this->height + LINETHICKNESS);
	points[3] = QPointF(this->x - LINETHICKNESS, this->y + this->height + LINETHICKNESS);

	painter->DrawPolygon(points, BOXVERTECIES);
}


//////////////////////////////////////////////////////////////////////////
// 선택 관련 : 2015-11-23

void NShape::Select(bool selected) {
	this->isSelected = selected;
}

int NShape::GetHitCode(QPointF point) {
	QRegion region = this->GetRegion();
	return GetHitCode(point, region);
}

int NShape::GetHitCode(const QPointF& point, const QRegion& region) {
	int result = HIT_NONE;
	if (region.contains(point.toPoint())) {
		result = HIT_BODY;
	}

	QRectF rectSelect;
	GetSelectionMarkerRect(HIT_TOPLEFT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TOPLEFT;
	}
	GetSelectionMarkerRect(HIT_TOPMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TOPMIDDLE;
	}
	GetSelectionMarkerRect(HIT_TOPRIGHT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TOPRIGHT;
	}
	GetSelectionMarkerRect(HIT_BOTTOMLEFT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_BOTTOMLEFT;
	}
	GetSelectionMarkerRect(HIT_BOTTOMMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_BOTTOMMIDDLE;
	}
	GetSelectionMarkerRect(HIT_BOTTOMRIGHT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_BOTTOMRIGHT;
	}
	GetSelectionMarkerRect(HIT_LEFTMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_LEFTMIDDLE;
	}
	GetSelectionMarkerRect(HIT_RIGHTMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_RIGHTMIDDLE;
	}
	return result;
}

void NShape::GetSelectionMarkerRect(int marker, QRectF *rect)
{
	int x;
	int y;
	switch (marker) {
	case HIT_TOPLEFT:
		x = this->x;
		y = this->y;
		break;
	case HIT_TOPMIDDLE:
		x = this->x + this->width / 2;
		y = this->y;
		break;
	case HIT_TOPRIGHT:
		x = this->x + this->width;
		y = this->y;
		break;
	case HIT_LEFTMIDDLE:
		x = this->x;
		y = this->y + this->height / 2;
		break;
	case HIT_RIGHTMIDDLE:
		x = this->x + this->width;
		y = this->y + this->height / 2;
		break;
	case HIT_BOTTOMLEFT:
		x = this->x;
		y = this->y + this->height;
		break;
	case HIT_BOTTOMMIDDLE:
		x = this->x + this->width / 2;
		y = this->y + this->height;
		break;
	case HIT_BOTTOMRIGHT:
		x = this->x + this->width;
		y = this->y + this->height;
		break;
	}

	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

QRegion NShape::GetSelectionMarkerAllRegion() {
	float x = this->x;
	float y = this->y;
	QRectF rect(x - 6, y - 6, 7, 7);
	QRegion region(rect.toRect());
	
	x = this->x + this->width / 2;
	y = this->y;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	x = this->x + this->width;
	y = this->y;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	x = this->x;
	y = this->y + this->height / 2;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	x = this->x + this->width;
	y = this->y + this->height / 2;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	x = this->x;
	y = this->y + this->height;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	x = this->x + this->width / 2;
	y = this->y + this->height;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	x = this->x + this->width;
	y = this->y + this->height;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	return region;
}

QCursor NShape::GetCursor(int hit) const {
	QCursor cursor;
	switch (hit) {
	case HIT_BODY:
		cursor.setShape(Qt::SizeAllCursor);
		break;
	case HIT_TOPLEFT:
		cursor.setShape(Qt::SizeFDiagCursor);
		break;
	case HIT_TOPMIDDLE:
		cursor.setShape(Qt::SizeVerCursor);
		break;
	case HIT_TOPRIGHT:
		cursor.setShape(Qt::SizeBDiagCursor);
		break;
	case HIT_BOTTOMLEFT:
		cursor.setShape(Qt::SizeBDiagCursor);
		break;
	case HIT_BOTTOMMIDDLE:
		cursor.setShape(Qt::SizeVerCursor);
		break;
	case HIT_BOTTOMRIGHT:
		cursor.setShape(Qt::SizeFDiagCursor);
		break;
	case HIT_LEFTMIDDLE:
		cursor.setShape(Qt::SizeHorCursor);
		break;
	case HIT_RIGHTMIDDLE:
		cursor.setShape(Qt::SizeHorCursor);
		break;
	}

	return cursor;
}

void NShape::Copy(NShape *object) {
	this->x = object->GetX();
	this->y = object->GetY();
	this->width = object->GetWidth();
	this->height = object->GetHeight();
	this->backGroundColor = object->GetBackGroundColor();
	this->borderLine = object->GetBorderLine();
	this->borderColor = object->GetBorderColor();
	this->contents = object->GetContents();

	this->isSelected = object->IsSelected();
}


void NShape::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController)
{
	QRectF rectSelect;

	QtGObjectFactory factory;
	GObject *brush = factory.MakeBrush(QColor(0, 0, 255), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	painter->Update();

	GetSelectionMarkerRect(HIT_TOPLEFT, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->value();
	Long positionY = scrollController->GetScroll(0)->value();
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_TOPMIDDLE, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_TOPRIGHT, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_BOTTOMLEFT, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_BOTTOMMIDDLE, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_BOTTOMRIGHT, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_RIGHTMIDDLE, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_LEFTMIDDLE, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	painter->SelectObject(*oldBrush);
	painter->Update();
	if (brush != NULL) {
		delete brush;
	}
}

void NShape::MakeRectToPoint(QPointF point, QRectF *rect) {
	float left = point.x() - BOXSCOPE;
	float top = point.y() - BOXSCOPE;
	float right = point.x() + BOXSCOPE;
	float bottom = point.y() + BOXSCOPE;
	rect->setCoords(left, top, right, bottom);
}

void NShape::Rewrite(char(*text)) {
	this->contents = text;
}

int NShape::GetSymbolID() {
	int id = 0;
	if (dynamic_cast<InputOutput*>(this)) {
		id = ID_INPUTOUTPUT;
	}
	else if (dynamic_cast<Preparation*>(this)) {
		id = ID_PREPARATION;
	}
	else if (dynamic_cast<Terminal*>(this)) {
		id = ID_TERMINAL;
	}
	else if (dynamic_cast<Process*>(this)) {
		id = ID_PROCESS;
	}
	else if (dynamic_cast<Decision*>(this)) {
		id = ID_DECISION;
	}

	return id;
}

int NShape::GetLineID() {
	int id = 0;
	if (dynamic_cast<Arrow*>(this)) {
		id = ID_ARROW;
	}
	else if (dynamic_cast<LeftDown*>(this)) {
		id = ID_LEFTDOWN;
	}
	else if (dynamic_cast<RightDown*>(this)) {
		id = ID_RIGHTDOWN;
	}
	else if (dynamic_cast<Join*>(this)) {
		id = ID_JOIN;
	}
	else if (dynamic_cast<RepeatTrue*>(this)) {
		id = ID_REPEATTRUE;
	}
	else if (dynamic_cast<RepeatFalse*>(this)) {
		id = ID_REPEATFALSE;
	}
	else if (dynamic_cast<RightDownJoin*>(this)) {
		id = ID_RIGHTDOWNJOIN;
	}

	return id;
}

SHAPE NShape::GetIdentify() {
	SHAPE id;
	if (dynamic_cast<InputOutput*>(this)) {
		id = INPUTOUTPUT;
	}
	else if (dynamic_cast<Preparation*>(this)) {
		id = PREPARATION;
	}
	else if (dynamic_cast<Terminal*>(this)) {
		id = TERMINAL;
	}
	else if (dynamic_cast<Process*>(this)) {
		id = PROCESS;
	}
	else if (dynamic_cast<Decision*>(this)) {
		id = DECISION;
	}
	else if (dynamic_cast<Arrow*>(this)) {
		id = ARROW;
	}
	else if (dynamic_cast<LeftDown*>(this)) {
		id = LEFTDOWN;
	}
	else if (dynamic_cast<RightDown*>(this)) {
		id = RIGHTDOWN;
	}
	else if (dynamic_cast<Join*>(this)) {
		id = JOIN;
	}
	else if (dynamic_cast<RepeatTrue*>(this)) {
		id = REPEATTRUE;
	}
	else if (dynamic_cast<RepeatFalse*>(this)) {
		id = REPEATFALSE;
	}
	else if (dynamic_cast<RightDownJoin*>(this)) {
		id = RIGHTDOWNJOIN;
	}

	return id;
}

void NShape::Register(Long registrationNumber) {
	this->registrationNumber = registrationNumber;
}

//Block virtual 정의
bool NShape::IsSame(const NShape& other) {
	return false;
}

Long NShape::Attach(NShape *shape) {
	return -1;
}

Long NShape::Insert(Long index, NShape *shape) {
	return -1;
}

Long NShape::Detach(Long index) {
	return -1;
}

Long NShape::Detach(SHAPE identify) {
	return -1;
}

bool NShape::DetachSelectedAll() {
	return false;
}

NShape* NShape::GetAt(Long index) {
	return 0;
}

Long NShape::Find(NShape* shape) {
	return -1;
}

Long NShape::Find(QPointF point) {
	return -1;
}

Long NShape::Find(float x, float y) {
	return -1;
}

Long NShape::Find(QRectF rect) {
	return -1;
}

Long NShape::Find(SHAPE identify) {
	return -1;
}

Long NShape::Find(Long fromIndex, SHAPE identify) {
	return -1;
}

void NShape::Find(Long styles, Long* (*indexes), Long *count) {

}

void NShape::Swap(Long toIndex, Long fromIndex) {

}

void NShape::Swap(Long toIndex, NShape *shape) {

}

void NShape::Clear() {

}

void NShape::SelectAll() {

}

void NShape::UnSelectAll() {

}
void NShape::GetSelecteds(Long* (*indexes), Long *count) {

}

Long NShape::CountSelecteds() {
	return -1;
}

void NShape::AscendingSort() {

}

void NShape::DescendingSort() {

}

Long NShape::FindByRegistrationNumber(SHAPE id, Long registrationNumber) {
	return -1;
}

Long NShape::GetCapacity() const {
	return -1;
}

Long NShape::GetLength() const {
	return -1;
}

Long NShape::GetCurrent() const {
	return -1;
}