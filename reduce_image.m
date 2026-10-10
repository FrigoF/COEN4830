% reduce_image.m - Use Fourier Transform to resize image
% Fred J. Frigo, Ph.D.
% Original date: 03-Oct-2023
% Interpolation fix:  10-Oct-2026        
%
function reduce_image(imfile)


if nargin == 0
    [fname, pathname] = uigetfile({'*.*', 'All image files'}, 'Select Image file');
    if isequal(fname, 0)
        return;  % User cancelled the file-selection dialog.
    end
    imfile = fullfile(pathname, fname);
end

% Read image and convert to grayscale if needed.
im = imread(imfile);
figure;
imshow(im);
title('Original image');
if ndims(im) == 3
    gray = rgb2gray(im);
else
    gray = im;
end
gray = double(gray);
[row, col] = size(gray);
figure;
imshow(gray, []);
title(sprintf('Original grayscale image: %d x %d', row, col));

% Compute and display the centered Fourier spectrum.
F = fft2(gray);
S = fftshift(F);
A = log1p(abs(S));  % Finite at zero-valued frequency bins.
figure;
imagesc(A);
title('Log magnitude of FFT');

% Set the resize factor: < 1 reduces; > 1 enlarges.
zip = 0.25;
zip_row = max(1, round(row * zip));
zip_col = max(1, round(col * zip));

if zip < 1
    % Keep the centered low-frequency region (Fourier-domain decimation).
    r0 = floor((row - zip_row) / 2) + 1;
    c0 = floor((col - zip_col) / 2) + 1;
    reduce_buffer = S(r0:r0 + zip_row - 1, c0:c0 + zip_col - 1);
    zip_buffer = ifftshift(reduce_buffer);
else
    % Zero-pad the centered spectrum to interpolate the image.
    interpolation_buffer = zeros(zip_row, zip_col, 'like', S);
    r0 = floor((zip_row - row) / 2) + 1;
    c0 = floor((zip_col - col) / 2) + 1;
    interpolation_buffer(r0:r0 + row - 1, c0:c0 + col - 1) = S;
    zip_buffer = ifftshift(interpolation_buffer);
end

% Preserve intensity scale under MATLAB's inverse-FFT normalization.
zip_complex = ifft2(zip_buffer) * (zip_row * zip_col) / (row * col);
% A real input should produce a real result; discard numerical roundoff.
zip_image_out = real(zip_complex);

figure;
imshow(zip_image_out, []);
title(sprintf('Resized grayscale image: %d x %d', zip_row, zip_col));
