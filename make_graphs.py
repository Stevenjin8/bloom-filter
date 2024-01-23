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
HP_N_WORDS = 454255


def make_fig():
    fig, ax = plt.subplots()
    return fig, ax

def speed_graph():
    bf_ks = []
    bf_sizes = []
    bf_times = []
    bf_itimes = []
    bf_fps = []

    cc_ks = []
    cc_sizes = []
    cc_times = []
    cc_itimes = []
    cc_fps = []

    trie_times = []
    trie_itimes = []
    true_fp = 0
    with open(BF_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time, fp, k, size, itime in reader:
            bf_ks.append(k)
            bf_sizes.append(size / N_WORDS)
            bf_times.append(time / HP_N_WORDS)
            bf_fps.append(fp)
            bf_itimes.append(itime / HP_N_WORDS)

    with open(CC_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time, fp, _, size, itime in reader:
            cc_ks.append(k)
            cc_sizes.append(size / N_WORDS)
            cc_times.append(time / HP_N_WORDS)
            cc_fps.append(fp)
            cc_itimes.append(itime / HP_N_WORDS)

    with open(TRIE_SPEED_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for time, fp, _, itime in reader:
            trie_times.append(time / HP_N_WORDS)
            true_fp = fp
            trie_itimes.append(itime / HP_N_WORDS)

    fig, ax = make_fig()
    ax.scatter(bf_sizes, bf_times, label="Bloom Filter")
    ax.scatter(cc_sizes, cc_times, label="Cuckoo Filter")
    ax.axhline(
        sum(trie_times) / len(trie_times), color="g", linestyle="--", label="Trie"
    )
    ax.set_xlabel("Filter Size (Bits/Entries)")
    ax.set_ylabel("Lookup Speed (microseconds/insertion)")
    ax.legend()
    fig.savefig("fig/speed-size.png")

    fig, ax = make_fig()
    ax.scatter(bf_sizes, bf_itimes, label="Bloom Filter")
    ax.scatter(cc_sizes, cc_itimes, label="Cuckoo Filter")
    ax.axhline(
        sum(trie_times) / len(trie_times), color="g", linestyle="--", label="Trie"
    )
    ax.set_xlabel("Filter Size (Bits/Entries)")
    ax.set_ylabel("Insertion Speed (microseconds/insertion)")
    ax.set_ylim(0, 0.4)
    ax.legend()
    fig.savefig("fig/ispeed-size.png")


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
        for _, c, size, _ in reader:
            correct = c
            trie_size = size / N_WORDS

    with open(BF_FILTER_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for _, c, k, size, _ in reader:
            bf_ks.append(k)
            bf_sizes.append(size / N_WORDS)
            bf_filters.append(1 - c / correct)

    with open(CC_FILTER_FILE, "r") as f:
        reader = csv.reader(f, quoting=csv.QUOTE_NONNUMERIC)
        for _, c, k, size, _ in reader:
            cc_ks.append(k)
            cc_sizes.append(size / N_WORDS)
            cc_filters.append(1 - c / correct)

    fig, ax = make_fig()

    x = list(range(1, int(N_WORDS * max(*bf_sizes, *cc_sizes)), 1000))
    y = [0.5 ** (i / N_WORDS * math.log(2)) for i in x]
    x = [i / N_WORDS for i in x]
    ax.plot(x, y, "--", label="Bloom Filter Theoretical", color=BF_COLOR)

    x = list(range(1, int(N_WORDS * max(*bf_sizes, *cc_sizes)), 1000))
    y = []
    for i in x:
        # Some hard coded values...
        # 2^17 buckets, each with 3 slots
        slots = (2**17) * 3
        k = i / slots  # number of buckets
        # each item has two buckets with 3 (at most) items each.
        # these hard coded values are reused elsewhere.
        y.append(1 - ((2**k - 1) / (2**k)) ** 6)

    x = [i / N_WORDS for i in x]

    ax.plot(x, y, "--", label="Cuckoo Filter Theoretical", color=CC_COLOR)

    ax.set_xlabel("Filter Size (Bits/Entry)")
    ax.set_ylabel("False Positive Rate")
    ax.set_yscale("log")
    ax.scatter(bf_sizes, bf_filters, label="Bloom Filter Empirical", color=BF_COLOR)
    ax.scatter(cc_sizes, cc_filters, label="Cuckoo Filter Empirical", color=CC_COLOR)
    ax.legend()
    fig.savefig("fig/filter-size.png")

speed_graph()
filter_graph()
