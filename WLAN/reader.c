#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
        long mtype;
        char mtext[200];
};

int main(void)
{
        struct my_msgbuf buf;
        int msqid;
        key_t key;
        key=10;

        msqid = msgget(key, 0644);

        printf("Ready to receive messages, captain.\n");

        for(;;)
        {
                msgrcv(msqid, &buf, sizeof buf.mtext, 0, 0);
                printf("Received: \"%s\"\n", buf.mtext);
        }
        return 0;
}
