#pragma once
#include "AddExpenseWidget.h"
#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "ui_AddExpenseWidget.h"
#include "Service.h"
#include "TableModel.h"
#include <qmessagebox.h>
#include <ctime>
#include <sstream>
#include <qshortcut.h>
#include <qpainter.h>
#include <qlabel.h>

class AddExpenseWidget;

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);
    void UpdateMucho();
private:
	QLabel* label;
	QShortcut* undoA;
	QShortcut* redoA;
    AddExpenseWidget *addWidget=0;
    TableModel* model;
    Service service;
    Ui::GUIClass ui;


    void connectSignalsAndSlots();
    void openAddWidget();
    int getSelectedIndex();
    void initRepo();
    void totalData();
	void Undo();
	void Redo();
};










class AddExpenseWidget : public QWidget
{
	Q_OBJECT

public:
	AddExpenseWidget(Service& service, TableModel* model,GUI* Parent, QWidget* parent = Q_NULLPTR);
	~AddExpenseWidget();
	void loadLineEditData(int index);
	void clearLineEditData();

protected:
	virtual void paintEvent(QPaintEvent*) override {
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

private:
	GUI* Parent;
	TableModel* model;
	Service& service;
	Expense loadedexpense;
	int index;
	Ui::AddExpenseWidget ui;
	void connectSignalsAndSlots();
	void processObject();
};