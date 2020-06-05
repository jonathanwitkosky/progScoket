#include <stdio.h>
#include <string.h> /* strlen */
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* inet_addr */
#include <unistd.h> /* close */

int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];

    
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

    if (socket_desc == -1)
    {
        printf("Não foi possível criar o socket\n");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

   
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        printf("Erro ao conectar-se\n");
        return 1;
    }

    printf("Conectado.\n");

    do {
       
        bzero(message, sizeof(message));
        
       
        printf("Digite uma mensagem: ");

        int ch, n = 0;
      
        while ((ch = getchar()) != '\n' && n < 2000) {
            message[n] = ch;
            ++n;
        }

        if (send(socket_desc, message, strlen(message), 0) < 0)
        {
            printf("Erro ao enviar\n");
            return 1;
        }
        printf("Dados enviados.\n");

      
        if (recv(socket_desc, server_reply, 2000, 0) < 0)
        {
            printf("Falha no recv\n");
            return 1;
        }
        printf("Resposta recebida.\n");
        printf("%s\n", server_reply);

       
        bzero(server_reply, sizeof(server_reply));
    } while (strcmp(message, "exit") != 0);

   
    close(socket_desc);

    return 0;
}