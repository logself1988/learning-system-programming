/* Global array */
int numbers[10];

/* Returns the largest value from array numbers. */
int get_largest_number()
{
  int largest = numbers[0];
  for (int i = 1; i < 10; i++)
  {
    if (numbers[i] > largest)
      largest = numbers[i];
  }
  return largest;
}