/**
 *  Ghita Andrei-Iulian 324CB
*/

#ifndef _REQUESTS_H_
#define _REQUESTS_H_

/**
 * @brief Add "line" to "message" with "\\r\\n" for proper send to server.
*/
void compute_message(char *message, const char *line);

/**
 * @brief Compute "GET" method request message.
*/
char *compute_get_request(char *host, char *url, char *cookie, char *token);

/**
 * @brief Compute "DELETE" method request message.
*/
char *compute_delete_request(char *host, char *url, char *body_data, char *cookie, char *token);

/**
 * @brief Compute "POST" method request message.
*/
char *compute_post_request(char *host, char *url, char* content_type, char *body_data, char *cookie, char *token);

#endif
