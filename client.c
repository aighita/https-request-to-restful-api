/**
 *  Ghita Andrei-Iulian 324CB
*/

#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include <stdbool.h>

#include "helpers.h"
#include "requests.h"
#include "parson.h"

char HOST[14] = "34.246.184.49";
int PORT = 8080;

char* extract_body(const char* response) {
    const char* start_pos = strstr(response, "[");
    if (start_pos == NULL) {
        start_pos = strstr(response, "{");
        if (start_pos == NULL) return NULL;
    }
    return strdup(start_pos);
}

int extract_response_code(char *response) {
    char* start = strstr(response, "HTTP/1.1 ");
    if (start == NULL) return -1;

    start += 9;

    char *end = strstr(start, " ");
    if (start == NULL) return -1;

    size_t len = end - start;

    char *code = malloc(len + 1);
    strncpy(code, start, len);
    code[len] = '\0';

    return atoi(code);
}

int main()
{
    int sockfd;
    char *message;
    char *response;
    char *input = malloc(sizeof(char) * 100);
    char *body_data = malloc(sizeof(char) * 256);
    char *cookie = NULL;
    char *token = NULL;

    int id;

    while (1) {
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) break;

        int value = calculateStringValue(input);

        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

        switch(value) {

        // Register
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

        // Login
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

        // Enter Library
        case ENTER_LIBRARY: {
            message = compute_get_request(
                "34.241.4.235:8080",
                "/api/v1/tema/library/access",
                cookie,
                NULL
            );

            break;
        }

        // Get Books
        case GET_BOOKS: {
            // printf("Compute get books.\n");
            message = compute_get_request(
                "34.241.4.235:8080",
                "/api/v1/tema/library/books",
                cookie,
                token
            );
            // printf("Computed get books.\n");

            break;
        }

        // Get Book
        case GET_BOOK: {
            printf("id=");
            scanf("%d", &id);

            char url[100] = {0};
            sprintf(url, "/api/v1/tema/library/books/%d", id);

            message = compute_get_request(
                "34.241.4.235:8080",
                url,
                cookie,
                token
            );

            break;
        }

        // Add Book
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
            // fgets(publisher, 100, stdin);

            title[strlen(title) - 1] = '\0';
            author[strlen(author) - 1] = '\0';
            genre[strlen(genre) - 1] = '\0';
            publisher[strlen(publisher) - 1] = '\0';

            sprintf(body_data, "{\"title\": \"%s\", \"author\": \"%s\", \"genre\": \"%s\", \"page_count\": \"%d\", \"publisher\": \"%s\"}", title, author, genre, page_count, publisher);
            // printf("Book: %s\n", body_data);

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

        // Delete Book
        case DELETE_BOOK: {
            printf("id=");
            scanf("%d", &id);

            char *url = malloc(100);
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

        // Logout
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

        case 1142: {
            break;
        }

        default:
            printf("Invalid command: %s\n", input);
            break;
        }

        // printf("Sending:\n%s\n", message);
        send_to_server(sockfd, message);
        // printf("Sent!\n");
        response = receive_from_server(sockfd);
        // printf("Response:\n%s\n", response);

        switch(value) {
        case 537:
            cookie = extract_cookie(response);
            // printf("Session cookie: %s\n", cookie);
            break;
        case 1394:
            token = extract_token(response);
            // printf("Token: %s\n", token);
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
                printf("Utilizator înregistrat cu succes!");
                break;
            case LOGIN:
                printf("Utilizatorul a fost logat cu succes");
                break;
            case ENTER_LIBRARY:
                printf("Utilizatorul are acces la biblioteca");
                break;
            case DELETE_BOOK:
                printf("Cartea cu id %d a fost stearsa cu succes!", id);
                break;
            case LOGOUT:
                printf("Utilizatorul s-a delogat cu succes!");
                break;
            case GET_BOOKS:
                // printf("\n%s\n", extract_body(response));
                break;
            case GET_BOOK:
                // printf("\n%s\n", extract_body(response));
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

    // free(input);
    // free(message);
    // free(response);

    return 0;
}
