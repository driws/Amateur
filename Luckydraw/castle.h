#ifndef CASTLE_H
#define CASTLE_H
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include <QObject>
#include "ui_castle.h"
#include <QIcon>
#include <QDebug>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QFontMetrics>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QTime>
#include <QTimer>
#include <QFontMetrics>
#include <QEvent>
#include <QKeyEvent>
#include <QFontDatabase>
#define MAXNUM 80
class Castle : public QMainWindow
{
	Q_OBJECT
public:
	Castle(QWidget *parent = 0);
	~Castle();
	void InitUI();
	void adjustShowTimer();
private:
	Ui::CastleClass ui;
	QLabel * m_labelSelect;
	int m_ipersonNum;
	QTimer * m_showTimer;
	QVector<QString> m_vPerson;
	QVector<QPixmap> m_vpImage;
	virtual bool eventFilter(QObject * watched, QEvent * event);
	virtual void keyPressEvent(QKeyEvent *ev);
	private slots:
	void onShowTimerOut();
};

#endif // CASTLE_H
