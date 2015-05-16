%use x,y -> theta

global MAX_TIME
global MAX_SAMPLE

%normalise x,y axis (orginally an ellipse)
%assume its offset already
Mag_X_norm = Mag_X_ac ./ repmat(max(Mag_X_ac,[],2),1,MAX_SAMPLE);
Mag_Y_norm = Mag_Y_ac ./ repmat(max(Mag_Y_ac,[],2),1,MAX_SAMPLE);

%calculate theta
Thetawrap = atan(Mag_Y_norm ./ Mag_X_norm);
Angle = unwrap(Thetawrap*2,[],2)/2;

% dt = MAX_TIME / MAX_SAMPLE;
%calculate angular velocity and acceleration
AngVel = diff(Angle,1,2);
AngAcc = diff(Angle,2,2);
