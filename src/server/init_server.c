/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"

fd_set fds;
fd_set rfds;
fd_set wfds;

server_t *init_server(char *ip_addr, int port)
{
    server_t *server = malloc(sizeof(server_t));
    char buf[6000];
    int acc = 0;
    ssize_t rec = 0;

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
    acc = accept(server->socket, &server->addr, sizeof(server->addr));
    rec = recv(server->socket, buf, 6000, 0);
    FD_SET(server->socket, &fds);
    int sel = select(&fds, &rfds, &wfds, NULL, NULL);
    server->fd_array[sizeof(server->fd_array)] = sel;
    if (FD_ISSET(sel, &fds) != 0) {
        printf("error");
        return server;
    }

    return server;
}