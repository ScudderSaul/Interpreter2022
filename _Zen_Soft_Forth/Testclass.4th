" 0) test . " printstring cr
1 . 2 . 3 . cr

" 1) test + and dup " printstring cr
21245 dup . 7194 dup . + . cr

" 2) test - " printstring cr
11111 dup . 22222 dup . - . cr


: goog if 222 111 + else 777 111 - then . ;

: soog if 123 456 + . then ;

' soog decompile
.s cr

" 3) test ( : ; if else then )" printstring cr
0 soog
1 soog
0 goog
1 goog

: tst-depth depth if " Unclean stack " else " OK " then printstring cr ;

.s cr

" 4) This is a test string" cr printstring cr

22 22 22 + + . cr

: moog " this is another test string " ;

moog printstring cr

" 5) test begin until " printstring cr
: hoog 1 begin 1 + dup 10 > until " the output was " printstring  . ; 

hoog cr
" 6) test constant " printstring cr
2 constant noog 
noog . cr
" 7) test rot " printstring
1 dup . 2 dup . 3 dup . rot . . . cr
" 8) test multiply " printstring
1111 dup . 2 dup . * . cr
" 9) test divide " printstring
10000 dup . 100 dup . / . cr

" 10) test variable " printstring
777 variable roog cr

" test @ " printstring
roog @ . cr

" test ! " printstring
888 roog ! 
roog @ . cr

tst-depth

" 11) test +! " printstring
111 roog +! roog @ . cr

" 12) test max " printstring
1000 dup . 2000 dup . max . cr
" 13) test min " printstring
1000 dup . 2000 dup . min . cr
" 14) test == " printstring
1000 dup . 2000 dup . == . cr
" 15) test <> " printstring
1000 dup . 2000 dup . <> . cr
" 16) test > " printstring
1000 dup . 2000 dup . > . cr
" 17) test >= " printstring
1000 dup . 2000 dup . >= . cr
" 18) test 0= " printstring
2000 dup . 0= . cr

tst-depth

" 19) compile testtrue " printstring cr

: testtrue 0= 
  if " false " printstring cr 
  else " true " printstring cr 
  then ; 
cr
" 20) test negate " printstring 
25 negate cr
roog ! 

tst-depth

" 21) test == " printstring cr
24 negate dup . roog @ dup . == testtrue
tst-depth

 
" 22) test < " printstring cr
24 negate dup . roog @ dup . < testtrue 
tst-depth


" 23) test str= " printstring cr

: tests1 " The rain in Spain " ;
: tests2 " The same in Maine " ;
: tests3 " aaa" ;

tst-depth
tests1 printstring cr
tests2 printstring cr
tst-depth

tests1 tests2 str= printstring cr
tests1 printstring 
tests2 printstring cr
tst-depth

" 24) test substr " printstring cr 
tests1 printstring 
tests3 tests1 4 7 substr printstring cr
tests3 printstring cr

tst-depth

" 25) test str+ " printstring cr
: test4 " again " ; 
tests1 test4 str+ printstring cr

-23 . cr

" 26) test do .. loop " printstring cr

: testloop 0 10 0 do 1 + dup . loop . ;
.s

testloop cr


" 27) test string " printstring cr
 " Above the town there was a grey wall " string townwall
 townwall printstring cr 

.s
' townwall decompile
.s
tst-depth

" 28) test newchar " printstring cr

 " HOOT" string hoot

 " GOOT" string goot

0 constant NULL

tst-depth .s cr

11 char[]: bufptr 

.s cr
0 variable ccnt
: ruel begin 
            55 ccnt @ bufptr + c! 1 ccnt +! ccnt @ 9 > 
       until 
       bufptr ccnt @ + 0 swap c! 
       ;
ruel

.s cr
bufptr dup char[]_len type cr

.s

: tst_cstr c" a string " ;

tst_cstr count type cr
.s

1 2 3 4 2swap . . . . cr 
1 2 3 4 2over . . . . . . cr 

