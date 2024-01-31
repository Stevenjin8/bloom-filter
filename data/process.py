import sys

import nltk
from nltk.tokenize import word_tokenize

nltk.download("punkt")
with open(0, "r", encoding="utf-8", errors="ignore") as f:
    text = f.read()

tokenized = (x.strip().lower() for x in word_tokenize(text) if x.isalpha() and x)
if len(sys.argv) > 1:
    tokenized = set(tokenized)

print(*tokenized, sep="\n")
