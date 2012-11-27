function [distance] = haversine (long1, lat1, long2, lat2)

% Haversine formula: to calculate the great-circle distance between two 
% points – that is, the shortest distance over the earth’s surface – 
% giving an ‘as-the-crow-flies’ distance between the points (ignoring any 
% hills, of course!).

% http://www.movable-type.co.uk/scripts/latlong.html
% http://en.wikipedia.org/wiki/Great-circle_distance

% lat1 = 40.05; 
% long1 = -88.37;
% 
% lat2 = 36.324;
% long2 = -116.019;

dlong = deg2rad(long2 - long1);
dlat = deg2rad(lat2 - lat1);
a = sin(dlat/2.0)^2 + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dlong/2.0)^2;
c = 2 * atan2(sqrt(a), sqrt(1-a));
distance = 6372.8 * c;