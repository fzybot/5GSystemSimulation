function [outputComplex] = qpskEncoder(inputBitArray);

outputComplex = [];
normalized = [];
k = 0;
for i = 1 : 2 : length(inputBitArray)
    k = k + 1;
    if inputBitArray(i) == 0 && inputBitArray(i+1) == 0
        I = 1 / sqrt(2);
        Q = 1 / sqrt(2);
    elseif inputBitArray(i) == 0 && inputBitArray(i+1) == 1
        I = 1 / sqrt(2);
        Q = -1 / sqrt(2);
    elseif inputBitArray(i) == 1 && inputBitArray(i+1) == 0
        I = -1 / sqrt(2);
        Q = 1 / sqrt(2);
    elseif inputBitArray(i) == 1 && inputBitArray(i+1) == 1
        I = -1 / sqrt(2);
        Q = -1 / sqrt(2);
    end;
    outputComplex = [outputComplex complex(I, Q)];
end;

%[normalized] = normalization_by_value(outputComplex, 1);