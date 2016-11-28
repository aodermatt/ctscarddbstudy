/*
 * Raima Database Compiled Catalog Source File
 * This file is autogenerated, please don't edit the file
*/

#include "cardsdb_cat.h"

/* -- catalog in ASCII format -- 
{
  "database":{
    "catver":1,
    "dbver":1,
    "encryption":"none",
    "maxdrawers":50,
    "nodrawers":3,
    "nextdrawer":3,
    "nodoms":0,
    "maxdoms":0,
    "maxtabs":50,
    "notabs":2,
    "nexttab":2,
    "drawers":[
      {"dwrid":0,"tabid":"0(card_info)","srcid":0,"type":"table"},
      {"dwrid":1,"tabid":"0(card_info)","srcid":0,"type":"btree"},
      {"dwrid":2,"tabid":"1(card_access_rules)","srcid":1,"type":"table"}
    ],
    "tables":[
      {"tabid":0,"dwrid":0,"name":"card_info","type":"standard","nocols":4,"nextcol":4,"maxcols":20,"nokeys":1,"nextkey":1,"maxkeys":5,
        "columns":[
          {"colid":0,"name":"access_rules_record_addr","type":{"data_type":"uint64"},"not_null":"(null)","defValue":"0"},
          {"colid":1,"name":"card_access_type","type":{"data_type":"uint8"},"not_null":"(null)","defValue":"0"},
          {"colid":2,"name":"token_digest","type":{"data_type":"binary","length":35},"keyid":0,"usage":1,"not_null":"(null)"},
          {"colid":3,"name":"last_digits","type":{"data_type":"char","length":5},"not_null":"(null)","defValue":"\"\""}
        ],
        "keys":[
          {"keyid":0,"dwrid":1,"type":"unique","method":"btree","nocols":1,"cols":[{"colid":"2(token_digest)","order":"asc"}]}
        ]
      },
      {"tabid":1,"dwrid":2,"name":"card_access_rules","type":"standard","nocols":1,"nextcol":1,"maxcols":20,
        "columns":[
          {"colid":0,"name":"access_data","type":{"data_type":"binary","length":500},"not_null":"(null)","defValue":"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"}
        ]
      }
    ]
  }
}

*/

