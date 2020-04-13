#!/usr/bin/perl

while (<DATA>) {
    chomp;
    my ($s, $i, $q, $p) = split /\s+/;

    if ($s eq 'B') {
	printf("EXPECT_EQ(orderBook_.bid(%d).quantity(), %d);\n", $i - 1, $q);
	printf("EXPECT_EQ(orderBook_.bid(%d).price(), %.2f);\n", $i - 1, $p);
    } else {
	printf("EXPECT_EQ(orderBook_.ask(%d).quantity(), %d);\n", $i - 1, $q);
	printf("EXPECT_EQ(orderBook_.ask(%d).price(), %.2f);\n", $i - 1, $p);
    }

}
__DATA__
A 10 40 240.1
A 9 50 240.05
A 8 180 239.95
A 7 400 239.9
A 6 500 239.85
A 5 150 239.8
A 4 120 239.75
A 3 390 239.7
A 2 300 239.65
A 1 75 239.6
B 1 100 239.55
B 2 280 239.5
B 3 200 239.45
B 4 50 239.35
B 5 200 239.3
B 6 125 239.25
B 7 140 239.15
B 8 250 239.05
B 9 100 239
B 10 50 238.95
