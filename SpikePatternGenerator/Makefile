prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: SpikePatternGenerator

SpikePatternGenerator: SpikePatternGenerator.c Gui.o Graphs.o ../Pattern/Pattern.o ../Randn/Randn.o ../../NeuroSim/Library/IzNeuron/Neuron.o ../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.o ../../NeuroSim/Library/Event/Event.o ../../NeuroSim/Library/Synapse/Synapse.o ../../NeuroSim/Library/Network/Network.o ../../NeuroSim/Library/IzNeuron/NeuronTypes.o ../DataHandling/DataHandling.o ../DataHandling/v0/DataFormat_v0.o ../../BlueSpike/Misc/Misc.o ../../BlueSpike/Library/NeuroStats/FiringRate.o
	$(CC) $(LXRT_CFLAGS) -o $@ $< Gui.o Graphs.o ../Pattern/Pattern.o ../Randn/Randn.o ../../NeuroSim/Library/IzNeuron/Neuron.o ../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.o ../../NeuroSim/Library/Event/Event.o ../../NeuroSim/Library/Synapse/Synapse.o ../../NeuroSim/Library/Network/Network.o ../../NeuroSim/Library/IzNeuron/NeuronTypes.o ../DataHandling/DataHandling.o ../DataHandling/v0/DataFormat_v0.o ../../BlueSpike/Misc/Misc.o ../../BlueSpike/Library/NeuroStats/FiringRate.o $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) 
	
Gui.o: Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	

Graphs.o: Graphs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 
	
../Pattern/Pattern.o: ../Pattern/Pattern.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 
	
../Randn/Randn.o: ../Randn/Randn.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 
	
../DataHandling/DataHandling.o: ../DataHandling/DataHandling.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		
	
../DataHandling/v0/DataFormat_v0.o: ../DataHandling/v0/DataFormat_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)	 			
	
../../NeuroSim/Library/Network/Network.o: ../../NeuroSim/Library/Network/Network.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		

../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.o: ../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	
	
../../NeuroSim/Library/Synapse/Synapse.o: ../../NeuroSim/Library/Synapse/Synapse.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	
	
../../NeuroSim/Library/Event/Event.o: ../../NeuroSim/Library/Event/Event.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		

../../NeuroSim/Library/IzNeuron/NeuronTypes.o: ../../NeuroSim/Library/IzNeuron/NeuronTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		
	
../../NeuroSim/Library/IzNeuron/Neuron.o: ../../NeuroSim/Library/IzNeuron/Neuron.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		
	
../../BlueSpike/Library/NeuroStats/FiringRate.o: ../../BlueSpike/Library/NeuroStats/FiringRate.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	
		
../../BlueSpike/Misc/Misc.o: ../../BlueSpike/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		# to see warnings
		
clean:
	rm -f *.o SpikePatternGenerator ../../NeuroSim/Library/IzNeuron/*.o ../../NeuroSim/Library/ParkerSochacki/*.o ../../NeuroSim/Library/Event/*.o ../../NeuroSim/Library/Synapse/*.o ../../NeuroSim/Library/Network/*.o ../Pattern/*.o ../Randn/*o ../DataHandling/*.o ../DataHandling/v0/*.o ../../BlueSpike/Misc/*.o ../../BlueSpike/Library/NeuroStats/*.o

.PHONY: clean

