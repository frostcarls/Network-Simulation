#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf
{
        long mtype;
        char mtext[200];
};

int main(void)
{
        struct my_msgbuf buf;
        int msqid;
        key_t key;

        key=10;
        msqid = msgget(key, 0644 | IPC_CREAT);

        printf("Enter lines of text, ^C to quit:\n");
        buf.mtype = 1;

        while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
        {
                int len = strlen(buf.mtext);

                if (buf.mtext[len-1] == '\n')
                        buf.mtext[len-1] = '\0';

                msgsnd(msqid, &buf, len+1, 0);
        }
        msgctl(msqid, IPC_RMID, NULL);
        return 0;
}
