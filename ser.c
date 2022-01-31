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

int main()
{
    struct hostent *myhost;
    struct sockaddr_in me;
    int s_waiting,s1;
    myhost = gethostbyname(hostname);
    bzero ((char*)&me, sizeof(me));
    me.sin_family = AF_INET;

    me.sin_port = PORT;
    bcopy(myhost -> h_addr, (char*)&me.sin_addr,
    myhost -> h_length);

    s_waiting = socket(AF_INET, SOCK_STREAM, 0);

    bind(s_waiting, &me, sizeof(me));

    listen(s_waiting,1);

    s1 = accept(s_waiting, NULL, NULL);
    close(s_waiting);

    write(1, "会話する", 10);

    do
    {
        int n;
        n = read(0, buf, BUF_LEN);
        write(s1,buf,n);
        write(1,buf,n);
    } while (strncmp(buf,"quit",4) != 0);
    
    close(s1);

}