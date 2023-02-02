#include "Linphone.h"
#include <iostream>
#include <QDebug>
#include<linphone/core.h>
#include<signal.h>

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

LinphoneWorker::LinphoneWorker (QObject *parent) : QThread (parent){

}

LinphoneWorker::~LinphoneWorker(){

}

void LinphoneWorker::init(){
    this ->start();
}

void LinphoneWorker::run(){

    LinphoneCoreVTable vtable={0};
    LinphoneCore *lc;
    LinphoneCall *call=NULL;

    signal(SIGINT,stop);
    vtable.call_state_changed=call_state_changed;

    lc=linphone_core_new(&vtable,NULL,NULL,NULL);
    while(true){
        qDebug() << "Thread linphone:" << QThread::currentThreadId();
        linphone_core_iterate(lc);
        ms_usleep(50000);
        if(LinphoneCallStateIncomingReceived){
            linphone_core_accept_call(lc,call);
    }
    }
    qDebug() << "Outra thread";
}


