#ifndef __MCO_HA_SAMPLES_COMMON_H
#define __MCO_HA_SAMPLES_COMMON_H

#ifdef _WIN32
#pragma warning ( disable:4311)
#pragma warning ( disable:4312)
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/*********************************************************************
 * definitions of HA
 *********************************************************************/
#include <mcoha.h>
#include <common.h>

#if defined(_LINUX) || defined(_SOLARIS) || defined(_QNX) || defined(_HPUX) || defined(_AIX)
    #include <signal.h>

    #define DEFINE_PROCESS_MASKS(set) sigset_t set;

    #define CLEAR_PROCESS_MASKS(set) \
    sigemptyset(&set);         \
    sigprocmask(SIG_SETMASK,&set, 0);\

    #define SET_PROCESS_MASK(set,mask) \
    sigaddset(&set,mask);    \
    sigprocmask(SIG_SETMASK,&set, 0);\

    #define PROCESS_MASKS() \
    CLEAR_PROCESS_MASKS(set); \
    SET_PROCESS_MASK(set,SIGPIPE);
#endif
#ifdef _WIN32
    #define DEFINE_PROCESS_MASKS(set)
    #define PROCESS_MASKS() 
#endif
#ifdef _VXWORKS
    #define DEFINE_PROCESS_MASKS(set)
    #define PROCESS_MASKS() 
#endif
#ifdef _INTEGRITY
    #define DEFINE_PROCESS_MASKS(set)
    #define PROCESS_MASKS() 
#endif
#ifdef _ECOS
    #define DEFINE_PROCESS_MASKS(set)
    #define PROCESS_MASKS() 
#endif

/* define master name and connection string for different NW libraries. */
#if defined(CFG_TCP) || defined(CFG_UDP)
    #define nw_MasterName            "10000"    /* port number */
    #define nw_ConnectionString      "127.0.0.1:10000"  /* hostname:port. Port should be the same as nw_MasterName */
#elif defined(CFG_PIPES)  
    #ifdef _WIN32
        #define nw_MasterName        "\\\\.\\pipe\\test00"     /*  pipename */
        #define nw_ConnectionString  "\\\\.\\pipe\\test00"    
    #else 
        #define nw_MasterName        "/tmp/test00"
        #define nw_ConnectionString  "/tmp/test00"
    #endif 
#else
    #define nw_MasterName            ""
    #define nw_ConnectionString      ""
#endif

#define MCAST_REPEAT_COUNTER        3  /* counter of the number of attempts to repeat commit when replica doesn't answer */
#define MULTICAST_BASEPORT      10100  /* base port for multicast replication */
#define MAX_REPLICAS               10  /* max number of replicas */

#define LOOP_COUNT          50000  /* total number of transactions */
#define REPORT_COUNTER       1000  /* number of transactions in report */

#define CONNECT_TIMEOUT    (2 * 1000)

void sample_HA_replica_notifying(  uint2 notification_code,  /* notification code */
                                uint4 param1,  /* reserved for special cases */
                                void* param2,  /* reserved for special cases */
                                void* context); /* pointer to the user-defined context */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MCO_HA_SAMPLES_COMMON_H */
