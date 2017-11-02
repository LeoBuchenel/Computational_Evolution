%% Data Loading
close all; clear all;

data = load('plant.out');
N = sqrt(size(data,2)); % N = L-1
tfin = size(data,1);

sys_param = load('system_param.out');
animal_param_begin = load('animal_param_begin.out');
animal_param_end = load('animal_param_end.out');
t = [0:tfin-1];

MaxDensity = max(data(:));



%% Animal/plant plot
figure
plot(sys_param(:,1));
hold on;
plot(sys_param(:,2));
xlabel('$t$');
ylabel('Number of specimens');
legend({'Animals', 'Plants'},'location', 'best');

%% Histogram plot
figure
histogram(animal_param_begin(:,1),100);
xlabel('force (beginning)');
ylabel('Number of animals');

figure
histogram(animal_param_begin(:,3));
xlabel('Number of offsprings (beginning)');
ylabel('Number of animals');

figure
histogram(animal_param_end(:,1),100);
xlabel('Force (end)');
ylabel('Number of animals');

figure
histogram(animal_param_end(:,3));
xlabel('Number of offsprings (end)');
ylabel('Number of animals');



%% Density plotting
for i = 1 : tfin
    Density(:,:, i) = transpose(reshape(data(i,:), [N,N]));
end

figure
for i = 1 : tfin
    
h=imagesc(Density(:,:,i));
set(gca,'YDir', 'Normal');

c = colorbar;
c.Label.Interpreter = 'latex';
c.Label.String = 'Number of plants on cell';
colormap(flipud(hot));
caxis([0, MaxDensity]);


ax = gca;
ax.GridAlpha = 0.5;

xlabel('$x$');
ylabel('$y$');
title(sprintf('$t$=%0.2f s',t(i)));
pause(.1)
    if ~ishandle(h)
        break % Arrete l'animation si la fenetre est fermee
    end
end

