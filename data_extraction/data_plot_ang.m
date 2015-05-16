%plot all data
function data_plot_ang(Time, Angle, AngVel, AngAcc)

global filelist

len = length(filelist);

%plot time vs magnetics field strength
for i=1:len
    figure(i)
    
    subplot(3,1,1)
    time = Time(i, 1:find(Time(i,:),1,'last')); %remove padding zeros of time
    plot(time,Angle(i,1:length(time)))
    title(strcat('Detumbling: ',filelist(i)))
    ylabel('Angular position(\theta)')
    
    subplot(3,1,2)
    time = Time(i, 1:find(Time(i,:),1,'last')-1); %remove padding zeros of time
    plot(time,AngVel(i,1:length(time)))
    line([0 time(end)],[0 0],'Color','r')
    ylabel('Angular velocity(\omega)')
    
    subplot(3,1,3)
    time = Time(i, 1:find(Time(i,:),1,'last')-2); %remove padding zeros of time
    plot(time,AngAcc(i,1:length(time)))
    xlabel('time (s)')
    ylabel('Angular accelration(\alpha)')
end

end
