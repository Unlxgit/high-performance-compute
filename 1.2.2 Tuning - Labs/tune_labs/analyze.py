import numpy as np
import matplotlib.pyplot as plt

# load the data files
# columns:
# 0: memory footprint in kB
# 1: Mflop/s of distance(...)
# 2: Mflop/s of distcheck(...)
# 3: Mflop/s of total program
# 4: runtime in secs
data_aos = np.loadtxt('aos.gcc.dat')
data_soa = np.loadtxt('soa.gcc.dat')

# plot Mflop/s of distance(...) vs memory footprint
plt.figure(1)
plt.figure(1)

# distance
plt.plot(data_aos[:, 0], data_aos[:, 1],
         color='tab:blue', linestyle='-', marker='o',
         label='AoS-distance')
plt.plot(data_soa[:, 0], data_soa[:, 1],
         color='tab:blue', linestyle='--', marker='o',
         label='SoA-distance')

# distcheck
plt.plot(data_aos[:, 0], data_aos[:, 2],
         color='tab:orange', linestyle='-', marker='s',
         label='AoS-distcheck')
plt.plot(data_soa[:, 0], data_soa[:, 2],
         color='tab:orange', linestyle='--', marker='s',
         label='SoA-distcheck')

# total
plt.plot(data_aos[:, 0], data_aos[:, 3],
         color='tab:green', linestyle='-', marker='^',
         label='AoS-total')
plt.plot(data_soa[:, 0], data_soa[:, 3],
         color='tab:green', linestyle='--', marker='^',
         label='SoA-total')

plt.xlabel('Memory footprint (kB)')
plt.ylabel('Performance (Mflop/s)')
plt.title('Data structure comparison: AoS vs SoA')
plt.legend()
plt.grid(True, axis='both')
# --- log scale ---
plt.xscale('log', base=2)

xmin = min(data_aos[:, 0].min(), data_soa[:, 0].min())
xmax = max(data_aos[:, 0].max(), data_soa[:, 0].max())

powers = np.arange(
    np.floor(np.log2(xmin)),
    np.ceil(np.log2(xmax)) + 1
)

ticks = 2 ** powers

# label only every second power
labels = []
for i, t in enumerate(ticks):
    if i % 2 == 0:
        labels.append(f'{int(t)}')
    else:
        labels.append('')

plt.xticks(ticks, labels)
plt.savefig('distance_performance.png')



plt.figure(2)

plt.plot(data_aos[:, 0], data_aos[:, 4],
         color='tab:blue', linestyle='-', marker='o',
         label='AoS runtime')
plt.plot(data_soa[:, 0], data_soa[:, 4],
         color='tab:blue', linestyle='--', marker='o',
         label='SoA runtime')

plt.xlabel('Memory footprint (kB)')
plt.ylabel('Runtime (s)')
plt.title('Runtime comparison: AoS vs SoA')
plt.legend()
plt.grid(True, which='both')
plt.xscale('log', base=2)

# reuse the same tick scheme as plot 1
plt.xticks(ticks, labels)

plt.savefig('runtime_comparison.png', dpi=300, bbox_inches='tight')
