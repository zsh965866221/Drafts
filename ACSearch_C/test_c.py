# coding = utf-8

run_str = """
ACSearch.find_all(patterns=patterns, text=text)
"""
setup_str = """
import ACSearch

patterns = ['ash', 'shex', 'bcd', 'sha', 'ab', 'abc', 'aba']
text = 'secashcvashexbcdashareerwqrqewrababcabacabacc'
"""


import ACSearch
print('-' * 20 + ' C ' + '-' * 20)
patterns = ['ash', 'shex', 'bcd', 'sha', 'ab', 'abc', 'aba']
text = 'secashcvashexbcdashareerwqrqewrababcabacabacc'
print('Search simple text with cpp')
print('patterns: {}'.format(patterns))
print('text: {}'.format(text))
ret = ACSearch.find_all(patterns=patterns, text=text)
print('ret: ')
for key, value in sorted(ret.items()):
    print('  {}: {}'.format(key, value))
import timeit
t = timeit.timeit(stmt=run_str, setup=setup_str, number=10000)
print('10000次，C耗时: {}'.format(t))
print('-' * 20 + ' C END ' + '-' * 20)