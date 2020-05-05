CC = gcc
OBJS = election.o area.o exUtilities.o electionTestsExample.o nodeKeyValue.o
EXEC = election
DEBUG_FLAG = #Currently none
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@  -L. -lmap

election.o: election.c election.h mtm_map/map.h area.h exUtilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

area.o: area.c area.h mtm_map/map.h exUtilities.h nodeKeyValue.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

exUtilities.o: exUtilities.c exUtilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

nodeKeyValue.o: nodeKeyValue.c nodeKeyValue.h exUtilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

electionTestsExample.o: tests/electionTestsExample.c election.h mtm_map/map.h test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tests/$*.c

clean:
	rm -f $(OBJS) $(EXEC)
