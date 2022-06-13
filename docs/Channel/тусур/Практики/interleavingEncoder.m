function [outputBitArray, randPattern] = interleavingEncoder(inputBitArray);

outputBitArray = [];
randPattern = [];
for i = 1 : 1 : length(inputBitArray)
    randPattern = [randPattern i];
end
randPattern = randperm(length(randPattern));
for i = 1 : 1 : length(inputBitArray)
    outputBitArray = [outputBitArray inputBitArray(randPattern(i))];
end