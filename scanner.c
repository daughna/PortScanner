#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(){
    char host[] = "127.0.0.1";

    
    
    struct sockaddr_in addr;
    for(int i=0; i<65535;i++){
      int fd = socket(AF_INET, SOCK_STREAM, 0);
      if(fd < 0){
        exit(1);
      }
      addr = *((struct  sockaddr_in*)malloc(sizeof(struct sockaddr_in)));
      inet_pton(fd, (char *)host, &addr.sin_addr);

      addr.sin_family = AF_INET;
      addr.sin_port = htons(i);
      if(connect(fd, (const struct sockaddr *)&addr, sizeof(addr)) >= 0){
        printf("%d open\n", i);
      }
      close(fd);
    }

}
