
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

	void echo_svr(int sock)
	{
		char recvbuf[1024] = { 0 };
		int n = 0;
		while (1)
		{
			n = read(sock, recvbuf, sizeof(recvbuf));
			if (n == -1)
			{
				if (n == EINTR)
					continue;
				ERR_EXIT("read");
			}
			if (n == 0)
			{
				printf("client close");
				break;
			}
				
			fputs(recvbuf, stdout);
			write(sock, recvbuf, sizeof(recvbuf));
			memset(recvbuf, 0, sizeof(recvbuf));
		}


	}
	int main()
	{
		int sock;
		sock = socket(PF_UNIX, SOCK_STREAM, 0);
		unlink("/tmp/test_sock");
		struct sockaddr_un sockaddr;
		sockaddr.sun_family = AF_UNIX;
		strcpy(sockaddr.sun_path, "/tmp/test_sock");

		if (bind(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
		{
			ERR_EXIT("bind");
		}
		if (listen(sock, SOMAXCONN) < 0)
			ERR_EXIT("listen");
		int conn = 0;
		pid_t pid;
		while (1)
		{
			conn = accept(sock, NULL, NULL);
			if (conn == -1)
			{
				if (conn == EINTR)
					continue;
				ERR_EXIT("accept");
			}
			pid = fork();
			if (pid == -1)
				ERR_EXIT("fork");
			if (pid == 0)
			{
				close(sock);
				echo_svr(conn);
				exit(EXIT_SUCCESS);
			}
			close(conn);
		}
		return 0;
	}


	
