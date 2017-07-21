#include "server.h"
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
	close(cs);
	close(sock);
    return (0);
}
