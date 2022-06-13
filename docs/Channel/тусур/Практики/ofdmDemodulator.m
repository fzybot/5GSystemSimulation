function [modSymbRx] = ofdmDemodulator(input, control);

out = fft(input(20+1:end));

informSpectrum = out(20+1:end-20);
informSpectrum = [informSpectrum(1:control.half) informSpectrum(control.half + 2: end)];
informSpectrum = informSpectrum ./ max(informSpectrum);

rs_rx = informSpectrum(control.rs_sc);
hw = rs_rx ./ control.rs_val;

% Линейная интерополяция
EQ(1, 1) = hw(1);
L = length(control.data_sc) + length(control.rs_sc);
j = 0;

for i = 1 : length(hw)-1
    D = (hw(i+1) - hw(i)) / (control.rs_step + 1);
    for k = 1 : control.rs_step + 1
        j = j + 1;
        EQ(1, j+1) = EQ(1, j) + D;
    end;
end;

EQ(j+2:L) = hw(end);

informSpectrumEQ = informSpectrum ./ EQ;

figure(1);
subplot(4, 1, 2);
plot(abs(out));
title('Inform Spectrum RX');
subplot(4, 1, 3);
plot(abs(hw));
title('Channel coeff.');
subplot(4, 1, 4);
plot(abs(informSpectrumEQ));
title('Inform Spectrum RX Equalizer');

modSymbRx = informSpectrumEQ(control.data_sc);



