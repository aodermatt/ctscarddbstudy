/******************************************************************************* 
Import rules used to derive data modeling: 
 
"2" -- Sequence number 20 Bytes maximum. 
The Sequence number is not saved with the record but saved to know up to where 
the data was updated. 
"A" Ð One Byte which can be ÒAÓ for ADD entry or ÒDÓ for delete entry, 
A is also use for an update.

"1" Ð One byte Token type Ò1Ó for Smart Card, Ò2Ó for open payment card.

"3915" Ð 4 Bytes Last for digit of the card.
"aECUzVA3J5wjAsT9uVM/LJ/bfh8b7rpGsWA//EYaSwo=" Ð 45 Bytes for token digest in 
base 64, the key for the entry. 
"Op1^Op2^Op3" Ð Up to 500 Bytes of data as defined but in reality no more than 
100 bytes, also we will push to redesign this so only a long integer is use as 
a reference to a definition of the access rules. 
Assume 250 bytes for now for 30% of the entry.

*******************************************************************************/ 


#ifndef LAST_CARD_DIGITS_SZ
#define LAST_CARD_DIGITS_SZ 4  /* remove if can express as unsigned short */
#endif

#ifndef TOKEN_DIGEST_SZ
#define TOKEN_DIGEST_SZ  35     /* reduced from 45 */
#endif

#ifndef ACCESS_RULES_SZ
#define ACCESS_RULES_SZ 500
#endif

/* 32766 appears to be the maximum page file size */

#ifndef CARD_INFO_DATA_PGSZ  
#define CARD_INFO_DATA_PGSZ 32766
#endif

#ifndef TOKEN_DIGEST_KEY_PGSZ  
#define TOKEN_DIGEST_KEY_PGSZ 32766
/*#define TOKEN_DIGEST_KEY_PGSZ 1024*/
#endif

#ifndef CARD_ACCESS_RULES_PGSZ
#define CARD_ACCESS_RULES_PGSZ 32766
#endif

#ifndef TOKEN_DIGEST_HASHSZ 
#define TOKEN_DIGEST_HASHSZ 20000000    /* 20 million records */
#endif

database cardsdb
{
    data file [CARD_INFO_DATA_PGSZ] "cards.d01" contains card_info;
    data file [CARD_ACCESS_RULES_PGSZ] "cards.d02" contains card_access_rules;
    /*hash file [TOKEN_DIGEST_KEY_PGSZ] "cards.h01" size=TOKEN_DIGEST_HASHSZ contains token_digest;*/
    key file [TOKEN_DIGEST_KEY_PGSZ] "cards.k01" contains token_digest;

    record card_info
    {
        /* direct access to card_access_rules using a record db address ptr */ 
        DB_ADDR access_rules_record_addr; 

        /* high nybble - 0:smart card type, 1:open access card type */ 
        /* low nybble - 0:positive list record, 1:negative list record */
        unsigned char card_access_type;     

        /* salted card number */
        /* key unsigned char token_digest[TOKEN_DIGEST_SZ]; */
        unique key binary token_digest[TOKEN_DIGEST_SZ];
        /*hash uint64_t token_digest[5];*/

        /* digits could include A-Z or 0-9 - otherwise make it an */
        /* unsigned short type to reduce by 2 bytes */ 
        char last_digits[LAST_CARD_DIGITS_SZ];
    }

    /* meta data that describes card usage specification */
    record card_access_rules
    {
        unsigned char access_data[ACCESS_RULES_SZ];
    }

} 


