#! /usr/bin/bash
# file msgrw.sh
mkfifo usrfifo
read(){
    i=0
    cat < usrfifo
}
write(){
    i=0
    echo "$str"
    echo "$str" > usrfifo
    
}


i=1
while [ $i -eq 1 ] 
do
    cmd=$1
    r=-read
    w=-write
    if [ "$cmd" != "$r" ]
    then
        if [ "$cmd" != "$w" ]
        then
            echo "wrong syntax"
            echo "[ $cmd -ne $r ]"
            i=0
        elif [ "$cmd" == "$r" ]
        then
            read
        elif [ "$cmd" == "$w" ]
        then
            str=$2
            if [ "$str" == "" ]
            then
                echo "no text msg"
                i=0
            else
                write
            
            fi
        fi
    fi
done
