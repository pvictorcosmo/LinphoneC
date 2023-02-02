#ifndef LINPHONE_H
#define LINPHONE_H
#include <QThread>
#include <QQmlEngine>
#include <QJSEngine>

class LinphoneWorker : public QObject
{
    Q_OBJECT
public slots:
    void doWork();
    signals:
    void callReceived(const bool result);
};

class LinphoneController : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    static LinphoneController& getInstance() {
      static LinphoneController instance;
      return instance;
    }

    static QObject* qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);
        // C++ and QML instance they are the same instance
        return &LinphoneController::getInstance();
    }

    Q_INVOKABLE void initThread() {
        emit operate();
    }
public slots:
    void onCallReceived(const bool result);
private:
    LinphoneController();
    ~LinphoneController();
    LinphoneController(const LinphoneController&) = delete;
    LinphoneController& operator=(const LinphoneController&) = delete;
    LinphoneController(const LinphoneController&&) = delete;
    LinphoneController& operator=(const LinphoneController&&) = delete;
signals:
    void operate();
    void openCall();
};

#endif // LINPHONE_H
