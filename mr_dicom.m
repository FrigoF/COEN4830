% mr_dicom.m - Display MR DICOM image & read default WW/WL
% Marquette University
% COEN 4830
%
% Fred J. Frigo

% Read DICOM image file
dfile = 'e31s3i11.dcm';
 
% Display pixel data
myImage = dicomread(dfile);
figure;
colormap('gray');
imagesc(myImage);

% Get DICOM info from header.
info = dicominfo(dfile);

default_ww = info.WindowWidth;
default_wl = info.WindowCenter;
  
msg=sprintf('Default WW = %d, Default WL = %d', default_ww, default_wl);
title(msg);

% Window Level adjustment example
figure();
min_pixel = 100;
max_pixel = 2000;
window_width = max_pixel - min_pixel;
clims = [min_pixel max_pixel];
colormap('gray');
imagesc(myImage, clims);
msg1 = sprintf('Window width = %d, Window level = %d', ...
              window_width, (min_pixel+(window_width)/2));
title(msg1);

