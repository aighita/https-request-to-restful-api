/**
 *  Ghita Andrei-Iulian 324CB
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "helpers.h"
#include "requests.h"

char HOST[14] = "34.246.184.49";
int PORT = 8080;

int main()
{
    int sockfd;
    char *message;
    char *response;
    char *input = malloc(sizeof(char) * 100);
    char *body_data = malloc(sizeof(char) * 256);
    char *url = malloc(sizeof(char) * 100);
    char *cookie = NULL;
    char *token = NULL;

    int id;

    while (1) {
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) break;

        int value = calculateStringValue(input);

        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

        switch(value) {
        case REGISTER: {
            char username[20] = {0};
            char password[20] = {0};
            printf("username=");
            scanf("%s", username);
            printf("password=");
            scanf("%s", password);

            sprintf(body_data, "{\"username\": \"%s\", \"password\": \"%s\"}", username, password);

            message = compute_post_request(
                "34.241.4.235:8080",
                "/api/v1/tema/auth/register",
                "application/json",
                body_data,
                NULL,
                NULL
            );

            break;
        }

        case LOGIN: {
            char username[20] = {0};
            char password[20] = {0};

            printf("username=");
            scanf("%s", username);
            printf("password=");
            scanf("%s", password);

            sprintf(body_data, "{\"username\": \"%s\", \"password\": \"%s\"}", username, password);

            message = compute_post_request(
                "34.241.4.235:8080",
                "/api/v1/tema/auth/login",
                "application/json",
                body_data,
                NULL,
                NULL
            );

            break;
        }

        case ENTER_LIBRARY: {
            message = compute_get_request(
                "34.241.4.235:8080",
                "/api/v1/tema/library/access",
                cookie,
                NULL
            );

            break;
        }

        case GET_BOOKS: {
            message = compute_get_request(
                "34.241.4.235:8080",
                "/api/v1/tema/library/books",
                cookie,
                token
            );

            break;
        }

        case GET_BOOK: {
            printf("id=");
            scanf("%d", &id);

            sprintf(url, "/api/v1/tema/library/books/%d", id);

            message = compute_get_request(
                "34.241.4.235:8080",
                url,
                cookie,
                token
            );

            break;
        }

        case ADD_BOOK: {
            char title[100] = {0}, author[100] = {0}, genre[100] = {0}, publisher[100] = {0};
            int page_count = 0;
            printf("title=");
            fgets(title, 100, stdin);
            fgets(title, 100, stdin);
            printf("author=");
            fgets(author, 100, stdin);
            printf("genre=");
            fgets(genre, 100, stdin);
            printf("publisher=");
            fgets(publisher, 100, stdin);
            printf("page_count=");
            scanf("%d", &page_count);

            title[strlen(title) - 1] = '\0';
            author[strlen(author) - 1] = '\0';
            genre[strlen(genre) - 1] = '\0';
            publisher[strlen(publisher) - 1] = '\0';

            sprintf(body_data, "{\"title\": \"%s\", \"author\": \"%s\", \"genre\": \"%s\", \"page_count\": \"%d\", \"publisher\": \"%s\"}", title, author, genre, page_count, publisher);

            message = compute_post_request(
                "34.241.4.235:8080",
                "/api/v1/tema/library/books",
                "application/json",
                body_data,
                cookie,
                token
            );

            break;
        }

        case DELETE_BOOK: {
            printf("id=");
            scanf("%d", &id);

            sprintf(url, "/api/v1/tema/library/books/%d", id);

            message = compute_delete_request(
                "34.241.4.235:8080",
                url,
                body_data,
                cookie,
                token
            );

            break;
        }

        case LOGOUT: {
            message = compute_get_request(
                "34.241.4.235:8080",
                "/api/v1/tema/auth/logout",
                cookie,
                NULL
            );

            free(token);

            token = NULL;
            cookie = NULL;

            break;
        }

        default:
            break;
        }

        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);

        switch(value) {
        case 537:
            cookie = extract_cookie(response);
            break;
        case 1394:
            token = extract_token(response);
            break;
        default:
            break;
        }

        int code = extract_response_code(response);
        char *body = extract_body(response);
        if (code == 200 || code == 201) {
            printf("SUCCESS ");
            switch(value) {
            case REGISTER:
                printf("Utilizator înregistrat!");
                break;
            case LOGIN:
                printf("Utilizatorul a fost logat");
                break;
            case ENTER_LIBRARY:
                printf("Utilizatorul are acces la biblioteca");
                break;
            case DELETE_BOOK:
                printf("Cartea cu id %d a fost stearsa!", id);
                break;
            case LOGOUT:
                printf("Utilizatorul s-a delogat!");
                break;
            default:
                break;
            }
            printf("\n");
        } else printf("ERROR\n");

        if ((body != NULL) && (value != ENTER_LIBRARY)) printf("%s\n", body);
    }

    printf("Inchidere program\n");
    close(sockfd);

    free(input);
    free(message);
    free(response);
    free(input);
    free(body_data);
    free(url);

    return 0;
}
