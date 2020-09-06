#include "GUI.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->undoA = new QShortcut(QKeySequence(QKeySequence::Undo), this->ui.centralWidget);
    this->redoA = new QShortcut(QKeySequence(QKeySequence::Redo), this->ui.centralWidget);

    this->connectSignalsAndSlots();

    //this->initRepo();
    this->totalData();

    this->model = new TableModel(this->service);

    this->ui.mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->addWidget = new AddExpenseWidget(this->service, this->model,this);

    this->addWidget->setAutoFillBackground(true);

    this->ui.mainTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->setStyleSheet("background-image: url(./background2.png)");

    this->ui.mainTableView->verticalHeader()->hide();
    this->ui.totalCostLabel->setStyleSheet("border-radius: 15px;");

    this->ui.mainTableView->setModel(this->model);

    QPixmap logo("logo.png");
    QPixmap scaled = logo.scaled(250, 75, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    this->label = new QLabel(this);
    this->label->setPixmap(scaled);

    this->label->resize(QSize(300, 80));

    this->ui.horizontalLayout->addSpacing(50);
    this->ui.horizontalLayout->addWidget(this->label);
    this->ui.horizontalLayout->addWidget(this->ui.totalCostLabel);

    this->setWindowTitle("Expenses");
    this->setWindowIcon(QIcon("uplefticon.png"));
}

void GUI::connectSignalsAndSlots()
{
    QObject::connect(this->ui.mainTableView, &QTableView::doubleClicked, this, &GUI::openAddWidget);

    QObject::connect(this->undoA, &QShortcut::activated, this, &GUI::Undo);
    QObject::connect(this->redoA, &QShortcut::activated, this, &GUI::Redo);
}

void GUI::openAddWidget()
{
    //QMessageBox::information(this, "Success", QString::fromStdString(to_string(this->getSelectedIndex())));
    int index = this->getSelectedIndex();
    if (index != this->service.countExpenses()) this->addWidget->loadLineEditData(index);
    else this->addWidget->clearLineEditData();
    this->addWidget->show();
}

int GUI::getSelectedIndex()
{
    QModelIndexList indexes = this->ui.mainTableView->selectionModel()->selection().indexes();
    return indexes.at(0).row();
}

void GUI::initRepo()
{
    time_t tt;
    struct tm* ti;

    time(&tt);

    ti = localtime(&tt);
    string extension = ".csv";
    string filename = asctime(ti) + extension;
    this->service.setFilenameRepo(filename);
}

void GUI::totalData()
{
    float sum = this->service.getSumOfExpenses();
    stringstream strm;
    strm << fixed << setprecision(2) << sum;
    string text = "Spent this month:\n" + strm.str();
    this->ui.totalCostLabel->setText(QString::fromStdString(text));
}

void GUI::Undo()
{
    try
    {
        this->service.undo();
    }
    catch (string & error)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(error));
    }
    this->UpdateMucho();
}

void GUI::Redo()
{
    try
    {
        this->service.redo();
    }
    catch (string & error)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(error));
    }
    this->UpdateMucho();
}

void GUI::UpdateMucho()
{
    this->totalData();
    this->model->emit layoutChanged();
}
