#include "Linphone.h"
#include <QDebug>
#include <QThread>
#include <iostream>
#include <linphone/core.h>
#include <signal.h>
#include "QtCamera.h"
#include <QApplication>
#include <QCameraInfo>
#include <QDebug>
#include <QQuickView>
#include <linphone/player.h>

LinphoneCore *lc;
LinphoneCall *call = NULL;

static bool_t running = TRUE;
static void stop(int signum) { running = FALSE; }

static void call_state_changed(LinphoneCore *lc, LinphoneCall *call,
                               LinphoneCallState cstate, const char *msg) {
  switch (cstate) {
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
    printf("Unhandled notification %i\n", cstate);
  }
}

void LinphoneWorker::listening() {
  LinphoneCoreVTable vtable = {0};

  signal(SIGINT, stop);
  vtable.call_state_changed = call_state_changed;

  lc = linphone_core_new(&vtable, NULL, NULL, NULL);
  while (true) {
    // qDebug() << "Thread linphone:" << QThread::currentThreadId();
    linphone_core_iterate(lc);
    ms_usleep(50000);
    if (linphone_core_is_incoming_invite_pending (lc)) {
      // qDebug() << "Entrou
      emit callReceived(true);
    } else
      emit callReceived(false);
  }
  emit callReceived(false);
}

void LinphoneWorker::inCall() {
    //    LinphoneController v;
    //    v.CreateAccount();
        const char *dest = NULL;
        /* take the destination sip uri from the command line arguments */
        dest = "sip:pvictorcbbbb@sip.linphone.org";
        call = linphone_core_invite(lc, dest);
        linphone_call_ref(call);
        while (running) {
            linphone_core_iterate(lc);
            ms_usleep(50000);
        }
        emit doCalling(true);
    //    if (call && linphone_call_get_state(call) != LinphoneCallEnd) {
    //        /* terminate the call */
    //        printf("Terminating the call...\n");
    //        linphone_core_terminate_call(lc, call);
    //        /*at this stage we don't need the call object */
    //        linphone_call_unref(call);
    //    }
}

void LinphoneWorker::createAccount() {
    LinphoneCoreVTable vtable={0};
    LinphoneProxyConfig* proxy_cfg;
    LinphoneAddress *from;
    LinphoneAuthInfo *info;
    char* identity=NULL;
    char* password=NULL;
    const char* server_addr;

    identity="sip:dac1@192.168.201.223";
    password="123";

    signal(SIGINT,stop);

    lc=linphone_core_new(&vtable,NULL,NULL,NULL);

    proxy_cfg = linphone_core_create_proxy_config(lc);

    from = linphone_address_new(identity);

    if (password!=NULL){
            info=linphone_auth_info_new(linphone_address_get_username(from),NULL,password,NULL,NULL,NULL); /*create authentication structure from identity*/
            linphone_core_add_auth_info(lc,info); /*add authentication info to LinphoneCore*/
    }
    // configure proxy entries
    linphone_proxy_config_set_identity_address(proxy_cfg,from); /*set identity with user name and domain*/
    server_addr = linphone_address_get_domain(from); /*extract domain address from identity*/
    linphone_proxy_config_set_server_addr(proxy_cfg,server_addr); /* we assume domain = proxy server address*/
    linphone_proxy_config_enable_register(proxy_cfg,TRUE); /*activate registration for this proxy config*/
    linphone_address_unref(from); /*release resource*/
    linphone_core_add_proxy_config(lc,proxy_cfg); /*add proxy config to linphone core*/
    linphone_core_set_default_proxy_config(lc,proxy_cfg); /*set to default proxy*/
    /* main loop for receiving notifications and doing background linphonecore work: */

    proxy_cfg = linphone_core_get_default_proxy_config(lc); /* get default proxy config*/
    linphone_proxy_config_edit(proxy_cfg); /*start editing proxy configuration*/
    linphone_proxy_config_enable_register(proxy_cfg,FALSE); /*de-activate registration for this proxy config*/
    linphone_proxy_config_done(proxy_cfg); /*initiate REGISTER with expire = 0*/

    while(linphone_proxy_config_get_state(proxy_cfg) !=  LinphoneRegistrationCleared){
            linphone_core_iterate(lc); /*to make sure we receive call backs before shutting down*/
            ms_usleep(50000);
    }
}


LinphoneController::LinphoneController() {
  LinphoneWorker *listening = new LinphoneWorker;
  listening->moveToThread(&workerListening);
  connect(&workerListening, &QThread::finished, listening, &QObject::deleteLater);
  connect(this, &LinphoneController::operate, listening, &LinphoneWorker::listening);
  connect(listening, &LinphoneWorker::callReceived, this,&LinphoneController::onCallReceived);
  workerListening.start();

  LinphoneWorker *calling = new LinphoneWorker;
  calling->moveToThread(&workerCalling);
  connect(&workerCalling, &QThread::finished, calling, &QObject::deleteLater);
  connect(this, &LinphoneController::calling, calling, &LinphoneWorker::inCall);
  connect(calling, &LinphoneWorker::doCalling, this ,&LinphoneController::onCallOutgoing);
  workerCalling.start();
}

LinphoneController::~LinphoneController() {
  workerListening.quit();
  workerListening.wait();

  workerCalling.quit();
  workerCalling.wait();
}

void LinphoneController::accept() {
    linphone_core_accept_call(lc, call);
    emit acceptCall();
}

void LinphoneController::decline() {
    linphone_core_terminate_call(lc, call);
    linphone_core_destroy(lc);
    linphone_call_unref(call);
    emit declineCall();
}

void LinphoneController::decline_call() {
    linphone_core_terminate_all_calls(lc);
    emit declineInCall();
}

void LinphoneController::video_on() {
    linphone_core_enable_video(lc, TRUE, TRUE);
    linphone_core_enable_self_view(lc, FALSE);
    //linphone_conference_mute_microphone(conf);
    qDebug() << "Video ligado";

    emit videoOn();

}

void LinphoneController::onCallReceived(const bool result) {

    if (result){
        emit openCall();
        //        linphone_username
    }
}

void LinphoneController::onCallOutgoing(const bool result) {

}
