CC = g++
LIST = adj_list
WEIGHT = weighted_graph
MTX = adj_matrix
STATS = graph_statistics

BUILD = build
STRUCT = structures
GRAPHS = graphs
ALG = algorithms
SEARCH = search
PARSE = parser
UTILS = utils

comp_file = $(CC) $(1).cpp $(addprefix $(BUILD)/,$(addsuffix .o,$(2))) -o $(BUILD)/$(1).out

main: $(LIST) $(WEIGHT) $(SEARCH) $(PARSE) $(STATS)
	$(call comp_file,main,$(LIST) $(WEIGHT) $(SEARCH) $(PARSE) $(STATS))

$(GRAPHS): $(LIST) $(WEIGHT) $(MTX)

$(LIST): $(BUILD)
	$(CC) -c $(STRUCT)/$(LIST).cpp -o $(BUILD)/$(LIST).o

$(WEIGHT): $(BUILD)
	$(CC) -c $(STRUCT)/$(WEIGHT).cpp -o $(BUILD)/$(WEIGHT).o

$(MTX): $(BUILD)
	$(CC) -c $(STRUCT)/$(MTX).cpp -o $(BUILD)/$(MTX).o

$(SEARCH): $(BUILD) 
	$(CC) -c $(ALG)/$(SEARCH).cpp -o $(BUILD)/$(SEARCH).o

$(STATS): $(BUILD)
	$(CC) -c $(ALG)/$(STATS).cpp -o $(BUILD)/$(STATS).o

$(PARSE): $(BUILD) 
	$(CC) -c $(UTILS)/$(PARSE).cpp -o $(BUILD)/$(PARSE).o

$(BUILD):
	mkdir -p $(BUILD)
