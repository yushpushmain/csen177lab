# Name: Ayush Gupta
# Date: 6th Jan
# Title: Lab 1 - task 3
# Description: This program computes the area and perimeter of a circle

#!/bin/sh
area(){
	echo "3.14 * $radius * $radius" | bc
}

perimeter(){
	echo "2 * 3.14 * $radius" | bc
}

echo Executing
echo "Enter radius of circle: "
read radius

if [ $radius -ge 0 ]; then
	a=$(area)
	p=$(perimeter)
	echo "The area of the circle is $a"
	echo "The perimeter of the circle is $p"
else
	echo "Enter positive radius"
fi



