import sys

def log_error(*messages, sep=" ", end="\n"):
    print(*messages, file=sys.stderr, sep=sep, end=end)
