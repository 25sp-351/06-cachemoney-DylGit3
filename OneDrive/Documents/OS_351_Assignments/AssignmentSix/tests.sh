#!/bin/bash

echo "Running test cases..."

echo "Test Case 1: Character input"
echo "abcd" | ./money.exe
echo "-----------------------------"

echo "Test Case 2: Negative input"
echo "-123" | ./money.exe
echo "-----------------------------"

echo "Test Case 3: Zero"
echo "0" | ./money.exe
echo "-----------------------------"

echo "Test Case 4: One"
echo "1" | ./money.exe
echo "-----------------------------"

echo "Test Case 5: Decimal input"
echo "100.4" | ./money.exe
echo "-----------------------------"

echo "Test Case 6: Different numbers in all places"
echo "234" | ./money.exe
echo "-----------------------------"

echo "Test Case 7: Hundreds place"
echo "10000" | ./money.exe
echo "-----------------------------"

echo "Test Case 8: Thousands place"
echo "150000" | ./money.exe
echo "-----------------------------"

echo "Test Case 9: First past cache"
echo "150001" | ./money.exe
echo "-----------------------------"

echo "Test Case 10: Hundred thousands place"
echo "15000000" | ./money.exe
echo "-----------------------------"

echo "Test Case 11: All different numbers (large)"
echo "12345678" | ./money.exe
echo "-----------------------------"

echo "Test Case 12: All different numbers other than cents are zero"
echo "12345678900" | ./money.exe
echo "-----------------------------"

echo "Test Case 13: Almost upper limit of cents"
echo "99" | ./money.exe
echo "-----------------------------"

echo "Test Case 14: One billion"
echo "100000000000" | ./money.exe
echo "-----------------------------"

echo "Test Case 15: One billion one dollar"
echo "100000000100" | ./money.exe
echo "-----------------------------"

echo "Test cases completed."