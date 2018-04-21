/*FTP server*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>			//for close(fd)
/*for getting file size using stat()*/
#include <sys/stat.h>  /*for sendfile()*/
#include <sys/sendfile.h>   /*for O_RDONLY*/
#include <fcntl.h>
 #include <errno.h>

int main(int argc,char *argv[])
{
  struct sockaddr_in server, client;
  struct stat obj;
  int sfd1, nsfd;
  char buf[100], command[5], filename[20];
  int k, i, size, len, c;
  int filehandle;
  sfd1 = socket(AF_INET, SOCK_STREAM, 0);
  if(sfd1 == -1)
    {
      printf("Socket creation failed");
      exit(1);
    }
  server.sin_port = atoi(argv[1]);
  server.sin_family=AF_INET;
  server.sin_addr.s_addr =0;
  k = bind(sfd1,(struct sockaddr*)&server,sizeof(server));
  perror("bind");
  if(k == -1)
    {
      printf("Binding error");
      exit(1);
    }
  k = listen(sfd1,10);
  if(k == -1)
    {
      printf("Listen failed");
      exit(1);
    }
  len = sizeof(client);
  nsfd = accept(sfd1,(struct sockaddr*)&client, &len);
  i = 1;
  while(1)
    {
      recv(nsfd, buf, 100, 0);
     // printf("%s\n",buf );
     sscanf(buf, "%s", command);
      if(!strcmp(command, "ls"))
	{
	  system("ls >temps.txt");
	  i = 0;
	  stat("temps.txt",&obj);
	  size = obj.st_size;
	  send(nsfd, &size, sizeof(int),0);
	  filehandle = open("temps.txt", O_RDONLY);
	  sendfile(nsfd,filehandle,NULL,size);
	}
      else if(!strcmp(command,"get"))
	{
	  sscanf(buf, "%s%s", filename, filename);
	  stat(filename, &obj);
	  filehandle = open(filename, O_RDONLY);
	  size = obj.st_size;
	  if(filehandle == -1)
	      size = 0;
	  send(nsfd, &size, sizeof(int), 0);
	  if(size)
	  sendfile(nsfd, filehandle, NULL, size);
      
	}
      else if(!strcmp(command, "put"))
        {
	  int c = 0, len;
	  char *f;
	  sscanf(buf+strlen(command), "%s", filename);
	  recv(nsfd, &size, sizeof(int), 0);
	  i = 1;
	  while(1)
	    {
	      filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
	      if(filehandle == -1)
		{
		  sprintf(filename + strlen(filename), "%d", i);
		}
	      else
		break;
	    }
	  f = malloc(size);
	  recv(nsfd, f, size, 0);
	  c = write(filehandle, f, size);
	  close(filehandle);
	  send(nsfd, &c, sizeof(int), 0);
        }
      else if(!strcmp(command, "pwd"))
	{
	  system("pwd>temp.txt");
	  i = 0;
          FILE*f = fopen("temp.txt","r");
          while(!feof(f))
            buf[i++] = fgetc(f);
          buf[i-1] = '\0';
	  fclose(f);
          send(nsfd, buf, 100, 0);
	}
      else if(!strcmp(command, "cd"))
        {
          if(chdir(buf+3) == 0)
	    c = 1;
	  else
	    c = 0;
          send(nsfd, &c, sizeof(int), 0);
        }
      else if(!strcmp(command, "bye") || !strcmp(command, "quit"))
	{
	  printf("FTP server quitting..\n");
	  i = 1;
	  send(nsfd, &i, sizeof(int), 0);
	  exit(0);
	}
    }
  return 0;
}
 
