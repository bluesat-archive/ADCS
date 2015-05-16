%plot all data
function data_plot_ang_comp(Time, Angle, AngVel, AngAcc)

global filelist

len = length(filelist);

%plot time vs angle
figure(1)
for i=1:len
    subplot(len,1,i)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Angle(i,1:length(time)))
    title(strcat('Detumbling: ',filelist(i)))
    ylabel('Angular position(\theta)')
end
xlabel('time (s)')

%plot time vs angular velocity
figure(2)
for i=1:len
    subplot(len,1,i)
    time = Time(i, 1:find(Time(i,:),1,'last')-1); %remove padding zeros of time, differentiation give 1 less data
    plot(time,AngVel(i,1:length(time)))
    line([0 time(end)],[0 0],'Color','r')
    title(strcat('Detumbling: ',filelist(i)))
    ylabel('Angular velocity(\omega)')
end
xlabel('time (s)')

%plot time vs angular accleration
figure(3)
for i=1:len
    subplot(len,1,i)
    time = Time(i, 1:find(Time(i,:),1,'last')-2); %remove padding zeros of time, differentiation twice give 1 less data
    plot(time,AngAcc(i,1:length(time)))
    title(strcat('Detumbling: ',filelist(i)))
    ylabel('Angular accelration(\alpha)')
end
xlabel('time (s)')

end
