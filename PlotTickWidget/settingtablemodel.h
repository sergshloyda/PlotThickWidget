#ifndef SETTINGTABLEMODEL_H
#define SETTINGTABLEMODEL_H

#include <QAbstractTableModel>
#include "qstring.h"
#include <qfile.h>
#include<qdir.h>
struct RowStruct
{
	int num_setting;
	QString name_setting;
	QString use_setting;
	QString thick;
	QString MAB;
	QString algor;
	QString creation_time;
	QString modif_time;

};
class SettingTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	SettingTableModel(QObject *parent);
	~SettingTableModel();

	void setRowStruct();
	void populateModel(const QDir& dir);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation=Qt::Horizontal, int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const override;

	QModelIndex findSettings(int num_settings);

private:
	QList<RowStruct> list_data;

};

#endif // SETTINGTABLEMODEL_H
