#python3 graph.py
import matplotlib.pyplot as plt
import csv

data = {}

with open('stats.csv', 'r') as f:
    read = csv.DictReader(f)
    for row in read:
        t = int(row['Threads'])
        if t not in data:
            data[t] = {'n': [], 'time': []}
        data[t]['n'].append(int(row['N']))
        data[t]['time'].append(float(row['Time']))

for t in sorted(data.keys()):
    plt.plot(data[t]['n'], data[t]['time'], marker='o', label=f'{t} Threads')

plt.xlabel('Размер матрицы (N)')
plt.ylabel('Время (с)')
plt.legend()
plt.grid()
plt.show()
