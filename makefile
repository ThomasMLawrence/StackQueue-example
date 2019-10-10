CXX = g++
CLFAGS = -Wall -Wextra -Werror
DEBUG = -g
OBJS = main.o list.o help.o vehicle.o 

make: $(OBJS)
	$(CXX) $(CFLAGS) -o vehicle_rental $(OBJS)

debug: $(OBJS)
	$(CXX) $(CFLAGS) $(DEBUG) -o vehicle_rental $(OBJS)

clear: $(OBJS)	
	rm -rvf $(OBJS) vehicle_rental

clean: $(OBJS)
	rm -rvf vehicle_rental
