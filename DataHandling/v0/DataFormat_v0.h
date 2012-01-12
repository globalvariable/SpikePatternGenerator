#ifndef SPIKEPATTERNGENERATOR_DATAFORMAT_V0_H
#define SPIKEPATTERNGENERATOR_DATAFORMAT_V0_H
#include <rtai_shm.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <gtk/gtk.h>
#include <string.h>

#include "./../../BlueSpike/Library/Misc/Misc.h"
#include "./../../NeuroSim/Library/Network/Network.h"
#include "./../Pattern/Pattern.h"

int create_spike_pattern_generator_data_directory_v0(int num, ...);
int save_spike_pattern_generator_data_directory_v0(int num, ...);
int load_spike_pattern_generator_data_directory_v0(int num, ...);





#endif
