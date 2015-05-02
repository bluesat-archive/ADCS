path = 'C:\Users\Ross\Documents\UNSW\BlueSat\ADCS\detumbling_exp';
filename = 'DATALOG6 - 01 - Control.TXT';
[fileID,errmsg] = fopen(fullfile(path,'data',filename),'r');
% fileID = fopen(fullfile('data','DATALOG7.txt'),'w+');

MAX_TIME = 10 *60; % in seconds

%read file line by line
i=1;
time(1)=0;
tline = fgetl(fileID);
while ischar(tline) && (time(i)<=MAX_TIME || i==1)
    [iter(i), time(i), mag_x(i), mag_y(i), mag_z(i)] = regex(tline);
    
    tline = fgets(fileID);
    i=i+1;
end
sample_size = i;
fclose(fileID);

figure(2)
plot(time,mag_y)
title(strcat('Detumbling: ',filename))
xlabel('time (s)')
ylabel('magnetometer (y)')
