#ifndef EEGOpenVibe_H
#define EEGOpenVibe_H
#include <QObject>
#include <QThread>
#include <QWaitCondition>

class EEGOpenVibePrivate;

class EEGOpenVibe : public QThread
{
    Q_OBJECT

public:
    static EEGOpenVibe *getInstance(int instance = 1, QWaitCondition *waitCondition = NULL);
    void run(void);
public slots:
    void slotSimulationReceived(QString name, int index, int state = -1);
private slots:
    void slotStimulationSentBack(int button, int isOn);
    void slotSimulationReceivedBack(QString name, int index, int state);
protected slots:
friend EEGOpenVibePrivate;
    void vrpnButton(int button, int isOn);
    void slotVRPNMainLoop();
signals :
    void signalStimulationSent(int button, int isOn);
    void signalStimulationSentBack(int button, int isOn);
    void signalSimulationReceivedBack(QString name, int index, int state);
private:
    EEGOpenVibe(int instance, QWaitCondition *waitCondition);
    ~EEGOpenVibe();
    EEGOpenVibePrivate *m_Private;
};

#endif // EEGOpenVibe_H
