% gray_scale_image.m - create grayscale image from color image

% Fred J. Frigo, Ph.D.
% 16-Aug-2021
%

function gray_scale_image( imfile )

if(nargin == 0)
    [fname,iname] = uigetfile('*.*', 'Select Image file');
    imfile = strcat(iname, fname);
end

% Read color photo
im = imread(imfile);  
figure();
imshow(im);
 
% Convert to gray scale
gray = (0.2989 * double(im(:,:,1)) + ...
        0.5870 * double(im(:,:,2)) + ...
        0.1140 * double(im(:,:,3)))/255;

figure();
imshow(gray);

