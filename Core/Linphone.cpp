#include "Linphone.h"
#include <iostream>
#include <QDebug>
#include<linphone/core.h>
#include<signal.h>
#include <QThread>

static bool_t running=TRUE;
static void stop(int signum){
        running=FALSE;
}

/*
 * Call state notification callback
 */
static void call_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg){
    switch(cstate){
            case LinphoneCallOutgoingRinging:
                    printf("It is now ringing remotely !\n");
            break;
            case LinphoneCallOutgoingEarlyMedia:
                    printf("Receiving some early media\n");
            break;
            case LinphoneCallConnected:
                    printf("We are connected !\n");
            break;
            case LinphoneCallStreamsRunning:
                    printf("Media streams established !\n");
            break;
            case LinphoneCallEnd:
                    printf("Call is terminated.\n");
            break;
            case LinphoneCallError:
                    printf("Call failure !");
            break;

            default:
                    printf("Unhandled notification %i\n",cstate);
    }
}

void LinphoneWorker::doWork()
{
    LinphoneCoreVTable vtable={0};
    LinphoneCore *lc;
    LinphoneCall *call=NULL;

    signal(SIGINT,stop);
        vtable.call_state_changed=call_state_changed;

        lc=linphone_core_new(&vtable,NULL,NULL,NULL);
        while(true) {
            //qDebug() << "Thread linphone:" << QThread::currentThreadId();
            linphone_core_iterate(lc);
            ms_usleep(50000);
            if(linphone_core_in_call(lc)){
                //qDebug() << "Entrou";
                emit callReceived(true);
                linphone_core_accept_call(lc,call);
            }
            else
                emit callReceived(false);
        }
        //qDebug() << "Outra thread";
    emit callReceived(false);
};


LinphoneController::LinphoneController() {
    LinphoneWorker *worker = new LinphoneWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &LinphoneController::operate, worker, &LinphoneWorker::doWork);
    connect(worker, &LinphoneWorker::callReceived, this, &LinphoneController::onCallReceived);
    workerThread.start();
}

LinphoneController::~LinphoneController(){
    workerThread.quit();
    workerThread.wait();
}

void LinphoneController::onCallReceived(const bool result)
{
    if(result)
        emit openCall();
}




