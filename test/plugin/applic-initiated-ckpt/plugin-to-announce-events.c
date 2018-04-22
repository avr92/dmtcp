#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "dmtcp.h"

static void
applic_initiated_ckpt_event_hook(DmtcpEvent_t event, DmtcpEventData_t *data)
{
  /* NOTE:  See warning in plugin/README about calls to printf here. */
  switch (event) {
  case DMTCP_EVENT_INIT:
    printf("Plugin(%s:%d): initialization of plugin is complete.\n",
           __FILE__, __LINE__);
    break;
  case DMTCP_EVENT_EXIT:
    printf("Plugin(%s:%d): exiting.\n", __FILE__, __LINE__);
    break;

  default:
    break;
  }
}

static void
checkpoint()
{
  system("docker ps > file");
  system("python parse.py");
  int fd = open("filep",O_RDONLY);
  char buf[1000];
  int num = read(fd,buf,0);
  char cont[10][12];
  int i,j;
  for (i = 0;i<10;i++) {
    for (j=0; j<12; j++) {
      cont[i][j] = buf[j];
    }
  }
  printf("Here");
  for(j=0;j<12;j++){
    printf("%c",cont[1][j]);
  }
  
	printf("Done");
char cmd_rm[50];
    char cmd_create[50];
    char argv[3]; 
    strcpy(cmd_rm,"docker checkpoint rm ");
    strcpy(cmd_create,"docker checkpoint create ");
    argv[1] = cont[1];
	printf("%s",cont[1]);
    argv[2] = " ckp1";
    argv[3] = NULL;
    strcat(cmd_rm,argv);
    strcat(cmd_create,argv);
    system(cmd_rm);
    system(cmd_create);
    printf("CKP");
close(fd);
}
static void
resume()
{

  printf("Plugin(%s:%d): done checkpointing.\n", __FILE__, __LINE__);
}

static void
restart()
{
  system("docker start --checkpoint ckp1 looper");
  printf("Plugin(%s:%d): done restarting from checkpoint image.\n",
         __FILE__, __LINE__);
}

static DmtcpBarrier barriers[] = {
  { DMTCP_GLOBAL_BARRIER_PRE_CKPT, checkpoint, "checkpoint" },
  { DMTCP_GLOBAL_BARRIER_RESUME, resume, "resume" },
  { DMTCP_GLOBAL_BARRIER_RESTART, restart, "restart" }
};

DmtcpPluginDescriptor_t applic_initiated_ckpt_plugin = {
  DMTCP_PLUGIN_API_VERSION,
  DMTCP_PACKAGE_VERSION,
  "applic_initiated_ckpt",
  "DMTCP",
  "dmtcp@ccs.neu.edu",
  "Application-initiated checkpoint plugin",
  DMTCP_DECL_BARRIERS(barriers),
  applic_initiated_ckpt_event_hook
};

DMTCP_DECL_PLUGIN(applic_initiated_ckpt_plugin);
