#!bin/bash

bash /class/ece198kl/Fa14/scripts/lateSub.sh -d "2014-11-12 22:00" > results.txt
echo "Compilation Results" >> results.txt
echo "*******************" >> results.txt
g++ -g -Wall -lm prog9.c mainTest.c &>> results.txt
timeout 10 ./a.out 1 ~/pepper/MP9/piano.wav stud.wav 5 4 10 > studout.txt
timeout 10 ./a.out 2 ~/pepper/MP9/omg.wav studChal.wav 500

echo "" >> results.txt
echo "Program 9" >> results.txt
echo "*******************" >> results.txt

end2=0
end4=0
readFile=0
sloop=0
loPass=0

if [[ -e "a.out" ]]
then
  head -1 studout.txt > studEnd2.txt
  head -2 studout.txt | tail -1 > studEnd4.txt
  sed -i "1,2d" studout.txt
  awk '{split($0,a,":");print a[2]}' studout.txt > studRead.txt
  if ! [[ $(diff -wB studEnd2.txt goldEnd2.txt) ]]
  then
    end2=10
  fi
  if ! [[ $(diff -wB studEnd4.txt goldEnd4.txt) ]]
  then 
    end4=10
  fi
  if ! [[ $(diff -wB studRead.txt goldRead.txt) ]]
  then
    readFile=25
  fi
  if [[ -e "stud.wav" ]]
  then
    if ! [[ $(diff -wB stud.wav ~/pepper/MP9/gold.wav) ]]
    then
      sloop=25
    fi
  fi
  if [[ -e "studChal.wav" ]]
  then
    if ! [[ $(diff -wB studChal.wav ~/pepper/MP9/goldChal.wav) ]]
    then
      loPass=20
    fi
  fi
fi

echo "Endian2: $end2" >> results.txt
echo "Endian4: $end4" >> results.txt
echo "ReadFile: $readFile" >> results.txt
echo "sloop: $sloop" >> results.txt
echo "" >> results.txt

echo "Challenges" >> results.txt
echo "*******************" >> results.txt
echo "LoPass: $loPass" >> results.txt

