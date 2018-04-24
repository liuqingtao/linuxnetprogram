
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/un.h>
#include<cstdlib>
#include <cstdio>
#include<errno.h>
#include<string>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
			}while(0)


	void echo_cli(int sock)
	{
		char sendbuf[1024] = { 0 };
		char recvbuf[1024] = { 0 };
		int n = 0;
		while (1)
		{
			if (fgets(sendbuf,sizeof(sendbuf),stdin) != NULL)
			{
				write(sock, sendbuf, sizeof(sendbuf));
				read(sock, recvbuf, sizeof(recvbuf));
				fputs(recvbuf, stdout);
				memset(sendbuf, 0, sizeof(sendbuf));
				memset(recvbuf, 0, sizeof(recvbuf));
			}

		}
		close(sock);
	}
	int main()
	{
		int sock;
		sock = socket(PF_UNIX, SOCK_STREAM, 0);
		struct sockaddr_un sockaddr;
		memset(&sockaddr, 0, sizeof(sockaddr));
		sockaddr.sun_family = AF_UNIX;
		strcpy(sockaddr.sun_path, "/tmp/test_sock");
		if (connect(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
			ERR_EXIT("connect");
		echo_cli(sock);
		
		
		return 0;
	}

