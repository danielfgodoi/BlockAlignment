( time bin/BlockAlignment -b test/block -t test/text test/text-2 test/text-b test/news test/news-2 ) > results/block 2>&1
( time bin/BlockAlignment -b test/block-b -t test/text-b test/news test/news-2 ) > results/block-b 2>&1
( time bin/BlockAlignment -b test/part -t test/news test/news-2 ) > results/part 2>&1
( time bin/BlockAlignment -b test/part-m -t test/news test/news-2 ) > results/part-m 2>&1
( time bin/BlockAlignment -b test/part-b -t test/news test/news-2 ) > results/part-b 2>&1
