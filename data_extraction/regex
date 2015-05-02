%extract info from a line of text 
function [iter, time, mag_x, mag_y, mag_z] = regex(str)

% str = '-1 01h02m03s {4, 5, 6}';
str = regexprep(str,'[^-0-9]', ' ');  %strip away all non-number characters

C = strsplit(str);  %split line into array of cells with ' ' separator

iter = str2double(cell2mat(C(1)));
hr = str2double(cell2mat(C(2)));
min = str2double(cell2mat(C(3)));
sec = str2double(cell2mat(C(4)));
mag_x = str2double(cell2mat(C(5)));
mag_y = str2double(cell2mat(C(6)));
mag_z = str2double(cell2mat(C(7)));

time = ((hr*60)+min)*60 + sec;

end
