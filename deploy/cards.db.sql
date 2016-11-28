create table card_info(
    card_access_type char, 
    token_digest char(36) primary key not null,
    last_digts char(4),
    access_rules blob(500)
    );


