#ifndef DIALLOADSAVEPAR_H
#define DIALLOADSAVEPAR_H

#include <QDialog>
#include <QtWidgets/QtWidgets>
#include "settingtablemodel.h"
#include "ui_dial_load_save_par.h"
class DialLoadSavePar : public QDialog
{
	Q_OBJECT

public:
	DialLoadSavePar(QWidget *parent= 0);
	virtual ~DialLoadSavePar();

	void CollectParamFiles();
	void SetSaveMode(const bool new_save_mode, const bool setup_mode);

	void  set_path(const QString& path);
	QString  get_path();

	void  set_num_par(const int  num_par);
	int  get_num_par();
	
	void  set_ip(const QString& ip);
	void  set_butt_text(const QString& text);
	
	void setSelectedPar();
private:

	QString DirName;
	QString curr_ip;
	bool save_mode;
	bool param_handler_setted;
	Ui::Dialog_load_save_par ui;

	SettingTableModel* table_model;
	QItemSelectionModel *selectionModel;
	
	quint16 selected_par;
	bool recursive_select;
public slots:

	void OnButtDir();
	void OnSetPath();
	void select_new_param();
	void OnSelectedParam(QModelIndex,QModelIndex);
	void selectionChanged( const QItemSelection & , const QItemSelection &  );
};

#endif // DIALLOADSAVEPAR_H
