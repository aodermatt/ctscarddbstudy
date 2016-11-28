#ifndef CARDSDB_H
#define CARDSDB_H
/*lint ++flb */

/* Raima Database Manager 12.0.14.3256 */

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


/* database cardsdb record/key structure declarations */

struct card_info {
   DB_ADDR access_rules_record_addr;
   uint8_t card_access_type;
   uint8_t token_digest[35];
   char last_digits[4];
};

struct card_access_rules {
   uint8_t access_data[500];
};

/* record, field and set table entry definitions */

/* File Id Constants */

/* Record Name Constants */
#define CARD_INFO 10000
#define CARD_ACCESS_RULES 10001

/* Field Name Constants */
#define ACCESS_RULES_RECORD_ADDR 0L
#define CARD_ACCESS_TYPE 1L
#define TOKEN_DIGEST 2L
#define LAST_DIGITS 3L
#define ACCESS_DATA 1000L

/* Set Name Constants */

/* Field Sizes */
#define SIZEOF_ACCESS_RULES_RECORD_ADDR 16
#define SIZEOF_CARD_ACCESS_TYPE 1
#define SIZEOF_TOKEN_DIGEST 35
#define SIZEOF_LAST_DIGITS 4
#define SIZEOF_ACCESS_DATA 500

/*lint --flb */
#endif    /* CARDSDB_H */
