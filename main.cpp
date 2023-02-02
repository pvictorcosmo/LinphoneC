#include "linphone/core.h"
#include <signal.h>
#include<iostream>
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
int main(int argc, char *argv[]){
        LinphoneCoreVTable vtable={0};
        LinphoneCore *lc;
        LinphoneCall *call=NULL;
        const char *dest=NULL;
        /* take the destination sip uri from the command line arguments */
//        dest="sip:+5585989592085@sip.linphone.org";
        signal(SIGINT,stop);

        /*
         Fill the LinphoneCoreVTable with application callbacks.
         All are optional. Here we only use the call_state_changed callbacks
         in order to get notifications about the progress of the call.
         */
        vtable.call_state_changed=call_state_changed;
        /*
         Instanciate a LinphoneCore object given the LinphoneCoreVTable
        */
        lc=linphone_core_new(&vtable,NULL,NULL,NULL);
//        if (dest){
//                /*
//                 Place an outgoing call
//                */
//                call=linphone_core_invite(lc,dest);
//                if (call==NULL){
//                        printf("Could not place call to %s\n",dest);

//                }else printf("Call to %s is in progress...",dest);
//                linphone_call_ref(call);
//        }
        /* main loop for receiving notifications and doing background linphonecore work: */
        while(running){
                linphone_core_iterate(lc);
                ms_usleep(50000);
                if(LinphoneCallStateIncomingReceived){
                     linphone_core_accept_call(lc,call);

                }
        }
//        if (call && linphone_call_get_state(call)!=LinphoneCallEnd){
//                /* terminate the call */
//                printf("Terminating the call...\n");
//                linphone_core_terminate_call(lc,call);
//                /*at this stage we don't need the call object */
//                linphone_call_unref(call);
//        }
//end:



        printf("Shutting down...\n");
        linphone_core_destroy(lc);
        printf("Exited\n");
        return 0;
}
