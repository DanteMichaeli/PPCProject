import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')

fig, ax1 = plt.subplots(figsize=(10, 6))

# Plot OperationsPerSecond against Iterations
color = 'tab:blue'
ax1.set_xlabel('Iterations')
ax1.set_ylabel('Operations per Second', color=color)
ax1.plot(df['Iterations'], df['OperationsPerSecond'], marker='o', color=color)
ax1.tick_params(axis='y', labelcolor=color)
ax1.set_xscale('log')  # Log scales for iterations for better visualization
ax1.set_yscale('log')
ax1.grid(True, which="both", ls="--")

# Find and annotate the maximum OperationsPerSecond
max_ops_index = df['OperationsPerSecond'].idxmax()
max_ops = df['OperationsPerSecond'][max_ops_index]
max_ops_iterations = df['Iterations'][max_ops_index]
ax1.annotate(f'Max OPS: {max_ops:.2e}\nAt Iterations: {max_ops_iterations:.2e}',
             xy=(max_ops_iterations, max_ops),
             xytext=(max_ops_iterations, max_ops*0.8),
             arrowprops=dict(facecolor='black', shrink=0.05))

# second y-axis for CPU frequency
ax2 = ax1.twinx()
color = 'tab:red'
ax2.set_ylabel('CPU Frequency', color=color)
ax2.plot(df['Iterations'], df['CPUFrequency'], marker='o', color=color)
ax2.tick_params(axis='y', labelcolor=color)

fig.tight_layout()
plt.title('Operations per Second and CPU Frequency vs Iterations')
plt.show()
