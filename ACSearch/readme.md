# ACSearch

```sh
./run.sh

-------------------- Python --------------------
Search simple text with python
patterns: ['ash', 'shex', 'bcd', 'sha', 'ab', 'abc', 'aba']
text: secashcvashexbcdashareerwqrqewrababcabacabacc
ret: 
  ab: [31, 33, 36, 40]
  aba: [31, 36, 40]
  abc: [33]
  ash: [3, 8, 16]
  bcd: [13]
  sha: [17]
  shex: [9]
10000次，Python耗时: 0.17422824900131673
-------------------- Python END --------------------
-------------------- CPP --------------------
Search simple text with cpp
patterns: ['ash', 'shex', 'bcd', 'sha', 'ab', 'abc', 'aba']
text: secashcvashexbcdashareerwqrqewrababcabacabacc
ret: 
  ab: [31, 33, 36, 40]
  aba: [31, 36, 40]
  abc: [33]
  ash: [3, 8, 16]
  bcd: [13]
  sha: [17]
  shex: [9]
10000次，CPP耗时: 0.04310589699889533
-------------------- CPP END --------------------

```