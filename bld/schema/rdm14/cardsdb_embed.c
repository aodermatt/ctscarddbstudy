/*
 * Raima file
 *
 * Copyright (c) 2016 by Raima Inc.
 * All rights reserved.
 *
 */

#include "rdm.h"
#include "rdmapi.h"
#include "cardsdb_embed.h"

static RDM_RETCODE embed_cardsdb_create (
    RDM_TFS     tfs,
    const char *nameSpace,
    const char *optString)
{
    RDM_RETCODE   rc;
    RDM_DB        db = NULL;
    const char   *dbNameSpec = NULL;
    const char   *ns = "";
    EMBED_PARAMS  params;

    memset(&params, 0, sizeof(EMBED_PARAMS));
    if ((rc = b_embed_fileGetOpts(optString, &params)) != sOKAY)
    {
        return rc;
    }

    if (nameSpace && nameSpace[0])
    {
        ns = nameSpace;
    }

    if (params.tfs)
    {
       dbNameSpec = psp_makeString("%s/%scardsdb", params.tfs, ns);
    }
    else
    {
       dbNameSpec = psp_makeString("%scardsdb", ns);
    }

    if (dbNameSpec == NULL)
    {
        rc = eNOMEMORY;
    }
    else
    {
        rc = rdm_tfsAllocDatabase(tfs, &db);
        if (rc == sOKAY)
        {
            rc = rdm_dbSetCatalog(db, cardsdb_cat);
            if (rc == sOKAY)
            {
                rc = rdm_dbOpen(db, dbNameSpec, RDM_OPEN_EXCLUSIVE);
                if (rc == sOKAY)
                {
                    rc = rdm_dbDeleteAllRowsFromDatabase(db);
                    (void) rdm_dbClose(db);
                }
            }
            (void) rdm_dbFree(db);
        }
    }

    psp_freeMemory(params.tfs, TAGL);
    psp_freeMemory(dbNameSpec, TAGL);

    return rc;
}

static RDM_RETCODE embed_cardsdb_delete (
    RDM_TFS     tfs,
    const char *nameSpace,
    const char *optString)
{
    RDM_RETCODE   rc;
    const char   *dbNameSpec = NULL;
    const char   *ns = "";
    EMBED_PARAMS  params;
    int32_t       count = 0;

    memset(&params, 0, sizeof(EMBED_PARAMS));
    if ((rc = b_embed_fileGetOpts(optString, &params)) != sOKAY)
    {
        return rc;
    }

    if (nameSpace && nameSpace[0])
    {
        ns = nameSpace;
    }

    if (params.tfs)
    {
       dbNameSpec = psp_makeString("%s/%scardsdb", params.tfs, ns);
    }
    else
    {
       dbNameSpec = psp_makeString("%scardsdb", ns);
    }
    if (dbNameSpec == NULL)
    {
        rc = eNOMEMORY;
    }
    else
    {
        while ((rc = rdm_tfsDropDatabase(tfs, dbNameSpec)) == eEXCLUSIVE)
        {
            /* Wait up to two seconds for other users to finish */
            if (++count == 20)
                break;
            psp_sleep(100);
        }

        if (rc == eTFS_INVDBID)
        {
           rc = sOKAY;
        }
    }

    psp_freeMemory(params.tfs, TAGL);
    psp_freeMemory(dbNameSpec, TAGL);

    return rc;
}


RDM_RETCODE embed_cardsdb_cat(
    const char        *fileName,
    B_EMBED_COMMAND    command,
    const char        *nameSpace,
    RDM_TFS            tfs,
    const char        *optString)
{
    RDM_RETCODE rc = sOKAY;
    uint8_t fileFound = fileName ? 0 : 1;

    if (nameSpace && strlen (nameSpace) > 128)
    {
        rc = eEMBED_ILLEGAL_NAMESPACE;
    }
    if (rc == sOKAY && (fileName==NULL || strcmp (fileName, "cardsdb") == 0))
    {
        fileFound = 1;
        if (command == EMBED_CREATE)
        {
            rc = embed_cardsdb_create (tfs, nameSpace, optString);
        }
        else if (command == EMBED_DELETE)
        {
            rc = embed_cardsdb_delete (tfs, nameSpace, optString);
        }
        else
        {
            rc = eEMBED_UNKNOWN_COMMAND;
        }
    }
    if (rc == sOKAY && fileFound == 0)
    {
        rc = eEMBED_FILE_NOT_FOUND;
    }
    return rc;
}
