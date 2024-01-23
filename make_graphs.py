from matplotlib import pyplot as plt
import csv
import math

TRIE_SPEED_FILE = "./results/trie-speed"
TRIE_FILTER_FILE = "./results/trie-filter"

BF_SPEED_FILE = "./results/bf-speed"
BF_FILTER_FILE = "./results/bf-filter"

CC_SPEED_FILE = "./results/cc-speed"
CC_FILTER_FILE = "./results/cc-filter"

BF_COLOR = "blue"
CC_COLOR = "orange"

N_WORDS = 370100

def make_fig():
    fig, ax = plt.subplots()
    return fig, ax

def speed_graph():
    bf_ks = []
    bf_sizes = []
    bf_times = []
    bf_fps = []

    cc_ks = []
    cc_sizes = []
    cc_times = []
    cc_fps = []

    trie_times = []
    true_fp = 0
    with open(BF_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time, fp, k, size in reader:
            bf_ks.append(k)
            bf_sizes.append(size / N_WORDS)
            bf_times.append(time)
            bf_fps.append(fp)

    with open(CC_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time, fp, _, size in reader:
            cc_ks.append(k)
            cc_sizes.append(size / N_WORDS)
            cc_times.append(time)
            cc_fps.append(fp)

    with open(TRIE_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time, fp, _ in reader:
            trie_times.append(time)
            true_fp = fp

    fig, ax = make_fig()
    ax.scatter(bf_sizes, bf_times, label="Bloom Filter")
    ax.scatter(cc_sizes, cc_times, label="Cuckoo Filter")
    ax.axhline(sum(trie_times) / len(trie_times), color="g", linestyle="--", label="Trie")
    ax.set_xlabel("Filter Size (Bits/Entries)")
    ax.set_ylabel("Execution Speed (microseconds)")
    ax.legend()
    fig.savefig("fig/speed-size.png")

def filter_graph():
    bf_filters = []
    bf_ks = []
    bf_sizes = []
    cc_ks = []
    cc_filters = []
    cc_sizes = []
    correct = 0
    trie_size = 0

    with open(TRIE_FILTER_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for _, c, size in reader:
            correct = c
            trie_size = size / N_WORDS

    with open(BF_FILTER_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for _, c, k, size in reader:
            bf_ks.append(k)
            bf_sizes.append(size / N_WORDS)
            bf_filters.append(1 - c / correct)

    with open(CC_FILTER_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for _, c, k, size in reader:
            cc_ks.append(k)
            cc_sizes.append(size / N_WORDS)
            cc_filters.append(1 - c / correct)

    print(trie_size)

    fig, ax = make_fig()

    x = list(range(1, int(N_WORDS * max(*bf_sizes, *cc_sizes)), 1000))
    y = [0.5 ** (i / N_WORDS * math.log(2)) for i in x]
    x = [i / N_WORDS for i in x]
    ax.plot(x, y, "--", label="Bloom Filter Theoretical", color=BF_COLOR)

    x = list(range(1, int(N_WORDS * max(*bf_sizes, *cc_sizes)), 1000))
    y = []
    for i in x:
        slots = (2 ** 17) * 3
        k = i / slots
        y.append(1 - ((2** k - 1) / (2 ** k)) ** 6)

    x = [i / N_WORDS for i in x]

    ax.plot(x, y, "--", label="Cuckoo Filter Theoretical", color=CC_COLOR)

    ax.set_xlabel("Filter Size (Bits/Entry)")
    ax.set_ylabel("False Positive Rate")
    ax.set_yscale("log")
    ax.scatter(bf_sizes,bf_filters, label="Bloom Filter Empirical", color=BF_COLOR)
    ax.scatter(cc_sizes,cc_filters, label="Cuckoo Filter Empirical", color=CC_COLOR)
    ax.legend()

    fig.savefig("fig/filter-size.png")




speed_graph()
filter_graph()

