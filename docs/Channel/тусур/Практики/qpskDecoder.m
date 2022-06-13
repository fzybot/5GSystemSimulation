function [outBits] = qpskDecoder(inputComplex);

outBits = [];

for i = 1 : length(inputComplex)
    if real(inputComplex(i)) >= 0 && imag(inputComplex(i)) >= 0
        outBits = [outBits 0];
        outBits = [outBits 0];
    elseif real(inputComplex(i)) >= 0 && imag(inputComplex(i)) < 0 
        outBits = [outBits 0];
        outBits = [outBits 1];
    elseif real(inputComplex(i)) < 0 && imag(inputComplex(i)) >= 0
        outBits = [outBits 1];
        outBits = [outBits 0];
    elseif real(inputComplex(i)) < 0 && imag(inputComplex(i)) < 0
        outBits = [outBits 1];
        outBits = [outBits 1];
    end;
end