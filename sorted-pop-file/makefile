# $ make GEN_COUNT=3 etc will override macro assignment here per standard make 
# usage. sks is the text based salted key extension
UNSORTED_FILENAME = unsorted.sks
SORTED_FILENAME = sorted.sks
GEN_COUNT = 20000000

deploy : 
	g++ -std=c++11 -I../dbcmn ../dbcmn/saltedkey.cpp main-pop-gen.cpp -o mpg
	time ./mpg $(UNSORTED_FILENAME) $(GEN_COUNT)
	time sort $(UNSORTED_FILENAME) -o $(SORTED_FILENAME)
	mv $(SORTED_FILENAME) ../deploy
	ls -la ../deploy/$(SORTED_FILENAME)