char a constant na

: hoove 26 0 do i na + emit
               i 10 > if [char] . emit then 
             loop  
   cr " foo" printstring 
   s" one " type cr 
   c" two " count type ; immediate

: foove 1 begin 1+ dup 20 < while [char] 221 emit repeat drop cr ; immediate

 : droove 0 1 2 3
      begin dup
          case 
            1 of s" three" type cr endof
            2 of s" four" type cr endof
            drop
         endcase
        while 
        repeat ; immediate

 ' droove decompile

hoove
foove
droove

: nhoove hoove foove ;


" **) test formated output" printstring cr
hex

FFA02 <# # # #s #> type cr

decimal

: cc c" 123" ; cr
cc 6 + c@ emit cr

" 29) test str>cstr " printstring cr
 goot bufptr str>cstr 
 bufptr count type cr

tst-depth

" 30) test delchar " printstring cr

bufptr delchar[] .

tst-depth

" 31) >>> Test structure defining words " printstring cr

structure: SmallStruct
  25 +char  Small_name
      +long  Small_long
structure;

structure: LargeStruct
 25              +char     Large_name
                 +long     Large_long
                 +short    Large_short
 2               +long[]   Large_both
 3  SmallStruct  +object[] Large_small
structure;

cr cr
" 32) print struct size " printstring cr
LargeStruct . cr

" 33) >>> Test create instance of structure " printstring cr

LargeStruct new-structure variable AddrLarge

" 34) Address of new instance " printstring cr
AddrLarge @ . cr

" 35) Address Large_long  (+25) " printstring cr
AddrLarge @ Large_long dup . AddrLarge @ - .  cr 

" 36) Address Large_short  (29) " printstring cr
AddrLarge @ Large_short dup . AddrLarge @ - .  cr

" 37) Address Large_both[0]  (31) " printstring cr
AddrLarge @ 0 Large_both dup . AddrLarge @ - .  cr

" 38) Address Large_both[1]  (35) " printstring cr
AddrLarge @ 1 Large_both dup . AddrLarge @ - .  cr

" 39) Address Large_small[0]  (39) " printstring cr
AddrLarge @ 0 Large_small dup . AddrLarge @ - .  cr

" 40) Address Large_small 1 Small_long " printstring 39 SmallStruct + 25 + . cr
AddrLarge @ 1 Large_small Small_long dup . AddrLarge @ - . cr

" 41) put 1000 in  *AddrLarge.Large_small[1].Small_long " printstring cr
1000 AddrLarge @ 1 Large_small Small_long !

" 42) get the long back " printstring cr
AddrLarge @ 1 Large_small Small_long @ . cr

tst-depth

: groog 10 0 do i . loop cr ;
" i test " printstring cr

groog


" 43) Test +loop " printstring cr

: nooot 20 0 do i . 2 +loop cr ;

: rooot do i . 2 +loop cr ;

nooot
20 0 rooot

" 44) Test ?do " printstring cr

: erool ?do i . 2 +loop cr ;

.s

10 0 erool

// ' erool decompile

 6 6 erool

2 5 7 .s drop drop drop cr .s cr

// ' erool decompile

.s

 " 45) test i i " printstring cr

: juuoool nop 
    10 0 
    do 
         " nxn:" printstring 
         i i * . cr 
    loop 
  ;

' juuoool decompile 

juuoool cr

.s

" 46) test i with j " printstring cr

: drool 5 0 do 
            5 0 do 
                i j * . 
                loop cr 
            loop cr 
        ;

drool

.s

" 47) i inside loop and if " printstring cr 

: xzoool 5 0 do
                i dup . 4 == 
                if 
                   i . 
                then 
            loop cr 
        ;

.s

 xzoool

.s


 " 48) test leave " printstring cr

: iiiool 10 0 
             do 
                     i dup . 7 == 
                     if 
                        i . 
                        leave 
                     then 
             loop 
             cr 
       ;

.s 

' iiiool decompile cr

 .s

 iiiool 

