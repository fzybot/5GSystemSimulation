function [bitArray, alphabet, message] = znakCoding(messageSize)

codeBook = 'TUSR';
alphabet = 7;
message = '';
for index = 1 : 1 : messageSize
    r = randi([1 4],1,1);
    message = append(message, codeBook(r));
end
bitArray = [];
for index = 1 : 1 : length(message)
    switch message(index)
        case 'T'
            bitArray = [bitArray [0, 0, 1, 0, 1, 0, 1]];
        case 'U'
            bitArray = [bitArray [1, 0, 1, 0, 1, 0, 1]];
        case 'S'
            bitArray = [bitArray [1, 1, 0, 0, 1, 0, 1]];
        case 'R'
            bitArray = [bitArray [0, 1, 0, 0, 1, 0, 1]];
    end
end