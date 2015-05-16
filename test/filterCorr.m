function [corr] = filterCorr(name, filterCoeff, order)
fileID = fopen('sig.txt','r');
sig = fscanf(fileID, '%f');
fclose(fileID);

fileID = fopen(name,'r');
sigApp = fscanf(fileID, '%f');
fclose(fileID);

sigFiltered = filter(filterCoeff, 1, sig, zeros([1 order * 2]));

absDiff = abs(sigApp - sigFiltered);
maxDiff = max(absDiff);
avgDiff = mean(absDiff);
corr = [maxDiff avgDiff];

fprintf('Difference with %s: Max %f, Avg %f\n', name, maxDiff, avgDiff)

fclose('all');