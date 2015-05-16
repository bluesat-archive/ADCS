%plot all data
function data_plot_xyz(Iter, Time, Mag_X, Mag_Y, Mag_Z)

global filelist

len = length(filelist);

%plot time vs magnetics field strength
for i=1:len
    figure(i)
    
    subplot(3,1,1)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Mag_X(i,1:length(time)))
    title(strcat('Detumbling: ',filelist(i)))
    xlabel('time (s)')
    ylabel('magnetometer (x)')
    
    subplot(3,1,2)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Mag_Y(i,1:length(time)))
    xlabel('time (s)')
    ylabel('magnetometer (y)')
    
    subplot(3,1,3)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Mag_Z(i,1:length(time)))
    xlabel('time (s)')
    ylabel('magnetometer (z)')
end

end
