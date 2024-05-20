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

/**
 * @brief Extract session cookie from server response.
 * @param response
*/
char* extract_cookie(char* response);

/**
 * @brief Extract authorization token from server response.
 * @param response
*/
char* extract_token(char *response);

/**
 * @brief Calculate integer (sum) value of a string by every letter.
 * @param str
*/
int calculateStringValue(const char *str);

/**
 * @brief Extract body from server's reponse. JSON
*/
char* extract_body(const char* response);

/**
 * @brief Extract response code from server's response.
*/
int extract_response_code(char *response);

#endif
