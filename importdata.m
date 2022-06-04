data = load ("explicit.txt");
p = size(data);
n = p(1,2);
start = 1/(2*(n-2));
x = linspace(start,1-start,n-2);

y = [0, x, 1];
plot(y,data);