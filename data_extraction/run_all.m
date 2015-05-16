%run files

%% S1 set up all the global variables
%global variables
global MAX_TIME
global MAX_SAMPLE
global filelist
global path

MAX_TIME = 8 *60; % in seconds
sample_rate = 5;    %5 samples per sec
MAX_SAMPLE = MAX_TIME * sample_rate;

filelist = {'DATALOG6 - 01 - Control.TXT', 'DATALOG6 - 02 - Test 1.TXT', 'DATALOG6 - 03 - Test 2.TXT'};
path = 'C:\Users\Ross\Documents\UNSW\BlueSat\ADCS\detumbling_exp';

%% S2 convert .txt file to .mat data file
data_extraction;

%% S3 load .mat file into a matrix
load_data;

%% S4 remove offset data in each axis
offset_xyz;

%% S5a compare different experiments on the same plot
data_plot_comp(Iter, Time, Mag_X_ac, Mag_Y_ac, Mag_Z_ac)

%% S5b plot xyz axis together
data_plot_xyz(Iter, Time, Mag_X_ac, Mag_Y_ac, Mag_Z_ac)

%% S6 convert x,y to angular domain
xy2angle;

%% S7a compare different experiments on the same angular plot
data_plot_ang_comp(Time, Angle, AngVel, AngAcc)

%% S7b plot angle, angular velocity, accelation together
data_plot_ang(Time, Angle, AngVel, AngAcc)
