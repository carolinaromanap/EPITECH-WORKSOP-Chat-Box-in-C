/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"

server_t *init_server(char *ip_addr, int port)
{
    server_t *server = malloc(sizeof(server_t));

    server->ip_addr = ip_addr;
    server->port = port;
    server->socket =  socket(AF_INET, SOCK_STREAM, 6);
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = inet_addr(server->ip_addr);
    if (bind(server->socket,(struct sockaddr*)&server->addr,sizeof(server->addr)) == -1) {
        perror("Bind");
        return NULL;
    }
    if (listen(server->socket, 50) == -1) {
        perror("Listen");
        return NULL;
    }
    return server;
}