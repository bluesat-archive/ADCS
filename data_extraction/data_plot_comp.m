%plot all data
function data_plot_comp(Iter, Time, Mag_X, Mag_Y, Mag_Z)

global filelist

len = length(filelist);

%plot time vs magnetics field strength: x-axis
figure(1)
for i=1:len
    subplot(len,1,i)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Mag_X(i,1:length(time)))
    title(strcat('Detumbling: ',filelist(i)))
    ylabel('magnetometer (x)')
end
xlabel('time (s)')

%plot time vs magnetics field strength: y-axis
figure(2)
for i=1:len
    subplot(len,1,i)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Mag_Y(i,1:length(time)))
    title(strcat('Detumbling: ',filelist(i)))
    ylabel('magnetometer (y)')
end
xlabel('time (s)')

%plot time vs magnetics field strength: z-axis
figure(3)
for i=1:len
    subplot(len,1,i)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Mag_Z(i,1:length(time)))
    title(strcat('Detumbling: ',filelist(i)))
    ylabel('magnetometer (z)')
end
xlabel('time (s)')

end
