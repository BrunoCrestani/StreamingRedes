#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stddef.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "../raw_sockets/sockets.h"
#include "../message/message.h"

void appendFile(char *filename, uint8_t *data, uint8_t size)
{
    FILE *file = fopen(filename, "a+");

    if (file == NULL)
    {
        perror("Erro ao abrir arquivo");
        return;
    }

    fwrite(data, 1, size, file);

    fclose(file);
}

int main()
{
    int rsocket = rawSocketCreator("enp3s0f3u3");
    Message *msg = createFakeMessage();

    int sentBytes = sendMessage(rsocket, msg);

    if (!sentBytes)
    {
        perror("Erro ao enviar mensagem");
    }

    while (1)
    {
        Message *receivedBytes = receiveMessage(rsocket);

        if (receivedBytes == NULL)
        {
            perror("Erro ao receber mensagem");
        }

        switch (receivedBytes->type)
        {
        case DATA:
            appendFile("README.md", receivedBytes->data, receivedBytes->size);
            break;
        }
    }

    return 0;
}