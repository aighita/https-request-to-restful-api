/**
 *  Ghita Andrei-Iulian 324CB
*/

#ifndef _HELPERS_H_
#define _HELPERS_H_

#define BUFLEN 4096
#define LINELEN 1000

#define REGISTER        869
#define LOGIN           537
#define ENTER_LIBRARY   1394
#define GET_BOOKS       957
#define GET_BOOK        842
#define ADD_BOOK        819
#define DELETE_BOOK     1149
#define LOGOUT          666

/**
 * @brief Function that establishes connection to server. Returns [sockfd] or
 *  ends application on error.
 * @param host_ip
 * @param portno
 * @param ip_type
 * @param socket_type
 * @param flag
*/
int open_connection(char *host_ip, int portno, int ip_type, int socket_type, int flag);

/**
 * @brief Custom error function
 * @param msg error message
*/
void error(const char *msg);

/**
 * @brief Send message to server
 * @param sockfd socket connection to server
 * @param message message to send 
*/
void send_to_server(int sockfd, char *message);

/**
 * @brief Receive response from server
*/
char *receive_from_server(int sockfd);

/**
 * @brief Close connection on given socket.
 * @param sockfd socket
*/
void close_connection(int sockfd);

char* extract_cookie(char* response);

char* extract_token(char *response);

int calculateStringValue(const char *str);

#endif
