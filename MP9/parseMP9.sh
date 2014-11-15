#!bin/bash

while read li
do
  stud=$(echo $li | awk '{print $1}')
  sect=$(echo $li | awk '{print $2}')
  ta=$(echo $li | awk '{print $3}')

  sub=0
  end2=0
  end4=0
  rf=0
  sb=0
  lp=0
  ivr=10
  cc=10
  warning=5

  cd /class/ece198kl/Sp14/MP9/$stud

  while read line
  do
    if [[ $line == Lost* ]]
    then
      sub=$(echo $line | awk '{print $2}')
    elif [[ $line == Endian2* ]]
    then
      end2=$(echo $line | awk '{print $2}')
    elif [[ $line == Endian4* ]]
    then
      end4=$(echo $line | awk '{print $2}')
    elif [[ $line == ReadFile* ]]
    then
      rf=$(echo $line | awk '{print $2}')
    elif [[ $line == SoundByte* ]] 
    then
      sb=$(echo $line | awk '{print $2}')
    elif [[ $line == LoPass* ]]
    then
      lp=$(echo $line | awk '{print $2}')
    elif [[ $line == *warning* ]]
    then
      warning=0
    elif [[ $line == *error* ]]
    then
      warning=0
      end2=0
      end4=0
      rf=0
      sb=0
      lp=0
      error=1
    fi
  done < /class/ece198kl/Sp14/MP9/$stud/results.txt
  tot=$(($end2+$end4+$rf+$sb+$lp))
  if [[ $tot -eq 0 ]]
  then
    ivr=0
    cc=0
  fi
  echo "$stud,$sect,$ta,$end2,$end4,$rf,$sb,$warning,$ivr,,$cc,$lp,$sub,,,,,," >> ~/ssRes.txt
done < /class/ece198kl/Sp14/spreadSheet.txt

