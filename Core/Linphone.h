#ifndef LINPHONE_H
#define LINPHONE_H

#include <QThread>

class LinphoneWorker : public QThread
{
    Q_OBJECT
public:
    LinphoneWorker( QObject *parent=nullptr);
    ~LinphoneWorker();
    void init();

private:
    void run();

};

#endif // LINPHONE_H
