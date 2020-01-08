#include "castle.h"

Castle::Castle(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	InitUI();
}

Castle::~Castle()
{

}

void Castle::InitUI()
{
	QWidget * ctrWidget = new QWidget(this);
	QHBoxLayout * layout = new QHBoxLayout();
	
	m_labelSelect = new QLabel("开始", this);
	int fontId = QFontDatabase::addApplicationFont("./Resources/方正舒体简体.ttf");
	QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont font("FZShuTi-S05S",70,75); 
	QPalette pa;
	pa.setColor(QPalette::WindowText, QColor(0,114,182));
	m_labelSelect->setPalette(pa);
	m_labelSelect->setFont(font);
	m_labelSelect->setFixedSize(this->size());
	m_labelSelect->installEventFilter(this);
	m_labelSelect->setAlignment(Qt::AlignCenter);
	layout->addWidget(m_labelSelect);
	ctrWidget->setLayout(layout);
	this->setCentralWidget(ctrWidget);
	m_showTimer = new QTimer(this);
	m_showTimer->setInterval(1);
	connect(m_showTimer, SIGNAL(timeout()), this, SLOT(onShowTimerOut()));

	QFile fp("Resources/name.txt");
	
	if (fp.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&fp);
		QString line;
		QStringList nameList;
		while (!in.atEnd())
		{
			line = in.readLine();
			if (line.size()>5)
			{
				nameList = line.split(" ");
				m_vPerson.push_back(nameList[nameList.size()-1]);
			}
		}
	}

	QString image_path = "Resources/pic/";
	QDir *dir = new QDir(image_path);
	QStringList fileList = dir->entryList(QDir::Files | QDir::Readable, QDir::Name);
	for (int k = 0; k < fileList.size(); k++)
	{
		QString filename = image_path + fileList.at(k);
		QPixmap image(filename);
		m_vpImage.push_back(image);
	}

}


void Castle::onShowTimerOut()
{
	m_ipersonNum = m_ipersonNum % m_vPerson.size() + 1;
	//m_labelSelect->setNum(m_ipersonNum);
	m_labelSelect->setText(m_vPerson[m_ipersonNum-1]);

	/*m_ipersonNum = m_ipersonNum % m_vpImage.size() + 1;
	m_labelSelect->setPixmap(m_vpImage.at(m_ipersonNum - 1));*/
}


bool Castle::eventFilter(QObject * watched, QEvent * event)
{
	if (watched == m_labelSelect)
	{
		if (event->type() == QEvent::MouseButtonDblClick)
		{
			adjustShowTimer();
		}
	
	}
	return QMainWindow::eventFilter(watched, event);

}


void Castle::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == Qt::Key_F5)
	{
		adjustShowTimer();
	}
	else if (ev->key() == Qt::Key_Escape)
	{
		m_labelSelect->setText("开始");
	}
}

void Castle::adjustShowTimer()
{
	if (!m_showTimer->isActive())
	{
		m_showTimer->start();
		qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
		m_ipersonNum = qrand() % m_vPerson.size() + 1;
	}
	else
		m_showTimer->stop();
}