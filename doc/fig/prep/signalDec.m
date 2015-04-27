h = figure;
set(h, 'Position', [0 0 1920 600])

[hdr, record] = edfread('../../../data/TEST.edf');
y = record(1,:);
x = linspace(0, length(y), length(y));
subplot(1,3,1);
plot(x,y);
title('Original', 'FontSize', 32);
axis([0 length(y) -300 200]);

N = 100;
pick = 1:N:length(x);
xn = x(pick);
yn = y(pick);
subplot(1,3,2);
plot(xn, yn);
title('N-th sample', 'FontSize', 32);
axis([0 length(y) -300 200]);

N = N * 2;
pick = 1:N:length(x);
xm = [];
ym = [];
for idx = pick(1:end-1)
   maxv = max(y(idx:idx+N));
   minv = min(y(idx:idx+N));
   xm = [xm idx+N/2 idx+N];
   ym = [ym maxv minv];
end
subplot(1,3,3);
plot(xm, ym);
title('Min-Max', 'FontSize', 32);
axis([0 length(y) -300 200]);

set(h,'Units','points');
pos = get(h,'Position');
set(h,'PaperPositionMode','Auto','PaperUnits','points','PaperSize',[pos(3), pos(4)])
print(h,'../signalDec','-dpdf','-r0')