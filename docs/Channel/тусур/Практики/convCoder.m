function [outputBitArray] = convCoder(inputBitArray);

convBitArray = [0, 0, 0, 0, 0, 0, 0];
outputBitArray = [];

for indeX = 1 : 1 : length(inputBitArray)
    summ_xor_x = 0;
    summ_xor_y = 0;
    convBitArray(end) = [];
    convBitArray = [inputBitArray(indeX) convBitArray];
    for indeY = 1 : 1 : length(convBitArray)
        switch indeY
            case 1
                summ_xor_x = xor(summ_xor_x, convBitArray(indeY));
                summ_xor_y = xor(summ_xor_y, convBitArray(indeY));
            case 2
                summ_xor_x = xor(summ_xor_x, convBitArray(indeY));
            case 3
                summ_xor_x = xor(summ_xor_x, convBitArray(indeY));
                summ_xor_y = xor(summ_xor_y, convBitArray(indeY));
            case 4
                summ_xor_x = xor(summ_xor_x, convBitArray(indeY));
                summ_xor_y = xor(summ_xor_y, convBitArray(indeY));
            case 6
                summ_xor_y = xor(summ_xor_y, convBitArray(indeY));
            case 7
                summ_xor_x = xor(summ_xor_x, convBitArray(indeY));
                summ_xor_y = xor(summ_xor_y, convBitArray(indeY));
        end
    end
    outputBitArray = [outputBitArray summ_xor_x];
    outputBitArray = [outputBitArray summ_xor_y];
end