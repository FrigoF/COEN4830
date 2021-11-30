% mr_image.m - MR image Dicom reader
% Marquette University
% EECE 4510/5510
%
% Fred J. Frigo
% Nov 29, 2021


% Read DICOM image file to obtain DICOM header info 
% Enter name of Pfile
dfile = "";
dfile = 'e31s3i11.dcm';
if(dfile == "")
    [fname, pname] = uigetfile('*.*', 'Select DICOM image File');
    dfile = strcat(pname, fname);
end
   
% DICOM read image
dimage = dicomread( dfile);
colormap('gray');
imagesc(dimage); %display image

% Get DICOM info from input image.
info = dicominfo(dfile);

msg = sprintf('Default window width = %d, default window level = %d', ...
            info.WindowWidth, info.WindowCenter);  
disp(msg);
  