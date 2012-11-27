clear
clf

		VTR = 1.e-6; 
		D = 3; 

		XVmin = [0.0,0.0,0.0]; 
		XVmax = [10,10,2*pi]; % Límites de búsqueda.

        stars = 4; % Puntas del polígono (cuadrado).
        r=5; % Semidiagonal del cuadrado a encontrat.

%% Building the stars.
for i = 1:stars
    for j = 1:2
        star(i,j) = rand(1)*10;
    end
end
plot(star(:,1),star(:,2),'x')
hold on

%%Variables Differential Evolution.
NP = 150; 
itermax = 100; 
F = 0.8; 
CR = 0.8; 
strategy = 7;
refresh = 10; 

%Llamada a D.E.
[x,f,nf] = gavec3('fitness_star',VTR,D,XVmin,XVmax,star,NP,itermax,F,CR,strategy,refresh);


%% Reconstrucción del cuadrado a partir de su centro (x,y) y su ángulo.
 xx=x(1);yy=x(2);theta=x(3);
        p1=[xx+r*cos(theta),yy+r*sin(theta)];
        p2=[xx-r*cos(deg2rad(90)-theta),yy+r*sin(deg2rad(90)-theta)];
        p3=[xx-r*cos(theta),yy-r*sin(theta)];
        p4=[xx+r*cos(deg2rad(90)-theta),yy-r*sin(deg2rad(90)-theta)];

%% Plotting final.
p = [p1;p2;p3;p4;p1];
line(p(:,1),p(:,2));

for i =1:stars
   line([p(i,1) star(i,1)],[p(i,2) star(i,2)], 'Color', 'r'); 
end
axis image


