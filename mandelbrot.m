% mandelbrot.m - create Mandelbrot image
%
% Author:  Chris Taylor
%          London, United Kingdom
%          linkedin.com/in/crntaylor
%          30-Dec-2013
%
% Use: >> mandelbrot(800, 40)
%         where n = image size, number of iterations = niter
%

function mandelbrot(n, niter)

x0 = -2;   x1 = 1;
y0 = -1.5; y1 = 1.5;

[x,y] = meshgrid(linspace(x0, x1, n), linspace(y0, y1, n));

c = x + 1i * y;
z = zeros(size(c));
k = zeros(size(c));

for ii = 1:niter
    z   = z.^2 + c;
    k(abs(z) > 2 & k == 0) = niter - ii;
end

figure,
imagesc(k),
colormap hot
axis square
end