%load .mat file

global MAX_TIME
global MAX_SAMPLE
global filelist
global path

% path = 'C:\Users\Ross\Documents\UNSW\BlueSat\ADCS\detumbling_exp';
% MAX_TIME = 8 *60; % in seconds
% sample_rate = 5;    %5 samples per sec
% MAX_SAMPLE = MAX_TIME * sample_rate;     %only interest up to n samples
% 
% filelist = {'DATALOG6 - 01 - Control.TXT', 'DATALOG6 - 02 - Test 1.TXT', 'DATALOG6 - 03 - Test 2.TXT'};

%matrix, each row from different file, each col is data across time
Iter = zeros(length(filelist), MAX_SAMPLE);
Time = zeros(length(filelist), MAX_SAMPLE);
Mag_X = zeros(length(filelist), MAX_SAMPLE);
Mag_Y = zeros(length(filelist), MAX_SAMPLE);
Mag_Z = zeros(length(filelist), MAX_SAMPLE);

for i=1:length(filelist)
    filename = cell2mat(filelist(i));
    filepath = fullfile(path,'data_mod',regexprep(filename,'(\.)\w+', '.mat'));
    data_struct = load(filepath);
    Iter(i,:) = data_struct.iter;
    Time(i,:) = data_struct.time;
    Mag_X(i,:) = data_struct.mag_x;
    Mag_Y(i,:) = data_struct.mag_y;
    Mag_Z(i,:) = data_struct.mag_z;
end
