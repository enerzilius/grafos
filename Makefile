CC = g++
LIST = adj_list
MTX = adj_matrix

GRAPHS = graphs
BUILD = build
STRUCT = structures

comp_file = $(CC) $(1).cpp $(BUILD)/$(2).o -o $(BUILD)/$(1).out

main: $(LIST) 
	$(call comp_file,main,$(LIST))

$(GRAPHS): $(LIST) $(MTX)

$(LIST):
	$(CC) -c $(STRUCT)/$(LIST).cpp -o $(BUILD)/$(LIST).o

$(MTX):
	$(CC) -c $(STRUCT)/$(MTX).cpp -o $(BUILD)/$(MTX).o