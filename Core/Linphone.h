#ifndef LINPHONE_H
#define LINPHONE_H
#include <QJSEngine>
#include <QQmlEngine>
#include <QThread>
#include <linphone/core.h>

class LinphoneWorker : public QObject {
  Q_OBJECT
public slots:
  void received();
  void makeCall();
signals:
  void doCalling(const bool result);
  void callReceived(const bool result);
private:
  void createAccount();
};

class LinphoneController : public QObject {
  Q_OBJECT
  QThread workerListening;
  QThread workerCalling;

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

  Q_INVOKABLE void initThread() {
      emit waitingCall();
  }

  Q_INVOKABLE void callInitialization() {
      emit callInit();
  }

  Q_INVOKABLE int linphoneCalling() {
      emit calling();
  }

  Q_INVOKABLE void accept();
  Q_INVOKABLE void decline();
  Q_INVOKABLE void decline_call();
  Q_INVOKABLE void video_on();
  Q_INVOKABLE void loadingScreen();

public slots:
  void onCallReceived(const bool result);
  void onCallOutgoing(const bool result);

private:
  LinphoneController();
  ~LinphoneController();
  LinphoneController(const LinphoneController &) = delete;
  LinphoneController &operator=(const LinphoneController &) = delete;
  LinphoneController(const LinphoneController &&) = delete;
  LinphoneController &operator=(const LinphoneController &&) = delete;

signals:
  void waitingCall();
  void calling();
  void openCall();
  void acceptCall();
  void declineCall();
  void declineInCall();
  void callingOk();
  void callInit();
  void videoOn();
  void loading();
};

#endif // LINPHONE_H
