CC = gcc
OBJS = election.o area.o exutilities.o electionTestsExample.o nodekeyvalue.o
EXEC = election
DEBUG_FLAG = #Currently none
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@  -L. -lmap

election.o: election.c election.h mtm_map/map.h area.h exutilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

area.o: area.c area.h mtm_map/map.h exutilities.h nodekeyvalue.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

exUtilities.o: exutilities.c exutilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

nodeKeyValue.o: nodekeyvalue.c nodekeyvalue.h exutilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

electionTestsExample.o: tests/electionTestsExample.c election.h mtm_map/map.h test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tests/$*.c

clean:
	rm -f $(OBJS) $(EXEC)
