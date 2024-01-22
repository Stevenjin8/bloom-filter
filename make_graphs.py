from matplotlib import pyplot as plt
import csv
import math

TRIO_SPEED_FILE = "./results/trie-speed"
TRIO_FILTER_FILE = "./results/trie-filter"

BF_SPEED_FILE = "./results/bf-speed"
BF_FILTER_FILE = "./results/bf-filter"

N_WORDS = 370100

def make_fig():
    fig, ax = plt.subplots()
    return fig, ax

def speed_graph():
    ks = []
    sizes = []
    times = []
    fns = []
    true_fn = 0
    trio_times = []
    with open(BF_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time, fn, k, size in reader:
            ks.append(k)
            sizes.append(size)
            times.append(time)
            fns.append(fn)

    with open(TRIO_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time,fn in reader:
            trio_times.append(time)
            true_fn = fn

    fig, ax = make_fig()
    ax.scatter(sizes, times)
    ax.axhline(sum(trio_times) / len(trio_times), color="g", linestyle="--")
    ax.set_xlabel("Filter Size (Bits)")
    ax.set_ylabel("Execution Speed (microseconds)")
    fig.savefig("fig/speed-size.png")

    fig, ax = make_fig()
    ax.scatter(ks, times)
    ax.axhline(sum(trio_times) / len(trio_times), color="g", linestyle="--")
    ax.set_xlabel("Number of Hash Functions")
    ax.set_ylabel("Execution Time (microseconds)")
    fig.savefig("fig/speed-k.png")

def filter_graph():
    filters = []
    ks = []
    sizes = []
    correct = 0

    with open(TRIO_FILTER_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for _, c in reader:
            correct = c

    with open(BF_FILTER_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for _, c, k, size in reader:
            ks.append(k)
            sizes.append(size)
            filters.append(1 - c / correct)

    fig, ax = make_fig()

    x = list(range(1, int(max(sizes)), 1000))
    y = [0.5 ** (i / N_WORDS * math.log(2)) for i in x]  # log is ln


    ax.plot(x, y, "g--", label="Theoretic")
    ax.set_xlabel("Filter Size (Bits)")
    ax.set_ylabel("False Negative Rate")
    ax.set_yscale("log")
    ax.scatter(sizes,filters, label="Empirical")
    ax.legend()

    fig.savefig("fig/filter-size.png")




speed_graph()
filter_graph()

