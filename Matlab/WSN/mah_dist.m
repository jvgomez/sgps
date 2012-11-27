function d = mah_dist (p,X, mu, SIGMA)
% p = coordinates of the point to evaluate
% X = coordinates of the station
% mu = mean of the error distribution
% SIGMA = covariance of the error distribution

mu = mu + X;

%d(I) = (Y(I,:)-mu)*inv(SIGMA)*(Y(I,:)-mu)';
d = (p - mu) * inv(SIGMA) * (p - mu)';