#include "settingtablemodel.h"
#include <QDateTime>
#include <functional> 
#include "params.h"
#include "dev_struct.h"
#include <algorithm>
#include "devicesettings.h"
SettingTableModel::SettingTableModel(QObject *parent)
	: QAbstractTableModel(parent)
{

}

SettingTableModel::~SettingTableModel()
{

}
void SettingTableModel::setRowStruct()
{
	for(int  i=0;i<10;i++)
	{
		RowStruct rs;
		rs.num_setting=i+1;
		rs.name_setting=tr("Settings # %1").arg(i);
		rs.use_setting=tr("Using # %1").arg(i);;
		rs.thick=tr("Thick something");
		rs.MAB=tr("MAB");
		rs.algor=tr("Some algorithm");;
		rs.creation_time=QDateTime::currentDateTime().toString();
		rs.modif_time=QDateTime::currentDateTime().toString();;
		list_data.append(rs);
	}
}

int SettingTableModel::rowCount(const QModelIndex & /* parent */) const
{
	return list_data.count();
}
int SettingTableModel::columnCount(const QModelIndex & /* parent */) const
{
	return 8;
}
QVariant SettingTableModel::data(const QModelIndex &index, int role) const
 {
	  if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
	  RowStruct rs=list_data.at(index.row());
	  QVariant ret_data;
	  switch(index.column())
	  {
	  case 0:
		  ret_data=rs.num_setting;
		  break;
	  case 1:
		  ret_data=rs.name_setting;
		  break;
	  case 2:
		  ret_data=rs.use_setting;
		  break;
	  case 3:
		  ret_data=rs.thick;
		  break;
	  case 4:
		  ret_data=rs.MAB;
		  break;
	 case 5:
		  ret_data=rs.algor;
		  break;
	 case 6:
		  ret_data=rs.creation_time;
		  break;
	 case 7:
		  ret_data=rs.modif_time;
		  break;


	  }
    return ret_data;
 }

QVariant SettingTableModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
	if ((role != Qt::DisplayRole)||(orientation!=Qt::Horizontal))
        return QVariant();
	 QString  header_str;
	  switch(section)
	  {
	  case 0:
		  header_str=tr("\342\204\226");//№
		  break;
	  case 1:
		  header_str=tr("\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265");//Описание
		  break;
	  case 2:
		 header_str=tr("\320\237\321\200\320\270\320\274\320\265\320\275\320\265\320\275\320\270\320\265");//Применение
		  break;
	  case 3:
		 header_str=tr("\320\232\320\276\320\275\321\202\321\200\320\276\320\273\320\270\321\200.\321\202\320\276\320\273\321\211");
		//Контролир.толщ
		  break;
	  case 4:
		  header_str=tr("\320\234\320\265\321\205-\320\220\320\272\321\203\321\201\321\202.\320\261\320\273\320\276\320\272");
		//Мех-Акуст.блок
		  break;
	 case 5:
		  header_str=tr("\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274");
		//Алгоритм
		  break;
	 case 6:
		  header_str=tr("\320\224\320\260\321\202\320\260 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217");
		//Дата создания
		  break;
	 case 7:
		  header_str=tr("\320\224\320\260\321\202\320\260 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217");
		//Дата изменения
		  break;


	  }
	  return QVariant(header_str);
}
QModelIndex SettingTableModel::findSettings(int num_settings)
{
	auto itr = std::find_if(list_data.begin(), list_data.end(), [=](const RowStruct& rs) { return rs.num_setting == num_settings; });
	int indx=-1;
    if(itr != list_data.end()) {
		indx=std::distance(list_data.begin(),itr);
		return createIndex(indx,0,(void*)&(*itr));
    }
	else
		return QModelIndex();
	
}

 QModelIndex SettingTableModel::index(int row, int column,
                      const QModelIndex &parent ) const 
 {
	 if (!hasIndex(row, column, parent))
		return QModelIndex();

	 return createIndex(row,column,(void*)&list_data.at(row));
 }
