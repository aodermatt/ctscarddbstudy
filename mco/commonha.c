/***************************************************************************
 * HA 
 ***************************************************************************/
#include <commonha.h>

/*****************************************************
 *    Replica notifying procedure. 
 *    Just prints notifications in human-readable format
 *****************************************************/

void sample_HA_replica_notifying(  uint2 notification_code,  /* notification code */
                                uint4 param1,  /* reserved for special cases */
                                void* param2,  /* reserved for special cases */
                                void* context) /* pointer to the user-defined context */
{
    switch (notification_code)
    {
        default:
            printf("\n** Notification ** Replica's been notified code = %d, param1 = %u, param2 = %p\n",
                   notification_code, param1, param2);
            break;
        case MCO_REPL_NOTIFY_CONNECTED:
            printf("\n** Notification ** Replica's been connected\n");
            break;
        case MCO_REPL_NOTIFY_CONNECT_FAILED:
            printf("\n** Notification ** Connection failed error = %d\n", param1);
            break;
        case MCO_REPL_NOTIFY_DB_EQUAL:
            printf("\n** Notification ** Master & Replica databases are equal\n");
            break;
        case MCO_REPL_NOTIFY_DB_LOAD_BEGIN:
            printf("\n** Notification ** Replica database is being loaded\n");
            break;
        case MCO_REPL_NOTIFY_DB_LOAD_FAILED:
            printf("\n** Notification ** Database load's failed with error = %d\n", param1);
            break;

        case MCO_REPL_NOTIFY_DB_LOAD_OK:
            printf("\n** Notification ** Database's been loaded successfully\n");
            break;
        case MCO_REPL_NOTIFY_COMMIT_FAILED:
            printf("\n** Notification ** Commit's failed with error = %d\n", param1);
            break;

        case MCO_REPL_NOTIFY_REPLICA_STOPPED:
            {
                const char* reason;
                switch (param1)
                {
                default:
                    reason = "Replica stopped by a keysroke";
                    break;
                case MCO_HA_REPLICA_HANDSHAKE_FAILED:
                    reason = "MCO_HA_REPLICA_HANDSHAKE_FAILED";
                    break;
                case MCO_HA_REPLICA_CONNECTION_ABORTED:
                    reason = "MCO_HA_REPLICA_CONNECTION_ABORTED";
                    break;
                case MCO_HA_REPLICA_MASTER_REQUESTED_DISCONNECT:
                    reason = "MCO_HA_REPLICA_MASTER_REQUESTED_DISCONNECT";
                    break;
                case MCO_HA_REPLICA_STOPPED_BY_LOCAL_REQUEST:
                    reason = "MCO_HA_REPLICA_STOPPED_BY_LOCAL_REQUEST";
                    break;
                case MCO_HA_REPLICA_BECOMES_MASTER:
                    reason = "MCO_HA_REPLICA_BECOMES_MASTER";
                    break;
                }
                printf("\n** Notification ** Replica stopped with the reason: %d (%s)\n", param1, reason);
            }
            break;
        case MCO_REPL_NOTIFY_HOTSYNC:
            printf("\n** Notification ** Hot synchronization is being started\n");
            break;

        case MCO_REPL_NOTIFY_EOHOTSYNC:
            printf("\n** Notification ** Hot synchronization is complete\n");
            break;
        case MCO_REPL_NOTIFY_STATEFUL_SYNC:
            printf("\n** Notification ** Stateful synchronization is being started\n");
            break;

        case MCO_REPL_NOTIFY_STATEFUL_SYNC_END:
            printf("\n** Notification ** Stateful synchronization is complete\n");
            break;

        case MCO_REPL_NOTIFY_MASTER_DB_EXTENDED: 
            {
                mco_size_t size = *((mco_size_t*) param2);
                printf("\n** Notification ** Master's database was extended, extend size %d bytes\n", (int) size);
                break;
            }
        case MCO_REPL_NOTIFY_MASTER_DB_CLEANED: 
            {
                printf("\n** Notification ** Database was cleaned\n");
                break;
            }
        case MCO_REPL_NOTIFY_SCHEMA_CHANGED: 
            {
                printf("\n** Notification ** Database schema was changed\n");
                break;
            }
    }
}
