#include <cstdint>
#define DEBUGPIPE 1
#include "child.h"
#include "child_private.h"
#include "../steamshim.h"
#include "../steamshim_private.h"
#include "../os.h"
#include "../steamshim_types.h"

int GArgc = 0;
char **GArgv = NULL;

static int initPipes(void)
{
    char buf[64];
    unsigned long long val;

    if (!getEnvVar("STEAMSHIM_READHANDLE", buf, sizeof (buf)))
        return 0;
    else if (sscanf(buf, "%llu", &val) != 1)
        return 0;
    else
        GPipeRead = (PipeType) val;

    if (!getEnvVar("STEAMSHIM_WRITEHANDLE", buf, sizeof (buf)))
        return 0;
    else if (sscanf(buf, "%llu", &val) != 1)
        return 0;
    else
        GPipeWrite = (PipeType) val;
    
    return ((GPipeRead != NULLPIPE) && (GPipeWrite != NULLPIPE));
} /* initPipes */

extern "C" {
  int STEAMSHIM_init(void)
  {
      dbgpipe("Child init start.\n");
      if (!initPipes())
      {
          dbgpipe("Child init failed.\n");
          return 0;
      } /* if */

#ifndef _WIN32
      signal(SIGPIPE, SIG_IGN);
#endif

      dbgpipe("Child init success!\n");
      return 1;
  } /* STEAMSHIM_init */

  void STEAMSHIM_deinit(void)
  {
      dbgpipe("Child deinit.\n");
      if (GPipeWrite != NULLPIPE)
      {
          // writeBye();
          closePipe(GPipeWrite);
      } /* if */

      if (GPipeRead != NULLPIPE)
          closePipe(GPipeRead);

      GPipeRead = GPipeWrite = NULLPIPE;

#ifndef _WIN32
      signal(SIGPIPE, SIG_DFL);
#endif
  } /* STEAMSHIM_deinit */

  static inline int isAlive(void)
  {
      return ((GPipeRead != NULLPIPE) && (GPipeWrite != NULLPIPE));
  } /* isAlive */

  static inline int isDead(void)
  {
      return !isAlive();
  } /* isDead */

  int STEAMSHIM_alive(void)
  {
      return isAlive();
  } /* STEAMSHIM_alive */

  const STEAMSHIM_Event *STEAMSHIM_pump(void)
  {
    // Write1ByteMessage(SHIMCMD_PUMP);
  } 

  void STEAMSHIM_getSteamID()
  {
	  Write1ByteMessage(SHIMCMD_REQUESTSTEAMID);
  }

  void STEAMSHIM_getPersonaName(){
      // write1ByteCmd(SHIMCMD_REQUESTPERSONANAME);
  }

  void STEAMSHIM_getAuthSessionTicket(){
      // write1ByteCmd(SHIMCMD_REQUESTAUTHSESSIONTICKET);
  }
  void STEAMSHIM_beginAuthSession(uint64_t steamid, SteamAuthTicket_t* ticket){
      // printf("stewamid: %llu, %llu, -ticket- \n",steamid,ticket->pcbTicket);
      // PIPE_Init();
      // PIPE_WriteLong(steamid);
      // PIPE_WriteLong(ticket->pcbTicket);
      // PIPE_WriteData(ticket->pTicket, AUTH_TICKET_MAXSIZE);
      // PIPE_SendCmd(SHIMCMD_BEGINAUTHSESSION);
  }

  void STEAMSHIM_setRichPresence(const char* key, const char* val){
      // uint8 buf[256];
      // uint8 *ptr = buf+1;
      // *(ptr++) = (uint8) SHIMCMD_SETRICHPRESENCE;
      // strcpy((char *) ptr, key);
      // ptr += strlen(key) + 1;
      // strcpy((char *) ptr, val);
      // ptr += strlen(val) + 1;
      // buf[0] = (uint8) ((ptr-1) - buf);
      // writePipe(GPipeWrite, buf, buf[0] + 1);
  }
}

// what the hell?
void *__gxx_personality_v0;