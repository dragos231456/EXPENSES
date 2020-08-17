#include "TableModel.h"
#include <qfont.h>
#include <qcolor.h>

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.getExpenses().size() + 1;
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 3;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();

	Expense expense;
	if(row!=this->service.countExpenses())  expense = this->service.getExpenses()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if (row != this->service.countExpenses())
		{
			switch (col)
			{
			case 0:
				return QString::fromStdString(expense.displayName());
			case 1:
				return QString::fromStdString(expense.displayPrice());
			case 2:
				return QString::fromStdString(expense.displayDatetime());
			default:
				break;
			}
		}
		else
		{
			switch (col)
			{
			case 0:
				return QString("Add expense...");
			default:
				break;
			}
		}
	}
	if (role == Qt::TextAlignmentRole)
	{
		return Qt::AlignCenter;
	}
	if (role == Qt::FontRole)
	{

		if (row != this->service.countExpenses())
		{
			switch (col)
			{
			case 0:
				return QFont("Calibri", 12);
			case 1:
				return QFont("Calibri", 12);
			case 2:
				return QFont("Calibri", 12);
			default:
				break;
			}
		}
		else
		{
			return QFont("Times", 12);
		}
	}
	if (role == Qt::TextColorRole)
	{
		if (row != this->service.countExpenses())
		{
			switch (col)
			{
			case 0:
				return QColor(Qt::black);
			case 1:
				return QColor(Qt::black);
			case 2:
				return QColor(Qt::black);
			default:
				break;
			}
		}
		else
		{
			return QColor(Qt::gray);
		}
	}
	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{	
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString("Description");
			case 1:
				return QString("Price");
			case 2:
				return QString("Date");
			default:
				break;
			}
		}
	}
	if (role == Qt::FontRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QFont("Calibri",16,QFont::Bold);
			case 1:
				return QFont("Calibri", 16, QFont::Bold);
			case 2:
				return QFont("Calibri", 16, QFont::Bold);
			default:
				break;
			}
		}
	}
	return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
