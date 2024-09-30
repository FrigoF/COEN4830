% fourier_image.m - display magnitude of Fourier Transformed image
% Fred J. Frigo, Ph.D.
% 16-Sep-2021
%
 
% Read color photo
function fourier_image( imfile )


if(nargin == 0)
    [fname,iname] = uigetfile('*.*', 'Select Image file');
    imfile = strcat(iname, fname);
end

% Read color photo
im = imread(imfile);  
figure();
imshow(im);
title("Color image");
 
% Convert to gray scale
gray = rgb2gray(im);

figure();
imshow(gray);
title("Gray scale image");

% Take the magnitude of the FFT
F=fft2(double(gray));
S=fftshift(F);
L=abs(S);
A=log2(L);
figure();
imagesc(A);
axis image;
title("Magnitude of FFT image");

