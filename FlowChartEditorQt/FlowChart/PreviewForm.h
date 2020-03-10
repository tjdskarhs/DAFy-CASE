#ifndef _PREVIEWFORM_H
#define _PREVIEWFORM_H

#include <QtWidgets/QFrame>
#include "Shape.h"

class FlowChartEditor;
class GObject;

class PreviewForm : public QFrame 
{
	Q_OBJECT

public:
	PreviewForm(QWidget *parent = Q_NULLPTR, FlowChartShape::Shape *flowChart = 0);
	
protected:
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *event);
	//void mousePressEvent(QMouseEvent *event);
	//afx_msg void OnCommandRange(UINT uID);
public:
	FlowChartEditor *editor;
	FlowChartShape::Shape *flowChart;
	FlowChartShape::Shape *a4Paper;
	GObject *painter;
	//CToolBar toolBar;
};

#endif //_PREVIEWFORM_H