static const char cardsdb_cat_a[][1024] =
{
    {0x7B, 0x0A, 0x20, 0x20, 0x22, 0x64, 0x61, 0x74, 0x61, 0x62, 0x61,
     0x73, 0x65, 0x22, 0x3A, 0x7B, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x22,
     0x63, 0x61, 0x74, 0x76, 0x65, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x0A,
     0x20, 0x20, 0x20, 0x20, 0x22, 0x64, 0x62, 0x76, 0x65, 0x72, 0x22,
     0x3A, 0x31, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x22, 0x65, 0x6E,
     0x63, 0x72, 0x79, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x22, 0x3A, 0x22,
     0x6E, 0x6F, 0x6E, 0x65, 0x22, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20,
     0x22, 0x6D, 0x61, 0x78, 0x64, 0x72, 0x61, 0x77, 0x65, 0x72, 0x73,
     0x22, 0x3A, 0x35, 0x30, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x22,
     0x6E, 0x6F, 0x64, 0x72, 0x61, 0x77, 0x65, 0x72, 0x73, 0x22, 0x3A,
     0x33, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x22, 0x6E, 0x65, 0x78,
     0x74, 0x64, 0x72, 0x61, 0x77, 0x65, 0x72, 0x22, 0x3A, 0x33, 0x2C,
     0x0A, 0x20, 0x20, 0x20, 0x20, 0x22, 0x6E, 0x6F, 0x64, 0x6F, 0x6D,
     0x73, 0x22, 0x3A, 0x30, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x22,
     0x6D, 0x61, 0x78, 0x64, 0x6F, 0x6D, 0x73, 0x22, 0x3A, 0x30, 0x2C,
     0x0A, 0x20, 0x20, 0x20, 0x20, 0x22, 0x6D, 0x61, 0x78, 0x74, 0x61,
     0x62, 0x73, 0x22, 0x3A, 0x35, 0x30, 0x2C, 0x0A, 0x20, 0x20, 0x20,
     0x20, 0x22, 0x6E, 0x6F, 0x74, 0x61, 0x62, 0x73, 0x22, 0x3A, 0x32,
     0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x22, 0x6E, 0x65, 0x78, 0x74,
     0x74, 0x61, 0x62, 0x22, 0x3A, 0x32, 0x2C, 0x0A, 0x20, 0x20, 0x20,
     0x20, 0x22, 0x64, 0x72, 0x61, 0x77, 0x65, 0x72, 0x73, 0x22, 0x3A,
     0x5B, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7B, 0x22, 0x64,
     0x77, 0x72, 0x69, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x74, 0x61,
     0x62, 0x69, 0x64, 0x22, 0x3A, 0x22, 0x30, 0x28, 0x63, 0x61, 0x72,
     0x64, 0x5F, 0x69, 0x6E, 0x66, 0x6F, 0x29, 0x22, 0x2C, 0x22, 0x73,
     0x72, 0x63, 0x69, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x74, 0x79,
     0x70, 0x65, 0x22, 0x3A, 0x22, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x22,
     0x7D, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7B, 0x22,
     0x64, 0x77, 0x72, 0x69, 0x64, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x74,
     0x61, 0x62, 0x69, 0x64, 0x22, 0x3A, 0x22, 0x30, 0x28, 0x63, 0x61,
     0x72, 0x64, 0x5F, 0x69, 0x6E, 0x66, 0x6F, 0x29, 0x22, 0x2C, 0x22,
     0x73, 0x72, 0x63, 0x69, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x74,
     0x79, 0x70, 0x65, 0x22, 0x3A, 0x22, 0x62, 0x74, 0x72, 0x65, 0x65,
     0x22, 0x7D, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7B,
     0x22, 0x64, 0x77, 0x72, 0x69, 0x64, 0x22, 0x3A, 0x32, 0x2C, 0x22,
     0x74, 0x61, 0x62, 0x69, 0x64, 0x22, 0x3A, 0x22, 0x31, 0x28, 0x63,
     0x61, 0x72, 0x64, 0x5F, 0x61, 0x63, 0x63, 0x65, 0x73, 0x73, 0x5F,
     0x72, 0x75, 0x6C, 0x65, 0x73, 0x29, 0x22, 0x2C, 0x22, 0x73, 0x72,
     0x63, 0x69, 0x64, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x74, 0x79, 0x70,
     0x65, 0x22, 0x3A, 0x22, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x22, 0x7D,
     0x0A, 0x20, 0x20, 0x20, 0x20, 0x5D, 0x2C, 0x0A, 0x20, 0x20, 0x20,
     0x20, 0x22, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x73, 0x22, 0x3A, 0x5B,
     0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7B, 0x22, 0x74, 0x61,
     0x62, 0x69, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x64, 0x77, 0x72,
     0x69, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6E, 0x61, 0x6D, 0x65,
     0x22, 0x3A, 0x22, 0x63, 0x61, 0x72, 0x64, 0x5F, 0x69, 0x6E, 0x66,
     0x6F, 0x22, 0x2C, 0x22, 0x74, 0x79, 0x70, 0x65, 0x22, 0x3A, 0x22,
     0x73, 0x74, 0x61, 0x6E, 0x64, 0x61, 0x72, 0x64, 0x22, 0x2C, 0x22,
     0x6E, 0x6F, 0x63, 0x6F, 0x6C, 0x73, 0x22, 0x3A, 0x34, 0x2C, 0x22,
     0x6E, 0x65, 0x78, 0x74, 0x63, 0x6F, 0x6C, 0x22, 0x3A, 0x34, 0x2C,
     0x22, 0x6D, 0x61, 0x78, 0x63, 0x6F, 0x6C, 0x73, 0x22, 0x3A, 0x32,
     0x30, 0x2C, 0x22, 0x6E, 0x6F, 0x6B, 0x65, 0x79, 0x73, 0x22, 0x3A,
     0x31, 0x2C, 0x22, 0x6E, 0x65, 0x78, 0x74, 0x6B, 0x65, 0x79, 0x22,
     0x3A, 0x31, 0x2C, 0x22, 0x6D, 0x61, 0x78, 0x6B, 0x65, 0x79, 0x73,
     0x22, 0x3A, 0x35, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
     0x20, 0x20, 0x22, 0x63, 0x6F, 0x6C, 0x75, 0x6D, 0x6E, 0x73, 0x22,
     0x3A, 0x5B, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
     0x20, 0x20, 0x7B, 0x22, 0x63, 0x6F, 0x6C, 0x69, 0x64, 0x22, 0x3A,
     0x30, 0x2C, 0x22, 0x6E, 0x61, 0x6D, 0x65, 0x22, 0x3A, 0x22, 0x61,
     0x63, 0x63, 0x65, 0x73, 0x73, 0x5F, 0x72, 0x75, 0x6C, 0x65, 0x73,
     0x5F, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x5F, 0x61, 0x64, 0x64,
     0x72, 0x22, 0x2C, 0x22, 0x74, 0x79, 0x70, 0x65, 0x22, 0x3A, 0x7B,
     0x22, 0x64, 0x61, 0x74, 0x61, 0x5F, 0x74, 0x79, 0x70, 0x65, 0x22,
     0x3A, 0x22, 0x75, 0x69, 0x6E, 0x74, 0x36, 0x34, 0x22, 0x7D, 0x2C,
     0x22, 0x6E, 0x6F, 0x74, 0x5F, 0x6E, 0x75, 0x6C, 0x6C, 0x22, 0x3A,
     0x22, 0x28, 0x6E, 0x75, 0x6C, 0x6C, 0x29, 0x22, 0x2C, 0x22, 0x64,
     0x65, 0x66, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x22, 0x3A, 0x22, 0x30,
     0x22, 0x7D, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
     0x20, 0x20, 0x20, 0x7B, 0x22, 0x63, 0x6F, 0x6C, 0x69, 0x64, 0x22,
     0x3A, 0x31, 0x2C, 0x22, 0x6E, 0x61, 0x6D, 0x65, 0x22, 0x3A, 0x22,
     0x63, 0x61, 0x72, 0x64, 0x5F, 0x61, 0x63, 0x63, 0x65, 0x73, 0x73,
     0x5F, 0x74, 0x79, 0x70, 0x65, 0x22, 0x2C, 0x22, 0x74, 0x79, 0x70,
     0x65, 0x22, 0x3A, 0x7B, 0x22, 0x64, 0x61, 0x74, 0x61, 0x5F, 0x74,
     0x79, 0x70, 0x65, 0x22, 0x3A, 0x22, 0x75, 0x69, 0x6E, 0x74, 0x38,
     0x22, 0x7D, 0x2C, 0x22, 0x6E, 0x6F, 0x74, 0x5F, 0x6E, 0x75, 0x6C,
     0x6C, 0x22, 0x3A, 0x22, 0x28, 0x6E, 0x75, 0x6C, 0x6C, 0x29, 0x22,
     0x2C, 0x22, 0x64, 0x65, 0x66, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x22,
     0x3A, 0x22, 0x30, 0x22, 0x7D, 0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20,
     0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7B, 0x22, 0x63, 0x6F, 0x6C,
     0x69, 0x64, 0x22, 0x3A, 0x32, 0x2C, 0x22, 0x6E, 0x61, 0x6D, 0x65,
     0x22, 0x3A, 0x22, 0x74, 0x6F, 0x6B, 0x65, 0x6E, 0x5F, 0x64, 0x69,
     0x67, 0x65, 0x73, 0x74, 0x22, 0x2C, 0x22, 0x74, 0x79, 0x70, 0x65,
     0x22, 0x3A, 0x7B, 0x22, 0x64, 0x61, 0x74, 0x61, 0x5F, 0x74, 0x79,
     0x70, 0x65, 0x22, 0x3A, 0x22, 0x62, 0x69, 0x6E, 0x61, 0x72, 0x79,
     0x22, 0x2C, 0x22, 0x6C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x22, 0x3A,
     0x33, 0x35, 0x7D, 0x2C, 0x22, 0x6B, 0x65, 0x79, 0x69, 0x64, 0x22,
     0x3A, 0x30, 0x2C, 0x22, 0x75, 0x73, 0x61, 0x67, 0x65, 0x22, 0x3A,
     0x31, 0x2C, 0x22, 0x6E, 0x6F, 0x74, 0x5F, 0x6E, 0x75, 0x6C, 0x6C,
     0x22, 0x3A, 0x22, 0x28, 0x6E, 0x75, 0x6C, 0x6C, 0x29, 0x22, 0x7D,
     0x2C, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
     0x20, 0x7B, 0x22, 0x63, 0x6F, 0x6C, 0x69, 0x64, 0x22, 0x3A, 0x33,
     0x2C, 0x22, 0x6E, 0x61, 0x6D, 0x65, 0x22, 0x3A, 0x22, 0x6C, 0x61,
     0x73, 0x74, 0x5F, 0x64, 0x69, 0x67, 0x69, 0x74, 0x73, 0x22, 0x2C,
     0x22}, /*lint !e785 */
    {0x74, 0x79, 0x70, 0x65, 0x22, 0x3A, 0x7B, 0x22, 0x64, 0x61, 0x74,
     0x61, 0x5F, 0x74, 0x79, 0x70, 0x65, 0x22, 0x3A, 0x22, 0x63, 0x68,
     0x61, 0x72, 0x22, 0x2C, 0x22, 0x6C, 0x65, 0x6E, 0x67, 0x74, 0x68,
     0x22, 0x3A, 0x35, 0x7D, 0x2C, 0x22, 0x6E, 0x6F, 0x74, 0x5F, 0x6E,
     0x75, 0x6C, 0x6C, 0x22, 0x3A, 0x22, 0x28, 0x6E, 0x75, 0x6C, 0x6C,
     0x29, 0x22, 0x2C, 0x22, 0x64, 0x65, 0x66, 0x56, 0x61, 0x6C, 0x75,
     0x65, 0x22, 0x3A, 0x22, 0x5C, 0x22, 0x5C, 0x22, 0x22, 0x7D, 0x0A,
     0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5D, 0x2C, 0x0A,
     0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0x6B, 0x65,
     0x79, 0x73, 0x22, 0x3A, 0x5B, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
     0x20, 0x20, 0x20, 0x20, 0x20, 0x7B, 0x22, 0x6B, 0x65, 0x79, 0x69,
     0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x64, 0x77, 0x72, 0x69, 0x64,
     0x22, 0x3A, 0x31, 0x2C, 0x22, 0x74, 0x79, 0x70, 0x65, 0x22, 0x3A,
     0x22, 0x75, 0x6E, 0x69, 0x71, 0x75, 0x65, 0x22, 0x2C, 0x22, 0x6D,
     0x65, 0x74, 0x68, 0x6F, 0x64, 0x22, 0x3A, 0x22, 0x62, 0x74, 0x72,
     0x65, 0x65, 0x22, 0x2C, 0x22, 0x6E, 0x6F, 0x63, 0x6F, 0x6C, 0x73,
     0x22, 0x3A, 0x31, 0x2C, 0x22, 0x63, 0x6F, 0x6C, 0x73, 0x22, 0x3A,
     0x5B, 0x7B, 0x22, 0x63, 0x6F, 0x6C, 0x69, 0x64, 0x22, 0x3A, 0x22,
     0x32, 0x28, 0x74, 0x6F, 0x6B, 0x65, 0x6E, 0x5F, 0x64, 0x69, 0x67,
     0x65, 0x73, 0x74, 0x29, 0x22, 0x2C, 0x22, 0x6F, 0x72, 0x64, 0x65,
     0x72, 0x22, 0x3A, 0x22, 0x61, 0x73, 0x63, 0x22, 0x7D, 0x5D, 0x7D,
     0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5D, 0x0A,
     0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7D, 0x2C, 0x0A, 0x20, 0x20,
     0x20, 0x20, 0x20, 0x20, 0x7B, 0x22, 0x74, 0x61, 0x62, 0x69, 0x64,
     0x22, 0x3A, 0x31, 0x2C, 0x22, 0x64, 0x77, 0x72, 0x69, 0x64, 0x22,
     0x3A, 0x32, 0x2C, 0x22, 0x6E, 0x61, 0x6D, 0x65, 0x22, 0x3A, 0x22,
     0x63, 0x61, 0x72, 0x64, 0x5F, 0x61, 0x63, 0x63, 0x65, 0x73, 0x73,
     0x5F, 0x72, 0x75, 0x6C, 0x65, 0x73, 0x22, 0x2C, 0x22, 0x74, 0x79,
     0x70, 0x65, 0x22, 0x3A, 0x22, 0x73, 0x74, 0x61, 0x6E, 0x64, 0x61,
     0x72, 0x64, 0x22, 0x2C, 0x22, 0x6E, 0x6F, 0x63, 0x6F, 0x6C, 0x73,
     0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6E, 0x65, 0x78, 0x74, 0x63, 0x6F,
     0x6C, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6D, 0x61, 0x78, 0x63, 0x6F,
     0x6C, 0x73, 0x22, 0x3A, 0x32, 0x30, 0x2C, 0x0A, 0x20, 0x20, 0x20,
     0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0x63, 0x6F, 0x6C, 0x75, 0x6D,
     0x6E, 0x73, 0x22, 0x3A, 0x5B, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
     0x20, 0x20, 0x20, 0x20, 0x20, 0x7B, 0x22, 0x63, 0x6F, 0x6C, 0x69,
     0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6E, 0x61, 0x6D, 0x65, 0x22,
     0x3A, 0x22, 0x61, 0x63, 0x63, 0x65, 0x73, 0x73, 0x5F, 0x64, 0x61,
     0x74, 0x61, 0x22, 0x2C, 0x22, 0x74, 0x79, 0x70, 0x65, 0x22, 0x3A,
     0x7B, 0x22, 0x64, 0x61, 0x74, 0x61, 0x5F, 0x74, 0x79, 0x70, 0x65,
     0x22, 0x3A, 0x22, 0x62, 0x69, 0x6E, 0x61, 0x72, 0x79, 0x22, 0x2C,
     0x22, 0x6C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x22, 0x3A, 0x35, 0x30,
     0x30, 0x7D, 0x2C, 0x22, 0x6E, 0x6F, 0x74, 0x5F, 0x6E, 0x75, 0x6C,
     0x6C, 0x22, 0x3A, 0x22, 0x28, 0x6E, 0x75, 0x6C, 0x6C, 0x29, 0x22,
     0x2C, 0x22, 0x64, 0x65, 0x66, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x22,
     0x3A, 0x22, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30}, /*lint !e785 */
    {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x22, 0x7D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
     0x5D, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7D, 0x0A, 0x20,
     0x20, 0x20, 0x20, 0x5D, 0x0A, 0x20, 0x20, 0x7D, 0x0A, 0x7D, 0x0A,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00} /*lint !e785 */
};

const char * const cardsdb_cat= cardsdb_cat_a[0];