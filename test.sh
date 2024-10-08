#!/bin/bash

assert() {
	expected="$1"
	input="$2"
	
	./9cc "$input" > tmp.s
	cc -o tmp tmp.s
	./tmp
	actual="$?"

	if [ "$actual" = "$expected" ]; then
		echo "$input => $actual"
	else
		echo "$input => $expected expected, but got $actual"
		exit 1
	fi
}

assert 0 "0;"
assert 42 "42;"
assert 41 "12 + 34 - 5;"
assert 47 "5 + 6 * 7;"
assert 15 "5*(9-6);"
assert 4 "(3+5)/2;"
assert 10 "-10+20;"

assert 0 "0==1;"
assert 1 "42==42;"
assert 0 "42!=42;"
assert 1 "0!=1;"

assert 1 "10>0;"
assert 0 "0>10;"
assert 1 "10>=10;"
assert 0 "9>=10;"

assert 1 "-1<0;"
assert 0 "0<-1;"
assert 1 "10<=10;"
assert 0 "10<=9;"

assert 10 "a=10;a;"
assert 3 "a=1;b=2;a+b;"
assert 10 "abc=6;efg=4;abc+efg;"

assert 2 "return 2;"
assert 2 "return 2; return 4;"

assert 1 "if(1==1) 1;"
assert 0 "if(1==0) 1;0;"

assert 1 "if(1==1) 1; else 0;"
assert 0 "if(1==0) 1; else 0;"

assert 10 "a=0; while(a < 10) a=a+1; return a;"
assert 0 "a=0; while(a > 10) a=a+1; return a;"

assert 10 "for(a=0; a<10; a++) a; return a;"

echo OK
