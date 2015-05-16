%extract data from .txt file to .mat file

global MAX_TIME
global MAX_SAMPLE
global filelist
global path

for i=1:length(filelist)
    filename = cell2mat(filelist(i));

    [fileID,errmsg] = fopen(fullfile(path,'data',filename),'r');

    iter = zeros(1,MAX_SAMPLE);
    time_tmp = zeros(1,MAX_SAMPLE);
    mag_x = zeros(1,MAX_SAMPLE);
    mag_y = zeros(1,MAX_SAMPLE);
    mag_z = zeros(1,MAX_SAMPLE);

    %read file line by line
    i=1;
    tline = fgetl(fileID);
    while ischar(tline) && (i==1 || time_tmp(i-1)<=MAX_TIME )
        [iter(i), time_tmp(i), mag_x(i), mag_y(i), mag_z(i)] = regex(tline);    %time_tmp won't be used (except the first & last value
        tline = fgets(fileID);
        i=i+1;
    end

    %create a linear time (in ms accuracy)
    time = linspace(time_tmp(1),max(time_tmp),MAX_SAMPLE);
    
    %save the file
    savefile = fullfile(path,'data_mod',regexprep(filename,'(\.)\w+', '.mat'));
    save(savefile,'iter', 'time', 'mag_x', 'mag_y', 'mag_z');

    fclose(fileID);
end
