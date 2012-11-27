
function F = fitness_star(cit,star)
        
%%Calcular aqui los puntos en funcion de la geometria de los sensores
r=5;
        x=cit(1);y=cit(2);theta=cit(3);
        p1=[x+r*cos(theta),y+r*sin(theta)];
        p2=[x-r*cos(deg2rad(90)-theta),y+r*sin(deg2rad(90)-theta)];
        p3=[x-r*cos(theta),y-r*sin(theta)];
        p4=[x+r*cos(deg2rad(90)-theta),y-r*sin(deg2rad(90)-theta)];
        F = euc_dist(star(1,:)',p1')+euc_dist(star(2,:)',p2')+euc_dist(star(3,:)',p3')+euc_dist(star(4,:)',p4')^2;