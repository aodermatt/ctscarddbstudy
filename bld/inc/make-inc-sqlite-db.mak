DB_SCHEMA_NAME = cards.db

gen-db : 
	cd $(RELATIVE_SCHEMAPATH) \
	&& rm -f $(DB_SCHEMA_NAME) \
	&& sqlite3 $(DB_SCHEMA_NAME) < $(DB_SCHEMA_NAME).sql \
	&& cp -f $(DB_SCHEMA_NAME) $(RELATIVE_DEPLOYPATH) \
	&& cp -f $(DB_SCHEMA_NAME).sql $(RELATIVE_DEPLOYPATH) \
	&& ls -l $(RELATIVE_DEPLOYPATH)/$(DB_SCHEMA_NAME).sql \
	&& ls -l $(RELATIVE_DEPLOYPATH)/$(DB_SCHEMA_NAME)

init-db : 
	@echo see gen-db copies/overwrites the cards.db file which does reset db



