CC=g++
CPPFLAGS=-g -Wall -std=c++11 -pedantic

INCLUDES= -I.

BQPP_TEST_OBJ=BQpptest.o
BQPP_TEST=bqpptest



EXEC_DIR=.


%.o : %.cpp
	$(CC)  -c $< -o $@ $(CPPFLAGS)


$(BQPP_TEST): $(BQPP_TEST_OBJ)
	$(CC) $(CPPFLAGS) -o $(EXEC_DIR)/$@ $(BQPP_TEST_OBJ) $(INCLUDES)




all:
	make $(BQPP_TEST)





clean:
	(rm -f *.o;)
	rm -f $(BQPP_TEST)

