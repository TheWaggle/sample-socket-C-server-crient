# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string.h>
# define PORT (u_short)10000
# define BUF_LEN 100
char hostname[] = "kiyo";

char buf[BUF_LEN];

void main()
{
struct hostent *servhost;
struct sockaddr_in server;
int c1;
servhost = gethostbyname(hostname);
bzero ((char*)&server, sizeof(server));

server.sin_family = AF_INET;
server.sin_port = PORT;
bcopy(servhost -> h_addr,(char*)&server.sin_addr,
      servhost -> h_length);
c1 = socket(AF_INET, SOCK_STREAM, 0);

connect(c1, &server, sizeof(server));
do
{
    int n;
    n = read(c1, buf, BUF_LEN);

    write(1, buf, n);
    n = read(0, buf, BUF_LEN);

    write(c1, buf, n);
} while (strncmp(buf, "quit", 4) != 0);
close(c1);

}