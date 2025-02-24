Tests
 1. Charecter input
    Input: abcd
    Output: (blank)
 2. Negative input to check bounds
    Input: -123
    Output: (blank)
 3. Zero
    Input: 0
    Output: 0 = zero cents
 4. One
    Input: 1
    Output: 1 = one cent
 5. Decimal input
    Input: 100.4
    Output: 100 = one dollar and zero cents
 6. Different numbers in all palces
    Input: 234
    Output: 234 = two dollars and thirty-four cents
 7. Hundreds place
    Input: 10000
    Output: 10000 = one hundred  dollars and zero cents
 8. Thousands place
    Input: 150000
    Output: 150000 = one thousand five hundred  dollars and zero cents
 9. First past cache
    Input: 150001
    Output: 150001 = one thousand five hundred  dollars and one cent
10. Hundred thousands place
    Input: 15000000
    Output: 15000000 = one hundred fifty thousand zero cents
11. All different numbers (large)
    Input: 12345678
    Output: 12345678 = one hundred twenty-three thousand four hundred fifty-six dollars and seventy-eight cents
12. All different numbers other than cents are zero
    Input: 12345678900
    Output: 123456789 = one million two hundred thirty-four thousand five hundred sixty-seven dollars and eighty-nine cents
13. Almost upper limit of cents
    Input: 99
    Output: 99 = ninety-nine cents
14. One billion
    Input: 100000000000
    Output: 100000000000 = one billion zero cents
15. One billion one dollar to check upper limit
    Input: 100000000100
    Output: (blank)