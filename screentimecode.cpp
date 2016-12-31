#include <QDialog>
#include <QLabel>
#include <QPainter>
#include <QTime>
#include <QGridLayout>

#include "screentimecode.h"

ScreenTimecode::ScreenTimecode(QObject *parent)
    : QObject(parent)
    , m_timePixmap1(NULL)
    , m_timePixmap2(NULL)
  {
  m_auxLabelColor = QColor(Qt::black);
  m_auxLabelText  = "";
  int timeDialogSizeX = 1650, timeDialogSizeY = 70;
  int timeDialogPosX = 0, timeDialogPosY = 0;
  m_timeDialogSizeX = timeDialogSizeX;
  m_timeDialogSizeY = timeDialogSizeY;

  QGridLayout *timeLayout1 = new QGridLayout();

  QDialog *timeDialog1 = new QDialog();
  timeDialog1->setLayout(timeLayout1);
  timeLayout1->setContentsMargins(0,0,0,0);

  timeDialog1->setWindowTitle(tr("Experiment Time Code"));
  timeDialog1->move(timeDialogPosX,timeDialogPosY);
  timeDialog1->resize(timeDialogSizeX, timeDialogSizeY);
  timeDialog1->setWindowFlags(Qt::Window | Qt::Dialog | Qt::Tool);

  m_timeWidget1 = new QWidget();
  timeLayout1->addWidget(m_timeWidget1, 0, 0);
  m_timeWidget1->resize(timeDialogSizeX, timeDialogSizeY);
  m_timeLabel1 = new QLabel(m_timeWidget1);
  //m_timeLabel1->setText("abc");
  m_timeLabel1->setAutoFillBackground(true);

  m_timePixmap1 = new QPixmap(QSize(timeDialogSizeX, timeDialogSizeY));
  m_timePixmap1->fill(Qt::black);
  m_timeLabel1->setPixmap(*m_timePixmap1);

  QPainter painter( m_timePixmap1 );
  painter.setPen(Qt::white);
  QFont font("Courier", 100, 100);

  painter.setFont(font);
  painter.drawText(QRect(QPoint(0, 0), QPoint(timeDialogSizeX, timeDialogSizeY)), Qt::AlignLeft, "00:00:00.00");
    
  m_timeLabel1->setPixmap(*m_timePixmap1);

  timeDialog1->show();

  QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout1()));

  m_timer.setInterval(10);
  m_timer.start();
  }

ScreenTimecode::~ScreenTimecode()
  {
  }

void ScreenTimecode::timeout1()
  {
  QString timeOutput = QTime::currentTime().toString("HH:mm:ss.zzz").left(11);
  delete m_timePixmap1;
  QSize size = m_timeWidget1->size();
  m_timePixmap1 = new QPixmap(size);
  m_timePixmap1->fill(Qt::black);
  QPainter painter( m_timePixmap1 );
  painter.setPen(Qt::white);
  QFont font("Courier", size.height() - 20, size.height() - 20);

  QPen pen1(QColor("#888888"));
  QPen pen2(QColor("#000000"));
  QBrush brush1(m_auxLabelColor);
  painter.setFont(font);
  painter.setPen(pen1);
  painter.drawText(QRect(QPoint(60, 0), QPoint(m_timeDialogSizeX, m_timeDialogSizeY)), Qt::AlignLeft, timeOutput);

  QFont font2("Courier", (size.height() - 20) / 2, (size.height() - 20) / 2);
  //painter.fillRect(QRect(0, 0, 55, 35), brush1);
  painter.setPen(m_auxLabelColor);
  painter.setFont(font2);
  painter.drawText(QRect(QPoint(0, 0), QPoint(m_timeDialogSizeX, m_timeDialogSizeY)), Qt::AlignLeft, m_auxLabelText);
  QImage origImage(m_timePixmap1->toImage());
  QImage flipImage(m_timePixmap1->toImage());
  m_timePixmap1->fill(Qt::black);
  flipImage = flipImage.copy(QRect(0, 0, m_timeDialogSizeX / 3, m_timeDialogSizeY));
  flipImage = flipImage.mirrored(true, false);
  painter.drawImage(QPoint(m_timeDialogSizeX / 4.125, 0), origImage);
  painter.drawImage(QPoint(m_timeDialogSizeX / 1.500, 0), flipImage);
  
  m_timeLabel1->setPixmap(*m_timePixmap1);
  m_timeLabel1->setFixedSize(m_timePixmap1->size());
  }

void ScreenTimecode::slotSetAuxLabel(const QString &aText, const QColor &aColor)
  {
  m_auxLabelText = aText;
  m_auxLabelColor = aColor;
  }
