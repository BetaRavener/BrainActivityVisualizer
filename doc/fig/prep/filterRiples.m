handle = figure;
set(handle, 'Position', [0 0 1920 600])

b = 0.4*sinc(0.4*(-15:15));
bwin = b.*hamming(31)';
[h,w] = freqz(b,1);
[hwin,wwin] = freqz(bwin,1);
x = w / pi;
y = 20*log10(abs(h));
ywin = 20*log10(abs(hwin));

ax1 = subplot(1,2,1); % top subplot
graph1 = plot(x,y);
set(graph1,'LineWidth',3);
axis([0 1 -70 10]);
title('Rectangular Window', 'FontSize', 32);
xlabel('Normalized Frequency (\times\pi rad/sample)', 'FontSize', 20)
ylabel('Magnitude (dB)', 'FontSize', 20)

ax2 = subplot(1,2,2); % bottom subplot
graph2 = plot(x,ywin);
set(graph2,'LineWidth',3);
axis([0 1 -70 10]);
title('Hamming Window', 'FontSize', 32);
xlabel('Normalized Frequency (\times\pi rad/sample)', 'FontSize', 20)
ylabel('Magnitude (dB)', 'FontSize', 20)

set(handle,'Units','points');
pos = get(handle,'Position');
set(handle,'PaperPositionMode','Auto','PaperUnits','points','PaperSize',[pos(3), pos(4)])
print(handle,'../filterRiples','-dpdf','-r0')