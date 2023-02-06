#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include "Linphone.cpp"
#include <QCameraInfo>
#include "QtCamera.h"

#include <QCamera>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<LinphoneController>("LinphoneController", 1, 0, "LinphoneController", &LinphoneController::qmlInstance);
    LinphoneController::getInstance();


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
//    QWindow *wi = QWindow::fromWinId(video_stream_get_native_window_id(video));
//    QWidget *ww = QWidget::createWindowContainer(wi);
    QCamera v;
    //v.start();

    return app.exec();
}
