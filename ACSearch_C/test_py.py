# coding = uts-8

from collections import deque

class Node:
    def __init__(self):
        self.key = None
        self.ending = False
        self.maps = dict()
        self.failure = None
        self.parent = None

    def __repr__(self):
        return self.key

class ACSearch:
    def __init__(self, patterns):
        self.root = Node()
        self.root.failure = self.root
        self.patterns = patterns
        self.build()

    def build(self):
        # build trie tree
        for pattern in self.patterns:
            p = self.root
            d = 0
            for c in pattern:
                d += 1
                if c not in p.maps:
                    t = Node()
                    t.key = c
                    t.depth = d
                    p.maps[c] = t
                    t.parent = p
                p = p.maps[c]
            p.ending = True
        # build failure
        # build failure with BFS
        queue = deque()
        for k, v in self.root.maps.items():
            v.failure = self.root
            queue.append(v)
        while len(queue) != 0:
            p = queue.popleft()
            for k, v in p.maps.items():
                failure = p.failure
                while k not in failure.maps and failure is not self.root:
                    failure = failure.failure
                if k in failure.maps:
                    v.failure = failure.maps[k]
                else:
                    v.failure = failure
                queue.append(v)

    def find_all(self, text):
        ret = {}
        for pattern in self.patterns:
            ret[pattern] = []
        p = self.root
        for index, c in enumerate(text):
            while c not in p.maps and p is not self.root:
                p = p.failure
            if c in p.maps:
                p = p.maps[c]
                if p.ending is True:
                    # matched
                    pattern = []
                    q = p
                    while q.parent is not None:
                        pattern.append(q.key)
                        q = q.parent
                    pattern.reverse()
                    pattern = ''.join(pattern)
                    ret[pattern].append(index - len(pattern) + 1)
        return ret


run_str = """
searcher.find_all(text)
"""
setup_str = """
from __main__ import ACSearch
patterns = ['ash', 'shex', 'bcd', 'sha', 'ab', 'abc', 'aba']
text = 'secashcvashexbcdashareerwqrqewrababcabacabacc'
searcher = ACSearch(patterns)
"""

if __name__ == '__main__':
    print('-' * 20 + ' Python ' + '-' * 20)
    patterns = ['ash', 'shex', 'bcd', 'sha', 'ab', 'abc', 'aba']
    text = 'secashcvashexbcdashareerwqrqewrababcabacabacc'
    searcher = ACSearch(patterns)
    print('Search simple text with python')
    print('patterns: {}'.format(patterns))
    print('text: {}'.format(text))
    ret = searcher.find_all(text)
    print('ret: ')
    for key, value in sorted(ret.items()):
        print('  {}: {}'.format(key, value))
    import timeit
    t = timeit.timeit(stmt=run_str, setup=setup_str, number=10000)
    print('10000次，Python耗时: {}'.format(t))
    print('-' * 20 + ' Python END ' + '-' * 20)