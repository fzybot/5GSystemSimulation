% Практика 1. Введение в Matlab/Octave
% Часть 1. Константы

clear all;
a = 1;
b = 7;
c = b - a;
d = c * b - a;
e = a + (-1i)*b;
h = d * (1e2);
g = a * (pi);

% Часть 2. Векторы

clear all;
a = 1;
b = 7;
c = b - a;
d = c * b - a;
N = c + 1;
f = ones(1, N);
g = ones(1, N);
h = f + g;
j = d * h;
v = ones(N, 1);
disp( v(2) );

% Часть 3. Матрицы

clear all;
A = ones(3, 3);
B = ones(3, 3);
C = A * B;
D = A * B;
disp( D(1, 1) )
disp( D(:, 1) );
disp( D(1, :) );

% Часть 4. Операторы и циклы

clear all;
a = 1;
c = 0;
% for X = start : step : end
for index = 0 : 1 : 10 * a
    disp(index);
    c = c + index;
end
disp(c);

summ = 0;
for index = 0 : 1 : 10 * a
    if (mod(index, 2) ~= 0)
        summ = summ + index;
    end
end
disp(summ);

a = 120;
x = 0;
summ2 = 0;
while x < a
    summ2 = summ2 +  x;
    x = x + 1;
end
disp(summ2);

% Часть 5. Библиотека функций

clear all;
A = randn(1, 10);
maxA = max(A);
minA = min(A);
[maxA, maxIndex] = max(A);
onesVector = ones(1, 10);
zerosVector = zeros(1, 10);

% Блок 6. Графическое отображение

clear all;
N = 100;
A = randi([1, 10], 1, N);
Y = [];
for index = 0 : 1 : N-1
    Y = [Y index];
end
fBar = figure();
bar(A);
fStem = figure();
stem(A);
fPlot = figure('name', 'Title');
p1 = plot(Y, A, '-r', 'LineWidth', 2);
xlabel('x data');
ylabel('y data');
legend('random values');
xlim([0 90]);
ylim([min(A), max(A)]);
grid on;