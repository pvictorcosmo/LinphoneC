#ifndef LINPHONE_H
#define LINPHONE_H
#include <QJSEngine>
#include <QQmlEngine>
#include <QThread>
#include <linphone/core.h>

class LinphoneWorker : public QObject {
  Q_OBJECT
public slots:
  void doWork();
signals:
  void callReceived(const bool result);
};

class LinphoneController : public QObject {
  Q_OBJECT
  QThread workerThread;

public:
  static LinphoneController &getInstance() {
    static LinphoneController instance;
    return instance;
  }

  static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    // C++ and QML instance they are the same instance
    return &LinphoneController::getInstance();
  }

  Q_INVOKABLE void initThread() { emit operate(); }
  Q_INVOKABLE void accept();
  Q_INVOKABLE void decline();
  Q_INVOKABLE void decline_call();
  Q_INVOKABLE int linphoneCalling();
  Q_INVOKABLE void callInitialization() { emit callInit(); }
  Q_INVOKABLE void mute_call();
  void CreateAccount();

public slots:
  void onCallReceived(const bool result);

private:
  LinphoneController();
  ~LinphoneController();
  LinphoneController(const LinphoneController &) = delete;
  LinphoneController &operator=(const LinphoneController &) = delete;
  LinphoneController(const LinphoneController &&) = delete;
  LinphoneController &operator=(const LinphoneController &&) = delete;
signals:
  void operate();
  void openCall();
  void acceptCall();
  void declineCall();
  void declineInCall();
  void callingOk();
  void callInit();
  void muteCall();
};

#endif // LINPHONE_H