.s

" 49) test case " printstring cr

: casetest 10 0 do i dup . 
   case 
   1 of i 10 + . endof
   2 of i 10 + . endof
   3 of i 10 + . endof
   20 + . 
   endcase cr
   loop ;

casetest

" 50) test begin while repeat " printstring cr

: tbwr 
         begin 3 + dup . 
                   dup 20 < dup .
         while dup 10 + . cr
         repeat . cr ;

3 tbwr

' tbwr decompile


" 51) test immediate and literal " printstring cr
traceon
: timm 2 ; immediate

: tlit timm literal 2 * . cr ;

tlit
traceoff
traceon
: gt8 state @ ; immediate 
gt8 . cr
traceoff
traceon
: gt9 gt8 literal ;
gt9 . cr
traceoff


' tlit is-in-voc cr

vocabulary roof immediate

roof definitions

: peak 2 2 + . cr ;

' peak is-in-voc cr

peak

forth definitions

tlit 

// release roof

// ' peak . cr

.s cr

: test-s" s" foobar" type cr ;

test-s" cr

1 1 rshift . cr
2 1 rshift . cr
0 1 rshift . cr
2 1 lshift . cr

0 invert . cr

traceon
: km 2 . ; source type cr
traceoff

create testcre 14 allot ;create

' testcre decompile cr

: mcre create 100 allot does> 10 + ;

' mcre decompile cr

' mcre . cr
.s

mcre fmcre

.s

' fmcre decompile cr

.s

fmcre . cr

.s

" 53) test exit " printstring cr

: testex begin 20 0 do 10 0 do j dup . 7 == if exit then loop cr loop again ;

testex cr

" 54) test [ ] and literal " printstring cr

: testbb [ 17 2 * ] literal . cr ;

' testbb decompile cr

testbb 

: testR 2 >r r@ . r> . cr ;

testR

" 55) test roll " printstring cr
1 2 3 4 3 roll .s drop drop drop drop .s

" 56) test unloop exit " printstring cr

: testule 10 0 do i . 10 0 do i dup . 5 == if unloop unloop exit then loop cr loop ;

testule

' testule decompile

" 57) test recurse " printstring cr

: testrec 1+ dup 4 < if recurse else . then ;

0 testrec

' testrec decompile 


" 58) test f/ fsin fcos facos fasin " printstring cr

: testfa  1 d>f fdup f. cr
         10 d>f fdup f. cr
         f/ fdup f. cr
         fsin fdup f. cr
         fcos fdup f. cr
         facos fdup f. cr
         fasin f. cr ;

testfa 

" 59) test small class " printstring cr

traceon

class: goomb

traceoff

" 60) started class definition " printstring cr

traceon

   [dword] anw

traceoff

" 61) added 1st [dword] object " printstring cr


   [dword] bnw
   [dword] cnw

                                      traceon
 public:
                                      traceoff
   [dword] anw2
   [dword] bnw2
   [dword] cnw2

traceon
  m: Anw@ anw @ m;
traceoff


" 62) added 1st method " printstring cr

  m: Anw! anw ! m;
  m: Bnw@ bnw @ m;
  m: Bnw! bnw ! m;
  m: Cnw@ cnw @ m;
  m: Cnw! cnw ! m;
   
traceon
  m: SumAB 1 Anw! 1 Bnw! Anw@ Bnw@ + dup . Cnw!  Cnw@ . cr m;
traceoff

traceon
class;
traceoff

traceon
goomb pulah
traceoff

traceon 
pulah -: SumAB
traceoff

" 63) test (decompile)-class " printstring cr

(decompile)-class goomb 

" 64) test use of class in defined method " printstring cr

traceon
: umber pulah -: SumAB ;
traceoff

umber

pulah delete

" 65) test use of class in class " printstring cr

traceon
class: goomb2

   [dword] mule
   [class] goomb truel

