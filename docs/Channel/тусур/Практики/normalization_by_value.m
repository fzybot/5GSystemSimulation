function [out] = normalization_by_value(input, normValue);

out = [];
maximum = 1 / sqrt(2);
k = normValue / maximum;

for i = 1 : 1 : length(input)
    I = real(input(i)) * k;
    Q = imag(input(i)) * k;
    out = [out complex(I, Q)];
end