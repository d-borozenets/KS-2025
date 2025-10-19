#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_KEY 1234

struct message {
    long type;
    char text[100];
};

int main() {
    int msgid;
    struct message msg;

    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Receiver started. Waiting for messages...\n");

    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.text), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        if (strcmp(msg.text, "exit") == 0)
            break;

        printf("Received: %s\n", msg.text);
    }

    printf("Receiver finished.\n");

    // Видаляємо чергу
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
