CC = gcc
OBJS = election.o area.o utilities.o electionTestsExample.o node_key_value.o
EXEC = election
DEBUG_FLAG = #Currently none
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@  -L. -lmap

election.o: election.c election.h mtm_map/map.h area.h utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

area.o: area.c area.h mtm_map/map.h utilities.h node_key_value.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

utilities.o: utilities.c utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

node_key_value.o: node_key_value.c node_key_value.h utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

electionTestsExample.o: tests/electionTestsExample.c election.h mtm_map/map.h test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tests/$*.c

clean:
	rm -f $(OBJS) $(EXEC)