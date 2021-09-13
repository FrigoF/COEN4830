% read_meta_data.m -  read image and display meta data
% COEN 4830 - Computer Graphics
% Fred J. Frigo, Ph.D.
% 12-Sep-2021
%
 
function read_meta_data( image_file )

  if(nargin == 0)
    [fname, pname] = uigetfile('*.*', 'Select file');
    image_file = strcat(pname, fname);
  end

  % display image
  im = imread(image_file);
  figure();
  image(im);
  title(image_file);
 
  % display meta data
  info = imfinfo(image_file);
 
  makeModel_string = sprintf('%s %s', info.Make, info.Model);
  date_string = info.DigitalCamera.DateTimeOriginal;
  gps_latitude = sprintf('%d %d %f %s', info.GPSInfo.GPSLatitude(1), ...
                                     info.GPSInfo.GPSLatitude(2), ...
                                     info.GPSInfo.GPSLatitude(3), ...
                                     info.GPSInfo.GPSLatitudeRef);
  gps_longitude = sprintf('%d %d %f %s', info.GPSInfo.GPSLongitude(1), ...
                                     info.GPSInfo.GPSLongitude(2), ...
                                     info.GPSInfo.GPSLongitude(3), ...
                                     info.GPSInfo.GPSLongitudeRef);
                                 
  fprintf('Make & Model: %s \n', makeModel_string);
  fprintf('Date & Time: %s \n', date_string);
  fprintf('GPS Coordinates: %s, %s \n', gps_latitude, gps_longitude);
  
end

