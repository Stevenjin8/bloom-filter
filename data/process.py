import sys
from nltk.tokenize import word_tokenize

text = sys.stdin.read()

tokenized = (x.strip().lower() for x in word_tokenize(text) if x.isalpha() and x)
if len(sys.argv) > 1:
    tokenized = set(tokenized)

print(*tokenized, sep="\n")
