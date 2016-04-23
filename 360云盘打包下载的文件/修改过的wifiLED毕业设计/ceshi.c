//client code
#include <winsock2.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#pragma comment(lib,"ws2_32.lib")	//��ws2_32.lib�ӵ�Linkҳ�����ӿ�
//#define IP "172.18.68.243"		//����̨������ϲ��ԣ�IPΪServer�˵�IP��ַ
#define IP "192.168.1.162"			//��һ̨������ϲ��ԣ�IPΪ���ػ��͵�ַ
#define PORT 8899					//ע�⣺�ͻ�������ͨ�ŵĶ˿� = ����˵Ķ˿�
#define BUFFER_SIZE 1024			//���ݷ��ͻ�������С
int main()
{
    int  cnt;
    char buf[BUFFER_SIZE];								//buf�����ſͻ��˷��͵���Ϣ
    int inputLen;										//���������ַ���������
    while(1)
    {
        printf("C://Socket/Client>");
        inputLen=0;
        memset(buf,0,sizeof(buf));                      //���Ѿ������ڴ�ռ�buf����n���ֽڵ�ֵ��Ϊo
        while((buf[inputLen++]=getchar())!='\n')		//�����Իس���Ϊ������ʶ
        {
           ;
        }
        if(buf[0]=='e' && buf[1]=='x' && buf[2]=='i' && buf[3]=='t')
        {
            printf("The End./n");
            //break;
        }
        WSADATA WSAData;
        if(WSAStartup(MAKEWORD(2,0),&WSAData)==SOCKET_ERROR)    //WSAStartup()������Winsock DLL���г�ʼ��
        {
            printf("Socket initialize fail!/n");
            continue;
        }
        SOCKET sock;											//�ͻ��˽��̴����׽���
        if((sock=socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR)  //�������׽��֣������˱���һ�£�
        {
            printf("Socket create fail!/n");
            WSACleanup();
            continue;
        }
        Fcntl(sock,F_SETFL,O_NONBLOCK);
        struct sockaddr_in ClientAddr;				                                //sockaddr_in�ṹ������ʶTCP/IPЭ���µĵ�ַ����ǿ��ת��Ϊsockaddr�ṹ
        ClientAddr.sin_family=AF_INET;				                                //ָInternet��
        ClientAddr.sin_port=htons(PORT);			                                //ָ���������Ԥ���Ķ˿�
        ClientAddr.sin_addr.s_addr=inet_addr(IP);	                                //ָ����������󶨵�IP��ַ
        if(connect(sock,(LPSOCKADDR)&ClientAddr,sizeof(ClientAddr))==SOCKET_ERROR)  //����connect()����������������̷�����������
        {
            printf("Connect fail!/n");
            closesocket(sock);
            WSACleanup();
            continue;
        }
        send(sock,buf,BUFFER_SIZE,0);				 //���������������
        cnt=recv(sock,buf,BUFFER_SIZE,0);
        if(cnt<0)
        {
          send(sock,buf,BUFFER_SIZE,0);
        }

        //puts(buf);
        closesocket(sock);							 //�ر��׽���

       // WSACleanup();								//��ֹ��Winsock DLL��ʹ�ã����ͷ���Դ���Ա���һ��ʹ��
    }
        return 0;
}
