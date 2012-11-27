function  result=getgooddays5(stations)
%Calculates de days that appear in all the stations

var=zeros(5300,5);
length(stations{1,1}.days)
for i=1:size(stations{1,1}.days)
    var(i,1)= i;
    i
    for s=2:5
        for j=1:size(stations{1,s}.days)
            if (stations{1,1}.years(i)== stations{1,s}.years(j))&&(stations{1,1}.days(i)==stations{1,s}.days(j))
                var(i,s)= j;
            end
        end
    end
end

%First row shows the real coordinates
result(1,1) = 0;
result(1,2) = 0;

for s=1:5
    result(1,2*s+1)=stations{1,2*s+1}.real_longitude;
    result(1,2*s+2)=stations{1,2*s+2}.real_latitude;
end

%Columns 1 and 2 show days and years.
%Columns 3 and 4 show longitude and latitude of station 1, 5 and 6 of
%station 2 and so on

resultindex=1;
length(stations{1,1}.days)
for i=1:size(stations{1,1}.days)
    i
    if ((var(i,1)~=0)&&(var(i,2)~=0)&&(var(i,3)~=0)&&(var(i,4)~=0)&&(var(i,5)~=0))
        result(resultindex,1)=stations{1,1}.days(var(i,1));
        result(resultindex,2)=stations{1,1}.years(var(i,1));
        for s=1:5
            %result(resultindex,2*s+1)=stations{1,s}.latitudes(var(i,s));
            %result(resultindex,2*s+2)=stations{1,s}.longitudes(var(i,s));
            result(resultindex,2*s+1)=stations{1,s}.longitudes(var(i,s));
            result(resultindex,2*s+2)=stations{1,s}.latitudes(var(i,s));
        end
        resultindex=resultindex+1;
    end
end
