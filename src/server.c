#include "server.h"
#include <errno.h>
#include "libft.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = Xv(NULL, getprotobyname("tcp"), "getprotobyname()");
	sock = X(0, socket(AF_INET, SOCK_STREAM, proto->p_proto), "socket()");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	X(-1, bind(sock, (const struct sockaddr *)&sin, sizeof(sin)), "bind()");
	X(-1, listen(sock, 42), "listen()");
	return (sock);
}

void	go_exe(char **argv)
{
	if (execv("/bin/ls", argv) == -1)
		printf("err  : %s", strerror(errno));
}

void	exec_cmd(int sock, char *str)
{
	char		**argv;
	char		*s = "ls > /tmp/file";
	struct stat	file;
	int			fd;
	void		*ptr;
	argv = ft_split(str);
	(void)argv;
	(void)s;
	fd = 0;
	go_exe(argv);
	printf("HERE I AM\n");
	X(-1, open("/tmp/file", O_RDONLY), "open()");
	X(-1, fstat(fd, &file), "stat()");
	printf("size %lu\n", file.st_size);
	ptr = mmap(0, file.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	printf("HERE I AM\n");
	send(sock, ptr, file.st_size, 0);
}

int		main_loop(int cs)
{
	int		r;
	char	buf[1024];

	while((r = recv(cs, buf, 1023, 0)))
	{
		if (buf[r - 1] == '\n')
			r--;
		buf[r] = '\0';
		printf("input : %s\n", buf);
		exec_cmd(cs, buf);
	}
	return (0);
}


int     main(int ac, char **av)
{
	int					sock;
	int					cs;
	socklen_t			cslen;
	struct sockaddr_in	csin;

	if (ac != 2)
		usage(av[0]);
	sock = create_server(ft_atoi(av[1]));
	cs = X(-1, accept(sock, (struct sockaddr *)&csin, &cslen), "accept()");
	main_loop(cs);
	close(cs);
	close(sock);
    return (0);
}
