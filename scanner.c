#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>


// Globals
char host[] = "127.0.0.1";
int portsOpen = 0;
pthread_mutex_t mutex;


// Structs

struct ports{
	int start;
	int end;
};



// Methods
void scan(void *inputPorts){
	struct sockaddr_in addr;
	int curr = ((struct ports*)inputPorts)->start;
	int last = ((struct ports*)inputPorts)->end;
	for(int i=curr; i<=last;i++){
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		if(fd < 0){
		  exit(1);
		}
		addr = *((struct  sockaddr_in*)malloc(sizeof(struct sockaddr_in)));
		inet_pton(fd, (char *)host, &addr.sin_addr);
		//printf("scanning: %d\n", i);
		
		
		addr.sin_family = AF_INET;
		addr.sin_port = htons(i);
		if(connect(fd, (const struct sockaddr *)&addr, sizeof(addr)) >= 0){
			printf("%d open\n", i);
			
			// Lock and unlock so we don't overwrite
			pthread_mutex_lock(&mutex);
			portsOpen++;
			pthread_mutex_unlock(&mutex);
			
		}
		close(fd);
	}
}

int main(){
    
	// Set up ports
	struct ports *toScan = (struct ports*)malloc(sizeof(struct ports));
	toScan->start = 0;
	toScan->end = 30000;
	
	struct ports *secondToScan = (struct ports*)malloc(sizeof(struct ports));
	secondToScan->start = 30001;
	secondToScan->end = 65535;
	
	// threads
	pthread_mutex_init(&mutex, NULL);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, (void *)scan, (void *)toScan);
	pthread_create(&t2, NULL, (void *)scan, (void *)secondToScan);
	
	// wait for threads to finish
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	pthread_mutex_destroy(&mutex);
	printf("\n\n !!!!!!!! Found %d ports open !!!!!!!!\n", portsOpen);

    
    
    

}
