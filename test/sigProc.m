fileID = fopen('sig.txt','r');
sig = fscanf(fileID, '%f');

samplingF = 250;
nyquistF = samplingF / 2;

black5 = blackman(11).';
black10 = blackman(21).';
hamm5 = hamming(11).';
hamm10 = hamming(21).';

black5 = black5 .* (length(black5) / sum(abs(black5)));
black10 = black10 .* (length(black10) / sum(abs(black10)));
hamm5 = hamm5 .* (length(hamm5) / sum(abs(hamm5)));
hamm10 = hamm10 .* (length(hamm10) / sum(abs(hamm10)));

low5order5 = fircls1(2*5, 5 / nyquistF, 1, 1);
low10order5 = fircls1(2*5, 10 / nyquistF, 1, 1);
low5order10 = fircls1(2*10, 5 / nyquistF, 1, 1);
low10order10 = fircls1(2*10, 10 / nyquistF, 1, 1);

low5order5 = low5order5 ./ sum(abs(low5order5));
low10order5 = low10order5 ./ sum(abs(low10order5));
low5order10 = low5order10 ./ sum(abs(low5order10));
low10order10 = low10order10 ./ sum(abs(low10order10));

high50order5 = fircls1(2*5, 50 / nyquistF, 1, 1, 'high');
high100order5 = fircls1(2*5, 100 / nyquistF, 1, 1, 'high');
high50order10 = fircls1(2*10, 50 / nyquistF, 1, 1, 'high');
high100order10 = fircls1(2*10, 100 / nyquistF, 1, 1, 'high');

high50order5 = high50order5 ./ sum(abs(high50order5));
high100order5 = high100order5 ./ sum(abs(high100order5));
high50order10 = high50order10 ./ sum(abs(high50order10));
high100order10 = high100order10 ./ sum(abs(high100order10));

filterCorr('low5Hamm5', low5order5 .* hamm5, 5);
filterCorr('low5Hamm10', low5order10 .* hamm10, 10);
filterCorr('low5Black5', low5order5 .* black5, 5);
filterCorr('low5Black10', low5order10 .* black10, 10);
filterCorr('low10Hamm5', low10order5 .* hamm5, 5);
filterCorr('low10Hamm10', low10order10 .* hamm10, 10);
filterCorr('low10Black5', low10order5 .* black5, 5);
filterCorr('low10Black10', low10order10 .* black10, 10);

filterCorr('high50Hamm5', high50order5 .* hamm5, 5);
filterCorr('high50Hamm10', high50order10 .* hamm10, 10);
filterCorr('high50Black5', high50order5 .* black5, 5);
filterCorr('high50Black10', high50order10 .* black10, 10);
filterCorr('high100Hamm5', high100order5 .* hamm5, 5);
filterCorr('high100Hamm10', high100order10 .* hamm10, 10);
filterCorr('high100Black5', high100order5 .* black5, 5);
filterCorr('high100Black10', high100order10 .* black10, 10);