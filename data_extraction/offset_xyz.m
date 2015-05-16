%normalise the variables in x,y,z axis

global MAX_SAMPLE

offsetx = (max(Mag_X,[],2) + min(Mag_X,[],2))/2;
offsety = (max(Mag_Y,[],2) + min(Mag_Y,[],2))/2;
offsetz = (max(Mag_Z,[],2) + min(Mag_Z,[],2))/2;

Mag_X_ac = Mag_X - repmat(offsetx,1,MAX_SAMPLE);
Mag_Y_ac = Mag_Y - repmat(offsety,1,MAX_SAMPLE);
Mag_Z_ac = Mag_Z - repmat(offsetz,1,MAX_SAMPLE);
