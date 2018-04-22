#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char containers[20][100];

char deduplicated_container[20][100];

char container_is_dup[20];

int main()
{

	DIR *dirp;
	char path[50];
    struct dirent entry;
    struct dirent *endp;
    FILE *fp;

    int container_cnt = 0;

    if ((dirp = opendir("/proc")) == NULL)
        return -1;

    while(1)
    {
    	endp = NULL;
        if (readdir_r(dirp, &entry, &endp) == -1) {
            closedir(dirp);
            return -1;
        }
    
        if (endp == NULL)
            break;

        if (strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name, "..") == 0)
            continue;

        if (entry.d_name[0] > 48 && entry.d_name[0] <= 57)
        {
        	//printf("%s/%s\n", "/proc", entry.d_name);
        	char buff[100], docker_container[100];
        	sprintf(path, "/proc/%s/cgroup", entry.d_name);
        	//printf("%s\n", path);

        	fp = fopen(path, "r");
   			fscanf(fp, "%s", buff);

   			int i = 0, j= 0, cnt = 0;

   			while(buff[i] != '\0')
   			{	
   				if(cnt == 3) {
   					docker_container[j] = buff[i];
   					j++;
   				}

   				if (buff[i] == ':' && cnt < 2)
   				{
   					cnt++;
   				}

   				if (cnt == 2)
   					cnt++;
   				i++;
   			}
   			
   			if (j != 1) {
   				docker_container[j] = '\0';
   				printf("Docker container id: %s\n", docker_container);
   				int l = 8;
   				i = 0;
   				while(l < j) {
   					containers[container_cnt][i] = docker_container[l];
   					l++;
   					i++;
   				}
   				containers[container_cnt][i] = '\0';
          container_is_dup[container_cnt] = 'F';
   				container_cnt++;
        }	
        fclose(fp);
      }
    }

    int i = 0;
    while (i < container_cnt)
    {
      int j = i+1;
      if (container_is_dup[i] == 'T')
      {
        i++;
        continue;
      }

      while (j < container_cnt)
      {
        if(strcmp(containers[i], containers[j]) == 0) {
          container_is_dup[j] = 'T';
        }
        j++;
      }
      i++;
    }
    

    printf("\n List of container IDs: \n");
    int k = 0;
    while (k < container_cnt)
    {
      if(container_is_dup[k] == 'F')
    	 printf("%s\n", containers[k]);
    	k++;
    }

    return 0;
}