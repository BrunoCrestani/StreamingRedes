#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "../raw_sockets/sockets.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <interface de rede>\n", argv[0]);
    exit(-1);
  }

  unsigned int rsocket = rawSocketCreator(argv[1]);

  // Cria um buffer para armazenar os pacotes
  unsigned char buffer[65536];

  while (1) {
    // Recebe pacotes
    int tamanho = recv(rsocket, buffer, 65536, 0);

    if (tamanho == -1) {
      fprintf(stderr, "Erro ao receber pacote\n");
      exit(-1);
    }

    // Imprime o pacote
    printf("Tamanho: %d\n", tamanho);

    if (strcmp(buffer, "Hello from client!") == 0) {
      printf("Client: %s\n", buffer);
      char msg[] = "Hello from server!";
      rawSocketSend(rsocket, msg, sizeof(msg), 0);
    }
  }

  return 0;
}