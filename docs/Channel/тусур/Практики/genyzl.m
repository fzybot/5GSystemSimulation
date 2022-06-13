function [ yzli, ves,add_to_metr,pyt,in_delay_pipe ] = genyzl;
k = 7;
G1 = 171;
G2 = 133;
G1=dec2bin(oct2dec(G1));
G1=str2num(reshape(G1,[],1))';
G2=dec2bin(oct2dec(G2));
G2=str2num(reshape(G2,[],1))';
%%формируем параметры декодирования
yzli=[];
for i=0:2^(k-1)-1
yzli=[yzli {dec2bin(i,k-1)}];
end
% yzli = [{'00'} {'10'} {'01'} {'11'} ];
% формируем pyt
for i = 1:2^(k-1)
yzel=cell2mat(yzli(i));
yzel1=yzel(2:k-1) ;
% oneorzero=yzel(1);
d=0;
for j=1:2^(k-1)
yzel=cell2mat(yzli(j));
yzel2=yzel(1:k-2) ;
if yzel1 == yzel2
d=d+1;
if d==1
pyt(1,i)=j;
else
pyt(2,i)=j;
end
end
end
end
%формируем веса
for i=1:2^(k-1)
nomer_pred=pyt(1,i);
yzel_pred=cell2mat(yzli(nomer_pred));
yzel=cell2mat(yzli(i));
yzel=yzel(1);
if yzel=='1' yzel_mat(1)=1;
else yzel_mat(1)=0; end
for j=1:k-1 %в числовую форму
if yzel_pred(j)=='1' yzel_mat(j+1)=1;
else yzel_mat(j+1)=0; end
end
out_s1=0;
out_s2=0;
for j=1:k %само кодирование
out_s1 = out_s1 + G1(j)*yzel_mat(j);
out_s2 = out_s2 + G2(j)*yzel_mat(j);
end
out1 = mod(out_s1,2);
out2 = mod(out_s2,2);
ves (1,i) = {[ out1 , out2 ]}; %то что на выходе если 0
nomer_pred=pyt(2,i);
yzel_pred=cell2mat(yzli(nomer_pred));
yzel=cell2mat(yzli(i));
yzel=yzel(1);
if yzel=='1' yzel_mat(1)=1;
else yzel_mat(1)=0; end
for j=1:k-1 %в числовую форму
if yzel_pred(j)=='1' yzel_mat(j+1)=1;
else yzel_mat(j+1)=0; end
end
out_s1=0;
out_s2=0;
for j=1:k %само кодирование
out_s1 = out_s1 + G1(j)*yzel_mat(j);
out_s2 = out_s2 + G2(j)*yzel_mat(j);
end
out1 = mod(out_s1,2);
out2 = mod(out_s2,2);
ves (2,i) = {[ out1 , out2 ]}; %то что на выходе если 0
end
% добавляем метрики к неправдоподобным путям
add_to_metr = [0];
for i = 1:2^(k-1)-1
add_to_metr=[add_to_metr 20];
end
% формируем инделайпайп
for i = 1:2^(k-1)
yzel=cell2mat(yzli(i));
if yzel(1)=='1' in_delay_pipe(1,i)=1; in_delay_pipe(2,i)=1;
else in_delay_pipe(1,i)=0; in_delay_pipe(2,i)=0; end
end