public:
   [dword] mule2
   [class] goomb truel2

   m: Intrule 2 truel -: Anw! 2 truel -: Bnw! 1 mule ! m;
   m: Usetruel truel -: Anw@ truel -: Bnw@ mule @ + + . " result of goomb2 Usetrue1" printstring  cr m;

   m: Intrule2  2 truel2 -: anw2 ! 2 truel2 -: bnw2 ! 1 mule2 ! m;
   m: Usetruel2 truel2 -: anw2 @ truel2 -: bnw2 @ mule2 @ + + . " result of goomb2 Usetrue12" printstring  cr m;

class;
traceoff

goomb2 pulah2

traceon
pulah2 -: Intrule
pulah2 -: Usetruel
traceoff

traceon
pulah2 -: Intrule2
pulah2 -: Usetruel2
traceoff

" 66) test use of class in class " printstring cr

: floom pulah2 -: Intrule pulah2 -: Usetruel ;

floom

" 67) test class inheritance" printstring cr

traceon
class: hoomw public: := goomb
private:

   [dword] Adw
   [class] goomb acl

public:


   m: tcn1 5 hoomw::goomb -: Anw!  
           5 hoomw::goomb -: Bnw!  
           5 hoomw::goomb -: Cnw!  
   m; 

   m: tcn2 hoomw::goomb -: Anw@  
           hoomw::goomb -: Bnw@  
           hoomw::goomb -: Cnw@   
           + + . cr 
   m; 

  m:  tcn3 6  Anw!  
           6  Bnw!  
           6  Cnw!  
   m; 

 m:  tcn4  7  Anw!  
           7  Bnw!  
           7  Cnw!  
   m; 

class;
traceoff

hoomw apngo 

" 68) test class access to inherited class using -: " printstring cr
apngo -: tcn1 apngo -: tcn2

" 69) test class access to inherited class using the inherited methods " printstring cr
apngo -: tcn3 apngo -: tcn2

apngo delete

traceon

class: TestDataTypes
   private:
        [byte]     a_byte
      2 [bytes]    2_bytes
        [word]     a_word
      3 [words]    3_words
        [dword]    a_dword
      4 [dwords]   4_dwords
        [pointer]  a_pointer
      5 [pointers] 5_pointers
   6 10 [arrays]   7_arrays
        [class]   hoomw  a_class
      8 [classes] hoomw  8_classes
   public:

   m: space 32 emit m;  // not defined

   m: TestDataTypes! 
       1 a_byte c!
    3  2 do 
               i dup 2 - 2_bytes c! 
         loop
       4 a_word w!
    7  4 do 
               i dup 4 - 3_words w! 
         loop
       8 a_dword ! 
   12  9 do
               i dup 9 - 4_dwords ! 
         loop
      13 a_pointer !
   19 14 do 
               i dup 14 - 5_pointers ! 
         loop
   26 20 do 
            9 0 do 
                      j 32 + i +
                      j 20 - 7_arrays i + dup 1+ 0 swap c! c! 
                loop 
         loop 
         a_class -: tcn4 
         35 28 do i 28 - 8_classes -: tcn3 loop 
    m;


   m: TestDataTypes@ 
         a_byte dup . c@ . cr
    3  2 do 
              i  2 - 2_bytes dup . c@ . space 
         loop cr
         a_word dup . w@ . cr 
    7  4 do 
              i  4 - 3_words dup . w@ . space 
         loop cr
         a_dword dup . @ . cr 
   12  9 do 
                   i 9 - 4_dwords dup . @ . space 
         loop cr
         a_pointer dup . @ . cr
   19 14 do 
             i 14 - 5_pointers dup . @ . space 
         loop cr
   26 20 do 
            9 0 do 
                       j 20 - 7_arrays i + dup . 32 emit c@ emit  
                loop cr 
         loop 
         a_class -: tcn2 
         35 28 do i 28 - 8_classes -: tcn2 loop 
    m;
    
traceoff

class;
         
TestDataTypes testinst

testinst -: TestDataTypes!
testinst -: TestDataTypes@

