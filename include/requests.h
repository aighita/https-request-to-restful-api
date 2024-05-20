/**
 *  Ghita Andrei-Iulian 324CB
*/

#ifndef _REQUESTS_H_
#define _REQUESTS_H_

void compute_message(char *message, const char *line);

char *compute_post_request(char *host, char *url, char* content_type, char *body_data,
                        char *cookie, char *token);

char *compute_get_request(char *host, char *url, char *cookie, char *token);

char *compute_delete_request(char *host, char *url, char *body_data,
                            char *cookie, char *token);

#endif
