CC = g++
LIST = adj_list
MTX = adj_matrix

BUILD = build
STRUCT = structures
GRAPHS = graphs
ALG = algorithms
SEARCH = search

comp_file = $(CC) $(1).cpp $(BUILD)/$(2).o -o $(BUILD)/$(1).out

main: $(LIST) $(SEARCH)
	$(call comp_file,main,$(LIST))

$(GRAPHS): $(LIST) $(MTX)

$(LIST): $(BUILD)
	$(CC) -c $(STRUCT)/$(LIST).cpp -o $(BUILD)/$(LIST).o

$(MTX): $(BUILD)
	$(CC) -c $(STRUCT)/$(MTX).cpp -o $(BUILD)/$(MTX).o

$(SEARCH): $(BUILD) 
	$(CC) -c $(ALG)/$(SEARCH).cpp -o $(BUILD)/$(SEARCH).o

$(BUILD):
	mkdir -p $(BUILD)
