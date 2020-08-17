#pragma once
#include <qabstractitemmodel.h>
#include "Service.h"

class TableModel : public QAbstractTableModel
{
private:
	Service& service;
public:
	TableModel(Service& service, QObject* parent = NULL) : service{ service }, QAbstractTableModel{ parent } {}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	~TableModel() = default;
};

