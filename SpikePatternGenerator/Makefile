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

SpikePatternGenerator: SpikePatternGenerator.c Gui.o SimulationView.o FiringRateView.o SimulationGraphs.o ../Pattern/Pattern.o ../../BlueSpike/Library/Misc/Randn.o ../../NeuroSim/Library/IzNeuron/Neuron.o ../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.o ../../NeuroSim/Library/Event/Event.o ../../NeuroSim/Library/Synapse/Synapse.o ../../NeuroSim/Library/Network/Network.o ../../NeuroSim/Library/IzNeuron/NeuronTypes.o ../DataHandling/DataHandling.o ../DataHandling/v0/DataFormat_v0.o ../../BlueSpike/Library/Misc/Misc.o ../../BlueSpike/Library/NeuroStats/FiringRate/FiringRate.o ../../BlueSpike/Library/NeuroStats/FiringRate/FiringRateGraph.o ../../TrialControllers/Library/TrialStats/TrialStats.o ../../TrialControllers/Library/TrialTypes/TrialTypes.o ../../NeuroSim/Library/Combos/LayerNrnGrpNeuronCombo.o ../../TrialControllers/Library/Combos/TrialTypesCombo.o ../../NeuroSim/Library/Patterns/CurrentPatterns.o
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< Gui.o SimulationView.o FiringRateView.o SimulationGraphs.o ../Pattern/Pattern.o ../../BlueSpike/Library/Misc/Randn.o ../../NeuroSim/Library/IzNeuron/Neuron.o ../../NeuroSim/Library/ParkerSochacki/ParkerSochacki.o ../../NeuroSim/Library/Event/Event.o ../../NeuroSim/Library/Synapse/Synapse.o ../../NeuroSim/Library/Network/Network.o ../../NeuroSim/Library/IzNeuron/NeuronTypes.o ../DataHandling/DataHandling.o ../DataHandling/v0/DataFormat_v0.o ../../BlueSpike/Library/Misc/Misc.o ../../BlueSpike/Library/NeuroStats/FiringRate/FiringRate.o ../../BlueSpike/Library/NeuroStats/FiringRate/FiringRateGraph.o ../../TrialControllers/Library/TrialStats/TrialStats.o ../../TrialControllers/Library/TrialTypes/TrialTypes.o ../../NeuroSim/Library/Combos/LayerNrnGrpNeuronCombo.o  ../../TrialControllers/Library/Combos/TrialTypesCombo.o ../../NeuroSim/Library/Patterns/CurrentPatterns.o
	
Gui.o: Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	
	
SimulationView.o: SimulationView.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		
		
FiringRateView.o: FiringRateView.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		

SimulationGraphs.o: SimulationGraphs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 
	
../Pattern/Pattern.o: ../Pattern/Pattern.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 
	
../../BlueSpike/Library/Misc/Randn.o: ../../BlueSpike/Library/Misc/Randn.c
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
	
../../BlueSpike/Library/NeuroStats/FiringRate/FiringRate.o: ../../BlueSpike/Library/NeuroStats/FiringRate/FiringRate.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	
	
../../BlueSpike/Library/NeuroStats/FiringRate/FiringRateGraph.o: ../../BlueSpike/Library/NeuroStats/FiringRate/FiringRateGraph.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		
		
../../BlueSpike/Library/Misc/Misc.o: ../../BlueSpike/Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		

../../NeuroSim/Library/Combos/LayerNrnGrpNeuronCombo.o: ../../NeuroSim/Library/Combos/LayerNrnGrpNeuronCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		

../../NeuroSim/Library/Combos/LayerNrnGrpNeuronCombo.o: ../../NeuroSim/Library/Combos/LayerNrnGrpNeuronCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	

../../NeuroSim/Library/Patterns/CurrentPatterns.o: ../../NeuroSim/Library/Patterns/CurrentPatterns.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	

../../TrialControllers/Library/TrialStats/TrialStats.o: ../../TrialControllers/Library/TrialStats/TrialStats.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 	
		
../../TrialControllers/Library/TrialTypes/TrialTypes.o: ../../TrialControllers/Library/TrialTypes/TrialTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS) 		# to see warnings

clean:
	rm -f *.o SpikePatternGenerator ../../NeuroSim/Library/IzNeuron/*.o ../../NeuroSim/Library/ParkerSochacki/*.o ../../NeuroSim/Library/Event/*.o ../../NeuroSim/Library/Synapse/*.o ../../NeuroSim/Library/Network/*.o ../Pattern/*.o ../DataHandling/*.o ../DataHandling/v0/*.o ../../BlueSpike/Library/Misc/*.o ../../BlueSpike/Library/NeuroStats/FiringRate/*.o ../../TrialControllers/Library/TrialStats/*.o ../../TrialControllers/Library/TrialTypes/*.o ../../NeuroSim/Library/Combos/*.o ../../TrialControllers/Library/Combos/*.o ../../NeuroSim/Library/Patterns/*.o

.PHONY: clean

