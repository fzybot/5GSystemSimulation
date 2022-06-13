function [outputBitArray] = interleavingDecoder(inputBitArray, interleavingPattern);

outputBitArray = [];
for i = 1 : 1 : length(inputBitArray)
    for j = 1 : 1 : length(inputBitArray)
        if (interleavingPattern(j) == i)
            outputBitArray = [outputBitArray inputBitArray(j)];
        end
    end
end