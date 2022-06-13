function [awgn, sumBeamsNoise, dopplerSig] = channel(ofdmSymb);

f = 2.2*10^9;
c = 3*10^8;
B = 15*10^3 * 1024;
T = 1 / B;

nBeams = 4;
n0 = -150;

%% Рассчет растояний лучей
distance(1) = randi([10, 500], 1, 1);
distance(2:nBeams) = sort(randi([distance(1) + 10 distance(1) + 2000], 1, nBeams-1));

%% Рассчет затуханий для каждого луча
gain = c ./(4 * pi * distance * f);

%% Рассчет задержек сигнала для каждого луча в целых отсчетах.

delay(1) = 0;
delay(2:nBeams) = round( (distance(2:nBeams) - distance(1))/c/T );

%% Многолучевой канал

% 1 1 1 1
% 0 0 0 0 0 0 0 0 0
% 1 1 1 1 0 0 0 0 0 - [0] луч
% 0 1 1 1 1 0 0 0 0 - [1] луч с задержкой в 1 отсчет
% и т.д.
delayVal = delay(end); 
sumBeams(1, :) = zeros(1, length(ofdmSymb) + delayVal);
for i = 1 : nBeams
    sumBeams(1, :) = sumBeams(1, :) + gain(i)*[zeros(1, delay(i)) ofdmSymb zeros(1, delayVal - delay(i))];
end

%% AWGN
awgn = wgn(1, length(sumBeams), n0);

%% Сложение сигнала с шумом

out = sumBeams(1, :) + awgn;
awgn = awgn(1 : length(ofdmSymb));
sumBeamsNoise = out(1 : length(ofdmSymb));

%% Допплер
Doppler = 5;
time = (1 : 1 : length(ofdmSymb)) / T * 2048; % sampleRate
for i = 1 : length(time)
    dopplerSig(i) = out(i) * exp(-1i*2*pi*Doppler*time(i));
end


