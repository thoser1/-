//client code
#include <winsock2.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#pragma comment(lib,"ws2_32.lib")	//把ws2_32.lib加到Link页的连接库
//#define IP "172.18.68.243"		//在两台计算机上测试，IP为Server端的IP地址
#define IP "192.168.1.162"			//在一台计算机上测试，IP为本地回送地址
#define PORT 8899					//注意：客户端设置通信的端口 = 服务端的端口
#define BUFFER_SIZE 1024			//数据发送缓冲区大小
int main()
{
    int  cnt;
    char buf[BUFFER_SIZE];								//buf数组存放客户端发送的消息
    int inputLen;										//用于输入字符自增变量
    while(1)
    {
        printf("C://Socket/Client>");
        inputLen=0;
        memset(buf,0,sizeof(buf));                      //将已经开辟内存空间buf的首n个字节的值设为o
        while((buf[inputLen++]=getchar())!='\n')		//输入以回车键为结束标识
        {
           ;
        }
        if(buf[0]=='e' && buf[1]=='x' && buf[2]=='i' && buf[3]=='t')
        {
            printf("The End./n");
            //break;
        }
        WSADATA WSAData;
        if(WSAStartup(MAKEWORD(2,0),&WSAData)==SOCKET_ERROR)    //WSAStartup()函数对Winsock DLL进行初始化
        {
            printf("Socket initialize fail!/n");
            continue;
        }
        SOCKET sock;											//客户端进程创建套接字
        if((sock=socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR)  //创建流套接字（与服务端保持一致）
        {
            printf("Socket create fail!/n");
            WSACleanup();
            continue;
        }
        Fcntl(sock,F_SETFL,O_NONBLOCK);
        struct sockaddr_in ClientAddr;				                                //sockaddr_in结构用来标识TCP/IP协议下的地址，可强制转换为sockaddr结构
        ClientAddr.sin_family=AF_INET;				                                //指Internet域
        ClientAddr.sin_port=htons(PORT);			                                //指定服务端所预留的端口
        ClientAddr.sin_addr.s_addr=inet_addr(IP);	                                //指定服务端所绑定的IP地址
        if(connect(sock,(LPSOCKADDR)&ClientAddr,sizeof(ClientAddr))==SOCKET_ERROR)  //调用connect()函数，向服务器进程发出连接请求
        {
            printf("Connect fail!/n");
            closesocket(sock);
            WSACleanup();
            continue;
        }
        send(sock,buf,BUFFER_SIZE,0);				 //向服务器发送数据
        cnt=recv(sock,buf,BUFFER_SIZE,0);
        if(cnt<0)
        {
          send(sock,buf,BUFFER_SIZE,0);
        }

        //puts(buf);
        closesocket(sock);							 //关闭套接字

       // WSACleanup();								//终止对Winsock DLL的使用，并释放资源，以备下一次使用
    }
        return 0;
}
