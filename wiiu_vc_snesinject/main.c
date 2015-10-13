#include <stdio.h>
#include <conio.h>
#include <windows.h>

static const int cport = 7331;
void sendall(SOCKET s, unsigned char *data, size_t size);
void waitforinput();
void main(int argc, char *argv[])
{	//windows exec path is so ugly to get
	char curpath[MAX_PATH]; 
	GetModuleFileName(NULL, curpath, MAX_PATH);
	char *pptr = curpath;
	while(*pptr) *pptr++;
	while(*pptr != '\\') *pptr--;
	*pptr = '\0';
	char ipfile[512];
	sprintf(ipfile, "%s\\ip.txt", curpath);
	//lets actually do cool stuff 8 lines later
	printf("WiiU SNES ROM Injector by FIX94\n");
	FILE *f = fopen(ipfile,"r");
	if(f == NULL)
	{
		printf("%s not found!\n", ipfile);
		waitforinput();
		return;
	}
	//enough space for a IPv4 address
	char caddr[16];
	caddr[15] = '\0';
	fgets(caddr,16,f);
	fclose(f);
	if(argc != 2)
	{
		printf("Please specify a ROM to inject\n");
		waitforinput();
		return;
	}
	f = fopen(argv[1], "rb");
	if(f == NULL)
	{
		printf("ROM not available!\n");
		waitforinput();
		return;
	}
	//just read the whole ROM at once, we got RAM nowadays
	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(f);
	rewind(f);
	unsigned char *buf = (unsigned char*)malloc(fsize);
	fread(buf,1,fsize,f);
	fclose(f);
	WSADATA WsaDat;
	WSAStartup(MAKEWORD(2,2),&WsaDat);
	SOCKET s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		printf("Socket error!\n");
		goto end;
	}
	SOCKADDR_IN saddr;
	saddr.sin_port=htons(cport);
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=inet_addr(caddr);
	if(connect(s,(SOCKADDR*)(&saddr),sizeof(saddr)) == SOCKET_ERROR)
	{
		printf("Unable to connect to %s:%i\n", caddr, cport);
		goto end;
	}
	printf("Connected to %s:%i\n", caddr, cport);
	//cmd_upload plus location to send to
	unsigned char cmd[1];
	cmd[0] = 0x41;
	sendall(s, cmd, 1);
	unsigned int dst[2];
	dst[0] = htonl(0x10502250);
	dst[1] = htonl(0x10502250+fsize);
	printf("Sending %i bytes\n", fsize);
	sendall(s, (unsigned char*)dst, 8);
	size_t remain = fsize;
	unsigned char *ptr = buf;
	while(remain > 0)
	{
		size_t sendsize = 0x400;
		if(remain < 0x400) sendsize = remain;
		sendall(s,ptr,sendsize);
		remain -= sendsize;
		ptr += sendsize;
	}
	shutdown(s,SD_SEND); //sent all we have
	recv(s, cmd, 1, 0); //lets see how tcpgecko reacted
	if(cmd[0] == 0xAA) printf("Transfer successful (%02x)!\n", cmd[0]);
	else printf("Transfer error occured (%02x)!\n", cmd[0]);
end:
	closesocket(s);
	WSACleanup();
	free(buf);
	waitforinput();
}
//simple socket send helper function
void sendall(SOCKET s, unsigned char *data, size_t size)
{
	size_t remain = size;
	while(remain > 0)
	{
		int sent = send(s, data, remain, 0);
		remain -= sent;
		data += sent;
	}
}
//cant get simpler than that
void waitforinput()
{
	printf("Press any button to exit");
	getch();
}
