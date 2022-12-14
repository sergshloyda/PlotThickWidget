#ifndef CHANINDICWIDGET_H
#define CHANINDICWIDGET_H

#include <QWidget>
#include "ui_ChannelIndicator.h"
class ChanIndicWidget : public QWidget
{
	Q_OBJECT


public:
	ChanIndicWidget(QWidget *parent);
	~ChanIndicWidget();
	enum ChannelIndicatorMaxChanCount
	{
		MaxCount=16
	};
	void SetChannelStates( const std::vector<bool>& vec_state);

protected:

    bool eventFilter(QObject *obj, QEvent *event);
private slots:
	/*	void LeftMouseButtonChanClicked(int chan_num);
		void RightMouseButtonChanClicked(int chan_num);
		void DblClickOnChan(int chan_num);*/
	void eventMousePressTimer();

signals:

	void ChannelLClicked(quint8 chan);
	void ChannelRClicked(quint8 chan);
	void ChannelDblClicked(quint8 chan);

private:
	QLabel* label_arr[MaxCount];
	bool _bClicked;
	quint8 _chan_num;
	Ui::ChannelIndicator ui;
};

#endif // CHANINDICWIDGET_H
