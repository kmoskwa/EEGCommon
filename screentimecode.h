#ifndef SCREENTIMECODE_H
#define SCREENTIMECODE_H

//#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <QPointer>

//#include "ui_screentimecode.h"

class ScreenTimecode : public QObject
{
    Q_OBJECT

public:
    ScreenTimecode(QObject *parent = 0);
    ~ScreenTimecode();

public slots:
    void slotSetAuxLabel(const QString &aText, const QColor &aColor);

protected slots:
    void timeout1();

private:
    //Ui::ScreenTimecodeClass ui;
    QTimer m_timer;
    QPointer<QLabel> m_timeLabel1;
    //QPointer<QPixmap> m_timePixmap1;
    QPixmap *m_timePixmap1;
    QPixmap *m_timePixmap2;
    QPointer<QWidget> m_timeWidget1;
    int m_timeDialogSizeX;
    int m_timeDialogSizeY;
    QString m_auxLabelText;
    QColor  m_auxLabelColor;
};

#endif // SCREENTIMECODE_H
