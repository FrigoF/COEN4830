% rgb_image.m - create red/green/blue color image
%
% Fred J. Frigo, Ph.D.
% 08-Sep-2021
%
% See: https://www.mathworks.com/matlabcentral/
%      answers/91036-how-do-i-split-a-color-image-into-its-3-rgb-channels

% Read color photo
function rgb_image( imfile )

if(nargin == 0)
    [fname,iname] = uigetfile('*.*', 'Select Image file');
    imfile = strcat(iname, fname);
end

% Read color photo
rgbImage = imread(imfile);  
figure();
imshow(rgbImage);

% Extract color channels.
redChannel = rgbImage(:,:,1); % Red channel
greenChannel = rgbImage(:,:,2); % Green channel
blueChannel = rgbImage(:,:,3); % Blue channel
% Create an all black channel.
allBlack = zeros(size(rgbImage, 1), size(rgbImage, 2), 'uint8');

% Create color versions of the individual color channels.
just_red = cat(3, redChannel, allBlack, allBlack);
just_green = cat(3, allBlack, greenChannel, allBlack);
just_blue = cat(3, allBlack, allBlack, blueChannel);

figure();
imshow(just_red);
figure();
imshow(just_green);
figure();
imshow(just_blue);