void SettingTableModel::populateModel(const QDir& dir)
 {
	 	QDir directory0(dir);
	QFileInfoList  file_list0 = directory0.entryInfoList(QDir::Files);

	/*QString ip_num = curr_ip.section('.', -1);*/


	const char *spark_metka(DEVICE_METKA);
	char check_metka[sizeof(DEVICE_METKA)];

	QString dim_par_name=tr("%1 \321\205 (%2 -%3% +%4%)");//%1 х (%2 -%3% +%4%)

	beginResetModel();
	list_data.clear();

	foreach (QFileInfo curr_fileinfo, file_list0)
	{
		if(curr_fileinfo.suffix() == "dpm")
		{
			RowStruct rs;
			QString file_name = curr_fileinfo.baseName();

			int param_number = file_name.section('_', 2, 2).toInt();
			QFile curr_file(curr_fileinfo.absoluteFilePath());

			if(curr_file.open(QIODevice::ReadOnly))
			{
				bool result = true;

				if(curr_file.read(check_metka, sizeof(DEVICE_METKA)) != sizeof(DEVICE_METKA))
					result = false;

				if(result)
					result = (strcmp(spark_metka, check_metka)==0);


				par_device_t tmp_par_device;

				if(result)
				{
					if(curr_file.read(reinterpret_cast<char *>(&tmp_par_device), sizeof(par_device_t)) != sizeof(par_device_t))
						result = false;
				}



				if(result)
				{
					QString str_cr(curr_fileinfo.created().toString(Qt::ISODate));
					QString str_mod(curr_fileinfo.lastModified().toString(Qt::ISODate));
									
					str_cr.replace(10, 1, ' ');//преобразование из формата вида (YYYY-MM-DDTHH:MM::SS) в формат (YYYY.MM.DD HH:MM:SS)
					str_cr.replace(4, 1, '.');
					str_cr.replace(7, 1, '.');

					str_mod.replace(10, 1, ' ');
					str_mod.replace(4, 1, '.');
					str_mod.replace(7, 1, '.');

					rs.num_setting=param_number;

					const par_view_t &view_par = tmp_par_device.view_par;
					const par_info_strings_t &strings = view_par.strings;
					const par_extra_alg_options_t &extra_alg_opt = view_par.extra_alg_opt;


					const QString& par_info_str=DeviceSettings::ConvRawArrayToStr(strings.par_info, strings.par_info_len);
					rs.name_setting=par_info_str;
					/*table_model.setData( table_model.index(i, 1), par_info_str );*/


					QString param_opt;
					if(extra_alg_opt.max_p_diam == 0)
						param_opt = tr("\320\242\320\276\320\273\321\211 %1-%2 \320\224\320\270\320\260\320\274 > %3")//Толщ %1-%2 Диам > %3
																.arg(static_cast<float>(extra_alg_opt.min_p_thick)/COEF_THICK, 0, 'f', 2)
																.arg(static_cast<float>(extra_alg_opt.max_p_thick)/COEF_THICK, 0, 'f', 2)
																.arg(static_cast<float>(extra_alg_opt.min_p_diam)/COEF_DIAMETER, 0, 'f', 1);
					else
						param_opt = tr("\320\242\320\276\320\273\321\211 %1-%2 \320\224\320\270\320\260\320\274 %3-%4")//Толщ %1-%2 Диам %3-%4
																.arg(static_cast<float>(extra_alg_opt.min_p_thick)/COEF_THICK, 0, 'f', 2)
																.arg(static_cast<float>(extra_alg_opt.max_p_thick)/COEF_THICK, 0, 'f', 2)
																.arg(static_cast<float>(extra_alg_opt.min_p_diam)/COEF_DIAMETER, 0, 'f', 1)
																.arg(static_cast<float>(extra_alg_opt.max_p_diam)/COEF_DIAMETER, 0, 'f', 1);

					rs.use_setting=param_opt;
					/*table_model.setData( table_model.index(i, 2), param_opt );*/
					QString thick_par_str=QString();
					if(tmp_par_device.contr_par.trk_par.cn_list.used_layers & USED_LAYER_THICK)
					{
						const par_thick_t &thick_par = tmp_par_device.contr_par.thick_par;
						
						if(thick_par.thick_lim_relative)
						{
							thick_par_str= tr("%2 +%3% -%4%") 
													.arg(thick_par.thick * 0.01f, 0, 'f', 2)
													.arg(thick_par.thick_lim_rel_pos * 0.1f, 0, 'f', 1)
													.arg(thick_par.thick_lim_rel_neg * 0.1f, 0, 'f', 1);
						}
					
						else
							thick_par_str= tr("%2 +%3 -%4")
													.arg(thick_par.thick * 0.01f, 0, 'f', 2)
													.arg(thick_par.thick_lim_pos * 0.01f, 0, 'f', 1)
													.arg(thick_par.thick_lim_neg * 0.01f, 0, 'f', 1);
					}
					else
						thick_par_str= tr("\320\275\320\265 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\320\270\321\200\321\203\320\265\321\202\321\201\321\217") ;
					//не контролируется
					rs.thick=thick_par_str;
					rs.MAB=DeviceSettings::ConvRawArrayToStr(strings.block_info, strings.block_info_len) ;
			
					QString alg_info_str=tr("\320\221\320\273\320\276\320\272 %1 '%2'").//Блок %1 '%2'
						arg(extra_alg_opt.alg_block).arg(DeviceSettings::ConvRawArrayToStr(strings.alg_info, strings.alg_info_len)) ;
					rs.algor=alg_info_str;

					rs.creation_time=str_cr;
				
					rs.modif_time=str_mod;
						
				
					list_data.append(rs);

				}
				curr_file.close();
			}

		}
	}
	std::sort(list_data.begin(),list_data.end(),[](const RowStruct& rs1,const RowStruct& rs2){return rs1.num_setting < rs2.num_setting;});
	endResetModel();
	/*beginInsertRows(QModelIndex(),0,list_data.count()-1);
	endInsertRows();*/
 }