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

    // Створюємо (або відкриваємо) чергу
    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Sender started. Enter messages (type 'exit' to quit):\n");

    while (1) {
        msg.type = 1; // тип повідомлення
        fgets(msg.text, sizeof(msg.text), stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0'; // прибираємо \n

        if (strcmp(msg.text, "exit") == 0)
            break;

        if (msgsnd(msgid, &msg, strlen(msg.text) + 1, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Sent: %s\n", msg.text);
    }

    printf("Sender finished.\n");
    return 0;
}
