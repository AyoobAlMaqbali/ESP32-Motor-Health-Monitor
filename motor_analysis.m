data = fileread('tests/high_current_test.txt');

values = regexp(data, ...
    'Voltage:\s*([\d.]+)\s*V\s*\|\s*Current:\s*(-?[\d.]+)\s*mA', ...
    'tokens');

voltage = zeros(length(values), 1);
current = zeros(length(values), 1);

for i = 1:length(values)
    voltage(i) = str2double(values{i}{1});
    current(i) = str2double(values{i}{2});
end

time = (0:length(current)-1) * 0.5;

figure;
plot(time, current, 'LineWidth', 1.5);
hold on;
yline(65, '--r', 'High Current Threshold');
xlabel('Time (seconds)');
ylabel('Current (mA)');
title('DC Motor Current During Fault Testing');
grid on;

figure;
plot(time, voltage, 'LineWidth', 1.5);
hold on;

yline(4.5, '--r', 'Low Voltage Threshold');
yline(5.5, '--r', 'High Voltage Threshold');

xlabel('Time (seconds)');
ylabel('Voltage (V)');
title('DC Motor Voltage During Fault Testing');
grid on;
