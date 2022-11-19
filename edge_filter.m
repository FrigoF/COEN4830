% edge_filter.m -  read jpeg image and perform edge filter
%
%
% COEN 4830 / EECE 5830 - Marquette University
% Fred J. Frigo, Ph.D.
% 19-Nov-2022
%

% Get input file to test
imfile = '';
if(imfile == "")
    [fname, pname] = uigetfile('*.*', 'Select input file');
    imfile = strcat(pname, fname);
end

img = imread(imfile);
figure();
image(img);

% Convert to gray scale
gray = rgb2gray(img); 
figure();
imshow(gray);

% 2D Sobel Filter
gray2 = im2double(gray); % image for 'sobel' function needs to be double
sobel_threshold = 0.1;      % use threshold values from 0.01 to 1.0
edgeIm = sobel(gray2, sobel_threshold);  
figure();
im3 = repmat(edgeIm, [1 1 3]);
image(im3);
sobel_str = sprintf('Sobel filter with threshold = %f',sobel_threshold);
title(sobel_str);

% Sobel Edge Filter
edgeIm = edge(gray, "Sobel");
figure();
im3 = repmat(edgeIm, [1 1 3]);
image(im3);
title('Sobel');

% Canny Edge Filter
edgeIm = edge(gray, "Canny");
figure();
im3 = repmat(edgeIm, [1 1 3]);
image(im3);
title('Canny');
