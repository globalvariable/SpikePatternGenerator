#ifndef DATAFORMAT_V0_H
#define DATAFORMAT_V0_H
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

int create_main_directory_v0(int num, ...);
int save_main_directory_v0(int num, ...);
int load_main_directory_v0(int num, ...);

int create_main_meta_file(char * main_dir_path);
int save_notes(char* main_dir_path, GtkWidget *text_view);
int save_drawn_stimulus_current(char *main_dir_path);
int save_neuron_params(char *main_dir_path);
int save_injected_current_noise_params(char *main_dir_path);
int save_initial_membrane_voltage_params(char *main_dir_path);
int create_data_directory(char *main_dir_path, int pattern_num);
int save_data_files(char  *data_directory_path, int pattern_num);
int save_meta_data(char *data_directory_path, int pattern_num);
int save_raw_stimulus_current(char *data_directory_path, int pattern_num);
int save_noisy_stimulus_current(char *data_directory_path, int pattern_num);
int save_spike_timestamps(char *data_directory_path, int pattern_num);

int read_main_meta_file(char * main_dir_path);
int read_notes(char* main_dir_path, GtkWidget *text_view);
int read_drawn_stimulus_current(char *main_dir_path);
int read_neuron_params(char *main_dir_path);
int read_injected_current_noise_params(char *main_dir_path);
int read_initial_membrane_voltage_params(char *main_dir_path);
int read_data_directory(char *main_dir_path, int pattern_num);
int read_data_files(char  *data_directory_path, int pattern_num);
int read_meta_data(char *data_directory_path, int pattern_num);
int read_raw_stimulus_current(char *data_directory_path, int pattern_num);
int read_noisy_stimulus_current(char *data_directory_path, int pattern_num);
int read_spike_timestamps(char *data_directory_path, int pattern_num);



#endif