testinst delete 

" 70) test automatic call to constructor and override forth words with method names" printstring cr

class: Toot
    [dword] tootval
public:

traceon
   m: Toot 111222 tootval ! m;
traceoff
   m: GetToot tootval @ m;
   m: ReadToot tootval @ . cr m;
   m: + * m;

class;

.s cr

Toot A_Toot

A_Toot -: ReadToot
 1 1  A_Toot -: +  . cr

" 70) test automatic call to constructor with new and -> " printstring cr
traceon
new Toot variable holds_Toot
traceoff

holds_Toot @ -> Toot ReadToot cr

" 71) test constructor with constructor inheritance " printstring cr

traceon
class: FromToot public: := Toot
traceoff

private:
   [dword] plustoot

  m: FromToot GetToot 222 - plustoot ! m;
  m: ReadPlus plustoot @ . cr m;
class;

(decompile)-class FromToot
  
traceon
FromToot B_Toot
traceoff


B_Toot -: ReadPlus

A_Toot delete
B_Toot delete

.s cr


" 71) test m* s<d " printstring cr

2 base !
100 s>d . bl emit  . cr
100 1 - s>d  . bl emit  . cr
-100 s>d . bl emit . cr
-100 1 +  s>d . bl emit  . cr
.s cr

" 72) test sm/rem fm/mod with both positive" printstring cr

10000000 10000000 m*  2dup . bl emit . cr   \ 100 0000 0000 0000
10000000 sm/rem . bl emit . cr 
10000000 10000000 m*  2dup . bl emit . cr   \ 100 0000 0000 0000
10000000 fm/mod . bl emit . cr 
.s cr
" 73) test sm/rem fm/mod with negative divisor" printstring cr

10000000 10000000 m*  2dup . bl emit . cr   \ 100 0000 0000 0000
-10000000 sm/rem . bl emit . cr 
10000000 10000000 m*  2dup . bl emit . cr   \ 100 0000 0000 0000
-10000000 fm/mod . bl emit . cr 
.s cr
" 74) test sm/rem fm/mod with negative d " printstring cr

-10000000 10000000 m*  2dup . bl emit . cr  \ 100 0000 0000 0000
10000000 sm/rem . bl emit . cr 
-10000000 10000000 m*  2dup . bl emit . cr  \ 100 0000 0000 0000
10000000 fm/mod . bl emit . cr 
decimal .s cr

10 0 -7 sm/rem . bl emit . cr
10 0 -7 fm/mod . bl emit . cr
-10 s>d 7 sm/rem . bl emit . cr
-10 s>d 7 fm/mod . bl emit . cr

2147483647 constant max-int
0 2147483647 - 1 - constant min-int 
42949672935 constant max-uint

.s
hex
traceon
: output-test
   ." you should see the standard graphic characters:" cr
   41 bl do i emit loop cr
   61 41 do i emit loop cr
   7f 61 do i emit loop cr
   ." you should see 0-9 separated by a space:" cr
   9 1+ 0 do i . loop cr
   ." you should see 0-9 (with no spaces):" cr
   [char] 9 1+ [char] 0 do i 0 spaces emit loop cr
   ." you should see a-g separated by a space:" cr
   [char] g 1+ [char] a do i emit space loop cr
   ." you should see 0-5 separated by two spaces:" cr
   5 1+ 0 do i [char] 0 + emit 2 spaces loop cr
   ." you should see two separate lines:" cr
   s" line 1" type cr s" line 2" type cr 
   ." you should see the number ranges of signed and unsigned numbers:" cr
   ."   signed: " min-int . max-int . cr
   ." unsigned: " 0 u. max-uint u. cr
 ;
decimal
traceoff
output-test

" 75) test included " printstring cr

: ftoinc s" test_included.4th " ;
ftoinc .s cr included cr

" 76) test stack underflow to see error " printstring cr

: loogg 1 1 + drop soog ;

.s

 loogg cr

" Test Complete -------------------------------" printstring cr
 


