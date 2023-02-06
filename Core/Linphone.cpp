#include "Linphone.h"
#include <iostream>
#include <QDebug>
#include <linphone/core.h>
#include <signal.h>
#include <QThread>
#include <QCameraInfo>
#include <QDebug>
LinphoneCore *lc;

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
int LinphoneController::linphoneCalling(){

    LinphoneCoreVTable vtable={0};
    LinphoneCall *call=NULL;
    const char *dest=NULL;
    /* take the destination sip uri from the command line arguments */
    vtable.call_state_changed=call_state_changed;
    dest="sip:Leo@192.168.200.121";
       if (dest){
                /*
                 Place an outgoing call
                */
                call=linphone_core_invite(lc,dest);
                if (call==NULL){
                        printf("Could not place call to %s\n",dest);

                }else printf("Call to %s is in progress...",dest);
                linphone_call_ref(call);
        }
    /* main loop for receiving notifications and doing background linphonecore work: */
    while(running){
            linphone_core_iterate(lc);
            ms_usleep(50000);
//            if(LinphoneCallStateIncomingReceived){
//                 linphone_core_accept_call(lc,call);

//            }
    }
        if (call && linphone_call_get_state(call)!=LinphoneCallEnd){
                /* terminate the call */
                printf("Terminating the call...\n");
                linphone_core_terminate_call(lc,call);
                /*at this stage we don't need the call object */
                linphone_call_unref(call);
        }



    printf("Shutting down...\n");

    printf("Exited\n");


    emit callingOk();
    return 0;

}


void LinphoneWorker::doWork()
{
    LinphoneCoreVTable vtable={0};

    signal(SIGINT,stop);
        vtable.call_state_changed=call_state_changed;

        lc=linphone_core_new(&vtable,NULL,NULL,NULL);
        while(true) {
            //qDebug() << "Thread linphone:" << QThread::currentThreadId();
            linphone_core_iterate(lc);
            ms_usleep(50000);
            if(linphone_core_in_call(lc)){
                //qDebug() << "Entrou
                emit callReceived(true);
//                linphone_core_accept_call(lc,call);
            }
            else
                emit callReceived(false);
        }

        //qDebug() << "Outra thread";
    emit callReceived(false);

}


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

void LinphoneController::accept(){
    LinphoneCall *call=NULL;
    linphone_core_accept_call(lc,call);
    emit acceptCall();
}








void LinphoneController::decline(){
    LinphoneReason Reason;
    LinphoneCall *call=NULL;
    linphone_core_decline_call(lc,call,Reason);

    emit declineCall();
}

bool Video::checkCameras()
{
    int camCount = QCameraInfo::availableCameras().count();
    if ( camCount > 0) {
        qDebug() << "Cameras encontradas: " << camCount << endl;
        return true;
    }
    else {
        qDebug() << "Nenhuma camera foi detectada!" << endl;
        return false;
    }
}





