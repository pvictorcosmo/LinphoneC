#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Linphone.cpp"

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
//    video_stream_set_native_window_id(std::io_errc::stream,ui->ANYTHING->winId());
    //qDebug() << "Thread principal:" << QThread::currentThreadId();
    return app.exec();
}
