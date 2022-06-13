function [vb] = ConvDecoder(input_bits)
k = 7;
G1 = 171;
G2 = 133;
length_dibits = length(input_bits )/2;
[yzli, ves,add_to_metr,pyt,in_delay_pipe] = genyzl;
nves=length(ves);
vb=[];
pyti=[];
kb=1;
for i=1:length_dibits
    dibits(i)={[input_bits(2*i-1),input_bits(2*i)]};
end
metk=[];
for n=1:length_dibits
    met1=[];
    met2=[];
    for i=1:nves
        met1=[ met1 sum(xor(dibits{n}, ves{1,i}))];
        met2=[ met2 sum(xor(dibits{n}, ves{2,i}))];
    end
    met=[met1;met2];
    metk=[metk; met];
    % считаем метрики путей
    for i=1:2
        for j=1:nves
            sw(i,j)=met(i,j)+add_to_metr(pyt(i,j));
        end
    end
    add_to_metr = min(sw);
    pyti=[pyti; pyt]; % добавляются все пути, потом чистятся
    for k=1:nves
        if (sw(1,k) <= sw (2,k) )
            pyti(2*n,k)=0; %обнуляем один из путей
        else
            pyti(2*n-1,k)=0;
        end
    end
    kp=n; %
    while kp>kb
        for k=1:nves
            if (sum([pyti(2*kp-1,:)==k pyti(2*kp,:)==k])==0)
                pyti(2*kp-2,k)=0;
                pyti(2*kp-3,k)=0;
            end
        end
        kp=kp-1;
    end
    %проверяем единственность пути
    p1=length(find(pyti(2*kb-1,:)));
    p2=length(find(pyti(2*kb,:)));
    if ((p1==1) && (p2==0)) || ((p1==0) && (p2==1));
        nb1=find(pyti(2*kb-1,:)); nb2=find(pyti(2*kb,:));
        if(p1==1) && (p2==0); vb=[vb in_delay_pipe(1,nb1)]; kb=kb+1; end;
        if(p1==0) && (p2==1); vb=[vb in_delay_pipe(2,nb2)]; kb=kb+1; end;
    end;
    if (n == length_dibits)
        min_end_metr=min(min(sw));
        for i=1:2
            for j=1:nves
                if(sw(i,j))==min_end_metr
                    end_way=pyti(2*length_dibits,j)+pyti(2*length_dibits-1,j);
                    vb(length_dibits)=in_delay_pipe(i,j); %декидируем
                end
            end
        end
        delt=length_dibits - kb+1; %сколько бит не декодировали
        for d=delt:-1:2; %идем с конца и декодируем неизвестные биты
            vb(kb-2+d) = in_delay_pipe(1,end_way);
            end_way = pyti(2*(kb-2)+2*d ,end_way ) + pyti(2*(kb-2)+2*d-1 ,end_way );
        end
    end
end