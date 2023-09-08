% gamma_plot.m - Show gamma adjusted output for monitors
% Fred J. Frigo, Ph.D.
% 07-Sep-2023
% 
% See Marshner, 5 edition p 72

my_input = 0:0.05:1.0;  % vector from 0 to 1 in steps of 0.05

data.gamma_1 = my_input.^0.25;
data.gamma_2 = my_input.^0.5;
data.gamma_3 = my_input;
data.gamma_4 = my_input.^2.0;
data.gamma_5 = my_input.^3.0;

f=fields(data);

figure();
for i=1:length(f)
    a = data.(f{i});
    plot(my_input,a);
    hold on
end
hold off
xlabel('Input value');
ylabel('Output value');
title('Gamma Adjustment');
legend('0.25','0.5','1.0', '2.0', '3.0');

