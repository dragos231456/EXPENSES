#include "GUI.h"

AddExpenseWidget::AddExpenseWidget(Service& service,TableModel *model,GUI* Parent,QWidget* parent)
	: QWidget(parent) , service{service}
{
	this->Parent = Parent;
	setWindowFlags(Qt::Window);
	ui.setupUi(this);
	this->model = model;

	this->connectSignalsAndSlots();
	this->setStyleSheet("background-image: url(./secondbackground2.png)");

	this->ui.descriptionLineEdit->setStyleSheet("background:#FFF;" "border-radius: 15px;");
	this->ui.fileLineEdit->setStyleSheet("background:#FFF;" "border-radius: 7px;");
	this->ui.nameLineEdit->setStyleSheet("background:#FFF;" "border-radius: 7px;");
	this->ui.priceLineEdit->setStyleSheet("background:#FFF;" "border-radius: 7px;");

	this->ui.pushButton->setStyleSheet("border-radius: 7px;" "border: 0.5px solid white;" "min-width: 120px;" "min-height: 30px;");
	this->ui.pushButton_2->setStyleSheet("border-radius: 7px;" "border: 0.5px solid white;" "min-width: 120px;" "min-height: 30px;");
	this->ui.pushButton_3->setStyleSheet("border-radius: 7px;" "border: 0.5px solid white;" "min-width: 120px;" "min-height: 30px;");
	this->ui.pushButton_4->setStyleSheet("border-radius: 7px;" "border: 0.5px solid white;" "min-width: 120px;" "min-height: 30px;");
	this->ui.loadPushButton->setStyleSheet("border-radius: 8px;" "border: 2px solid white;" "min-width: 150px;" "min-height: 40px;");
	QPixmap pixmap("icon.png");
	QIcon ButtonIcon(pixmap);
	this->ui.loadPushButton->setIcon(ButtonIcon);
	this->ui.loadPushButton->setIconSize(pixmap.rect().size());
	this->ui.loadPushButton->setFixedSize(pixmap.rect().size());

	this->setWindowTitle("Expenses");
	this->setWindowIcon(QIcon("uplefticon.png"));
}

AddExpenseWidget::~AddExpenseWidget()
{
}

void AddExpenseWidget::loadLineEditData(int index)
{
	Expense expense = this->service.getExpenses()[index];
	this->ui.nameLineEdit->setText(QString::fromStdString(expense.displayName()));
	this->ui.priceLineEdit->setText(QString::fromStdString(expense.displayPrice()));
	this->ui.descriptionLineEdit->setText(QString::fromStdString(expense.displayDescription()));
	this->ui.fileLineEdit->setText(QString::fromStdString(expense.displayPhotoName()));

	this->loadedexpense = expense;
	this->index = index;
}

void AddExpenseWidget::clearLineEditData()
{
	this->ui.nameLineEdit->clear();
	this->ui.priceLineEdit->clear();
	this->ui.descriptionLineEdit->clear();
	this->ui.fileLineEdit->clear();

	this->index = -1;
}

void AddExpenseWidget::connectSignalsAndSlots()
{
	QObject::connect(this->ui.loadPushButton, &QPushButton::clicked, this, &AddExpenseWidget::processObject);
}

void AddExpenseWidget::processObject()
{
	float price;
	string name = this->ui.nameLineEdit->text().toStdString();
	string pricestr = this->ui.priceLineEdit->text().toStdString(); stringstream pricestream(pricestr); pricestream >> price;
	string descrption = this->ui.descriptionLineEdit->toPlainText().toStdString();
	string photoName = this->ui.fileLineEdit->text().toStdString(); if (photoName == "") photoName = "-";
	try
	{
		if (this->index == -1) //add
		{
			time_t tt;
			struct tm* ti;

			time(&tt);

			ti = localtime(&tt);
			string datetime = asctime(ti);
			datetime[datetime.size() - 1] = '\0';

			this->service.addExpense(name, price, datetime, descrption, photoName);
			this->hide();
			this->Parent->UpdateMucho();
		}
		else //update
		{
			this->service.updateExpense(name, price, this->loadedexpense.displayDatetime(), descrption, photoName, this->index);
			QMessageBox::information(this, "Success", "Expense successfully updated!");
			this->hide();
			this->Parent->UpdateMucho();
		}
	}
	catch (string & error)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(error));
	}
}
