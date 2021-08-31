% gray_scale_image.m - create grayscale image from color image

% Fred J. Frigo, Ph.D.
% 16-Aug-2021
%
 
% Read color photo
im = imread('IMG_6728.jpg');
figure();
imshow(im);
 
% Convert to gray scale
gray = (0.2989 * double(im(:,:,1)) + ...
        0.5870 * double(im(:,:,2)) + ...
        0.1140 * double(im(:,:,3)))/255;

figure();
imshow(gray);

