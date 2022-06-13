function [message] = znakCoding(bitArray, alphabet)

N = size(bitArray);
message = '';

for index = 1 : alphabet : N(2)
    bitBurst = [];
    for ind = index : 1 : index + alphabet - 1
        bitBurst = [bitBurst bitArray(ind)];
    end
    if bitBurst == [0, 0, 1, 0, 1, 0, 1]
        message = append(message, 'T');
    elseif bitBurst == [1, 0, 1, 0, 1, 0, 1]
        message = append(message, 'U');
    elseif bitBurst == [1, 1, 0, 0, 1, 0, 1]
        message = append(message, 'S');
    elseif bitBurst == [0, 1, 0, 0, 1, 0, 1]
        message = append(message, 'R');
    end
end